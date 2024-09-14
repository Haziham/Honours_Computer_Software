#include "hexapodcontrolwidget.h"
#include "ui_hexapodcontrolwidget.h"

HexapodControlWidget::HexapodControlWidget(QHexapod* hexapod, QWidget *parent)
    : ControlWidget(parent)
    , ui(new Ui::HexapodControlWidget)
{
    ui->setupUi(this);
    m_hexapod = hexapod;

    ui->leg0Button->set_leg(&hexapod->leg0);
    ui->leg1Button->set_leg(&hexapod->leg1);
    ui->leg2Button->set_leg(&hexapod->leg2);
    ui->leg3Button->set_leg(&hexapod->leg3);
    ui->leg4Button->set_leg(&hexapod->leg4);
    ui->leg5Button->set_leg(&hexapod->leg5);

    connect(ui->calibrateButton, &QPushButton::clicked, m_hexapod, &QHexapod::start_calibration);
    connect(ui->allocateJointsButton, &QPushButton::clicked, m_hexapod, &QHexapod::allocate_joints);
    connect(ui->enableButton, &QPushButton::clicked, m_hexapod, &QHexapod::enable);
    connect(ui->disableButton, &QPushButton::clicked, m_hexapod, &QHexapod::disable);

    ui->heightInput->set_label("Height");
    ui->directionAngleInput->set_label("Direction Angle");
    ui->globalXInput->set_label("Global X");
    ui->globalXInput->set_minimum(0);
    ui->globalXInput->set_value(160);
    ui->globalXInput->set_maximum(320);
    ui->globalYInput->set_label("Global Y");
    ui->globalYInput->set_minimum(-160);
    ui->globalYInput->set_maximum(160);
    ui->globalZInput->set_label("Global Z");
    ui->globalZInput->set_minimum(-160);
    ui->globalZInput->set_maximum(160);


    connect(ui->globalXInput, SIGNAL(valueChanged(int)), this, SLOT(set_globalPosition()));
    connect(ui->globalYInput, SIGNAL(valueChanged(int)), this, SLOT(set_globalPosition()));
    connect(ui->globalZInput, SIGNAL(valueChanged(int)), this, SLOT(set_globalPosition()));



    start_refresh_timer();

}

HexapodControlWidget::~HexapodControlWidget()
{
    delete ui;
}

void HexapodControlWidget::refresh_widget()
{
    ui->leg0ForceDisplay->display(m_hexapod->leg0.get_force());
    ui->leg1ForceDisplay->display(m_hexapod->leg1.get_force());
    ui->leg2ForceDisplay->display(m_hexapod->leg2.get_force());
    ui->leg3ForceDisplay->display(m_hexapod->leg3.get_force());
    ui->leg4ForceDisplay->display(m_hexapod->leg4.get_force());
    ui->leg5ForceDisplay->display(m_hexapod->leg5.get_force());


}

void HexapodControlWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);  // Call base class implementation
    m_hexapod->allocate_joints();
}

void HexapodControlWidget::set_globalPosition()
{
    m_hexapod->set_allLegPositions(ui->globalXInput->value(), ui->globalYInput->value(), ui->globalZInput->value());
}
