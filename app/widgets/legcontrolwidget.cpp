#include "legcontrolwidget.h"
#include "ui_legcontrolwidget.h"

LegControlWidget::LegControlWidget(QLeg* leg, QWidget *parent)
    : ControlWidget(parent)
    , ui(new Ui::LegControlWidget)
{
    ui->setupUi(this);

    ui->xPositionInput->set_minimum(0);
    ui->yPositionInput->set_minimum(-160); 
    ui->zPositionInput->set_minimum(-160);

    ui->xPositionInput->set_maximum(320);
    ui->yPositionInput->set_maximum(160);
    ui->zPositionInput->set_maximum(160);
    
    ui->xPositionInput->set_value(80);
    ui->yPositionInput->set_value(80);
    ui->zPositionInput->set_value(80);

    ui->xPositionInput->set_label("X Position");
    ui->yPositionInput->set_label("Y Position");
    ui->zPositionInput->set_label("Z Position");

    connect(ui->allocateButton, &QPushButton::clicked, this, &LegControlWidget::allocate_joints);
    connect(ui->calibrateButton, &QPushButton::clicked, leg, &QLeg::start_calibration);


    connect(ui->xPositionInput, SIGNAL(valueChanged(int)), this, SLOT(set_position()));
    connect(ui->yPositionInput, SIGNAL(valueChanged(int)), this, SLOT(set_position()));
    connect(ui->zPositionInput, SIGNAL(valueChanged(int)), this, SLOT(set_position()));

    connect(ui->enableButton, &QPushButton::clicked, this, &LegControlWidget::enable);
    connect(ui->disableButton, &QPushButton::clicked, this, &LegControlWidget::disable);


    m_leg = leg;

    start_refresh_timer();
}


LegControlWidget::~LegControlWidget()
{
    delete ui;
}

void LegControlWidget::allocate_joints()
{
    QJoint* hipYawJoint = nullptr;
    QJoint* hipPitchJoint = nullptr;
    QJoint* kneePitchJoint = nullptr;


qDebug() << "Allocating joints: " << QString::number(m_leg->get_legNumber());
    g_joints.get_legJoints(&hipYawJoint, &hipPitchJoint, &kneePitchJoint, m_leg->get_legNumber());

    if (hipYawJoint != nullptr || hipPitchJoint != nullptr || kneePitchJoint != nullptr)
    {
        qDebug() << "No Joints Found";
    }

    ui->hipYawJoint->set_joint(hipYawJoint);
    ui->hipPitchJoint->set_joint(hipPitchJoint);
    ui->kneePitchJoint->set_joint(kneePitchJoint);

qDebug() << "Setting joints";
    m_leg->set_joints(hipYawJoint, hipPitchJoint, kneePitchJoint);
qDebug() << "Joints set";
}

void LegControlWidget::refresh_widget()
{
    QJoint* forceRecordingJoint = ui->kneePitchJoint->get_joint();

    if (forceRecordingJoint != nullptr)
    {
        ui->forceDisplay->setEnabled(true);
        ui->forceDisplay->display(forceRecordingJoint->get_force());
    }
    else {
        ui->forceDisplay->display(0);
        ui->forceDisplay->setDisabled(true);
    }
}

void LegControlWidget::set_position()
{
    m_leg->set_position(ui->xPositionInput->value(), ui->yPositionInput->value(), ui->zPositionInput->value());
}
