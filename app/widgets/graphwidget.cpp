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
    customPlot->yAxis2->setRange(-1.2, 1.2);
    customPlot->yAxis2->setLabel("Position");
    customPlot->yAxis2->setTickLabels(true);
    
    // make left and bottom axes transfer their ranges to right and top axes:
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    // connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
    
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
        customPlot->graph(1)->rescaleValueAxis();
        customPlot->graph(2)->rescaleValueAxis();
        customPlot->graph(3)->rescaleValueAxis();
        customPlot->graph(4)->rescaleValueAxis();
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
