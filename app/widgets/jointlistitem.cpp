#include "jointlistitem.h"
#include "ui_jointlistitem.h"

JointListItem::JointListItem(Joint** joint, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::JointListItem)
{
    ui->setupUi(this);
    m_joint = *joint;

    connect(m_joint, &Joint::settings_changed, this, &JointListItem::update);
    update();
}

JointListItem::~JointListItem()
{
    delete ui;
}

void JointListItem::update()
{
    ui->jointTypeLabel->setText(QString::number(m_joint->settings.joint.jointType));
    ui->nodeidLabel->setText(QString::number(m_joint->settings.joint.nodeId));
    ui->legNumberLabel->setText(QString::number(m_joint->settings.joint.legNumber));
}

void JointListItem::display_jointControlWidget()
{
    m_joint->display.show();
}
