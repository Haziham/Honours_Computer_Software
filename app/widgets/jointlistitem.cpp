#include "jointlistitem.h"
#include "ui_jointlistitem.h"

JointListItem::JointListItem(QJoint* joint, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::JointListItem)
{
    ui->setupUi(this);
    m_joint = joint;


    // if (m_joint) {
    //     connect(m_joint, &Joint::settings_changed, this, &JointListItem::update);
    //     update();
    // } else {
    //     // Handle the error: joint is null
    //     qWarning() << "Joint pointer is null!";
    // }
    connect(m_joint, &QJoint::settings_changed, this, &JointListItem::update, Qt::QueuedConnection);
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
    ui->enableIcon->setEnabled(m_joint->statusA.enabled);
}

void JointListItem::display_jointControlWidget()
{
    // m_joint->display.show();
}
