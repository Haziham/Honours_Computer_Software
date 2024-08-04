#include "legcontrolwidget.h"
#include "ui_legcontrolwidget.h"

LegControlWidget::LegControlWidget(QLeg* leg, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LegControlWidget)
{
    ui->setupUi(this);

    ui->xPositionInput->set_minimum(0);
    ui->yPositionInput->set_minimum(-160); 
    ui->zPositionInput->set_minimum(-160);

    ui->xPositionInput->set_maximum(160);
    ui->yPositionInput->set_maximum(160);
    ui->zPositionInput->set_maximum(160);
    
    ui->xPositionInput->set_value(80);
    ui->yPositionInput->set_value(80);
    ui->zPositionInput->set_value(80);



    connect(ui->allocateButton, &QPushButton::clicked, this, &LegControlWidget::allocate_joints);
    connect(ui->xPositionInput, SIGNAL(valueChanged(int)), this, SLOT(set_position()));
    connect(ui->yPositionInput, SIGNAL(valueChanged(int)), this, SLOT(set_position()));
    connect(ui->zPositionInput, SIGNAL(valueChanged(int)), this, SLOT(set_position()));


    m_leg = leg;
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

    g_joints.get_legJoints(&hipYawJoint, &hipPitchJoint, &kneePitchJoint, m_leg->get_legNumber());

    ui->hipYawJoint->set_joint(hipYawJoint);
    ui->hipPitchJoint->set_joint(hipPitchJoint);
    ui->kneePitchJoint->set_joint(kneePitchJoint);

    m_leg->set_joints(hipYawJoint, hipPitchJoint, kneePitchJoint);
}

void LegControlWidget::set_position()
{
    m_leg->set_position(ui->xPositionInput->value(), ui->yPositionInput->value(), ui->zPositionInput->value());
}
