#include "legcontrolwidget.h"
#include "ui_legcontrolwidget.h"

LegControlWidget::LegControlWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LegControlWidget)
{
    ui->setupUi(this);
    connect(ui->allocateButton, &QPushButton::clicked, this, &LegControlWidget::allocate_joints);
}


LegControlWidget::~LegControlWidget()
{
    delete ui;
}

void LegControlWidget::allocate_joints()
{

    qDebug() << "Allocate joints";
    QJoint* hipYawJoint = ui->hipYawJoint->get_joint();
    QJoint* hipPitchJoint = ui->hipPitchJoint->get_joint();
    QJoint* kneePitchJoint = ui->kneePitchJoint->get_joint();


    g_joints.get_legJoints(&hipYawJoint, &hipPitchJoint, &kneePitchJoint, m_leg.get_legNumber());
    ui->hipYawJoint->update();
    // g_joints.get_legJoints(&joint1, &joint2, &joint3, m_leg.get_legNumber());
    // g_joints.get_legJoints(ui->hipYawJoint->get_joint(), &ui->hipPitchJoint->get_joint(), &ui->kneePitchJoint->get_joint(), m_leg.get_legNumber());
}
