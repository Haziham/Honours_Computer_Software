#include "jointlistitem.h"
#include "ui_jointlistitem.h"

JointListItem::JointListItem(QWidget *parent, QJoint* joint)
    : QWidget(parent)
    , ui(new Ui::JointListItem)
{
    ui->setupUi(this);
    m_joint = joint;

    if (!m_joint) {
        display_noJoint();
        return;
    }
    connect(m_joint, &QJoint::settings_changed, this, &JointListItem::update, Qt::QueuedConnection);
    // on double click of widget, call display_jointControlWidget
    connect(this, &JointListItem::doubleClicked, this, &JointListItem::display_jointControlWidget);
    update();
}

JointListItem::~JointListItem()
{
    delete ui;
}

void JointListItem::set_joint(QJoint *joint)
{
    m_joint = joint;
    if (!m_joint) {
        display_noJoint();
        return;
    }
    connect(m_joint, &QJoint::settings_changed, this, &JointListItem::update, Qt::QueuedConnection);
    connect(this, &JointListItem::doubleClicked, this, &JointListItem::display_jointControlWidget);
    update();
}

void JointListItem::update()
{
    if (!m_joint) {
        display_noJoint();
        return;
    }
    ui->jointTypeLabel->setText(QString::number(m_joint->settings.joint.jointType));
    ui->nodeidLabel->setText(QString::number(m_joint->settings.joint.nodeId));
    ui->legNumberLabel->setText(QString::number(m_joint->settings.joint.legNumber));
    ui->enableIcon->setEnabled(m_joint->statusA.enabled);
}

void JointListItem::display_jointControlWidget()
{
    JointControlWidget *jointControlWidget = new JointControlWidget(m_joint);
    jointControlWidget->show();
    m_joint->request_settings();
}

void JointListItem::display_noJoint()
{
    ui->nodeidLabel->setText("N/A");
    ui->legNumberLabel->setText("N/A");
    ui->jointTypeLabel->setText("N/A");
    ui->enableIcon->setEnabled(false);
}
