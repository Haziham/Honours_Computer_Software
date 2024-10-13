#include "graphwidget.h"
#include "ui_graphwidget.h"
#include <cstdlib>

GraphWidget* graphWidget;
GraphWidget::GraphWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GraphWidget)
{
    ui->setupUi(this);
    QCustomPlot *customPlot = ui->graph;

    customPlot->addGraph(); // blue line
    customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    customPlot->addGraph(); // red line
    customPlot->graph(1)->setPen(QPen(QColor(255, 110, 40)));
    customPlot->addGraph(customPlot->xAxis, customPlot->yAxis2); // green line
    customPlot->graph(2)->setPen(QPen(QColor(40, 255, 40)));
    customPlot->addGraph(customPlot->xAxis, customPlot->yAxis2); // green line
    customPlot->graph(3)->setPen(QPen(QColor(0, 0, 0)));
    customPlot->addGraph(customPlot->xAxis, customPlot->yAxis2); // green line
    customPlot->graph(4)->setPen(QPen(QColor(255, 40, 255)));
    
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    customPlot->xAxis->setTicker(timeTicker);
    customPlot->axisRect()->setupFullAxesBox();
    customPlot->yAxis->setRange(-1.2, 1.2);
    // show yqxis 2
    customPlot->yAxis2->setVisible(true);
    customPlot->yAxis2->setTickLength(3, 3);
    customPlot->yAxis2->setSubTickLength(1, 1);
    customPlot->yAxis2->setRange(-100, 100);
    customPlot->yAxis2->setLabel("Position");
    customPlot->yAxis2->setTickLabels(true);
    
    // make left and bottom axes transfer their ranges to right and top axes:
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    // connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
    connect(ui->exportToCSVButton, &QPushButton::clicked, this, &GraphWidget::exportGraphToCSV);   
    
    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables );
    joint = nullptr;
}

GraphWidget::~GraphWidget()
{
    delete ui;
}

void GraphWidget::allocate_joint(QJoint *joint)
{
    dataTimer.stop();

    qDebug() << "Allocating joint";
    this->joint = joint;

    // if window is shown, start timer
    if (isVisible())
    {
        dataTimer.start(0);
    }
}


void GraphWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    time.restart();
    dataTimer.start(0);
}

void GraphWidget::hideEvent(QHideEvent *event)
{
    dataTimer.stop();
    QWidget::hideEvent(event);
}

void GraphWidget::realtimeDataSlot()
{
    if (joint == nullptr)
        return;

    QCustomPlot* customPlot = ui->graph;
    QRandomGenerator rand;
    // calculate two new data points:
    double key =  time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.002) // at most add point every 2 ms
    {
        // qDebug() << "Adding data point";
        // add data to lines:

        // customPlot->graph(0)->addData(key, qSin(key)+rand.generate()/(double)RAND_MAX*1*qSin(key/0.3843));
        // customPlot->graph(1)->addData(key, qCos(key)+rand.generate()/(double)RAND_MAX*0.5*qSin(key/0.4364));
        customPlot->graph(0)->addData(key, joint->statusA.position);
        customPlot->graph(1)->addData(key, joint->settings.internal.targetCommand);
        customPlot->graph(2)->addData(key, joint->statusC.debugValue1);
        customPlot->graph(3)->addData(key, joint->statusC.debugValue2);
        customPlot->graph(4)->addData(key, joint->statusC.debugValue3);

        // rescale value (vertical) axis to fit the current data:
        customPlot->graph(0)->rescaleValueAxis();
        customPlot->graph(1)->rescaleValueAxis(true);
        // customPlot->graph(2)->rescaleValueAxis();
        // customPlot->graph(3)->rescaleValueAxis(true);
        // customPlot->graph(4)->rescaleValueAxis(true);
        lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    customPlot->xAxis->setRange(key, 5, Qt::AlignRight);
    customPlot->replot();
    
    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) // average fps over 2 seconds
    {
    lastFpsKey = key;
    frameCount = 0;
    }
}


void GraphWidget::exportGraphToCSV()
{

    QCustomPlot *customPlot = ui->graph;

    if (!customPlot) {
        qWarning() << "Not plot";
        return;
    }

    // Open file for writing
    QFile file("/home/harry/University/Honours/Honours_Testing/Honours_Results_EXP3.csv");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file for writing";
        return;
    }

    QTextStream out(&file);

    // Write CSV header
    out << "time,targetPos,actualPos,proportional,derivative,integral\n";

    // Get the data container
    QSharedPointer<QCPGraphDataContainer> position = customPlot->graph(1)->data();
    QSharedPointer<QCPGraphDataContainer> target = customPlot->graph(0)->data();
    QSharedPointer<QCPGraphDataContainer> proportional = customPlot->graph(2)->data();
    QSharedPointer<QCPGraphDataContainer> derivative = customPlot->graph(3)->data();
    QSharedPointer<QCPGraphDataContainer> integral = customPlot->graph(4)->data();

    double startTime = 0;
    bool startWriting = false;
    double captureTime = 4;
    double leadIn = 400;
    // Iterate through data points and write to CSV
    for (int i = 0; i < position->size()-leadIn; i++) {
        double time = position->at(i)->key;
        double targetPos = position->at(i)->value;
        double actualPos = target->at(i)->value;
        double p = proportional->at(i)->value;
        double d = derivative->at(i)->value;
        double in = integral->at(i)->value;

        // double futureTarget = position->at(i+leadIn)->value;
        // if (futureTarget == 900) {
        //     startWriting = true;
        //     startTime = time;
        // }

        if (targetPos == -1000)
        {
            startWriting = true;
        }

        if (!startWriting) {
            continue;
        }

        if (targetPos == -1001)
        {
            break;
        }

        // if (time - startTime > captureTime) {
        //     break;
        // }
        out << time << "," << targetPos <<  ", " << actualPos << "," << p << "," << d << "," << in << "\n";
    }
    file.close();
    qDebug() << "Data exported to" << "cool";
}