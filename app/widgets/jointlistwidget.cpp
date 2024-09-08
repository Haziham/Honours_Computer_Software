#include "jointlistwidget.h"

JointListWidget::JointListWidget(QWidget *parent) : QListWidget(parent)
{
    // connect(this, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(display_jointListItem(QListWidgetItem*)));
}

void JointListWidget::assign_joints(JointsList *joints)
{
    m_joints = joints; 

    connect(m_joints, &JointsList::joint_added, this, &JointListWidget::add_jointToWidget);
    connect(m_joints, &JointsList::joint_removed, this, &JointListWidget::remove_jointFromWidget);
}

void JointListWidget::remove_jointFromWidget(int nodeId)
{
    for (int i = 0; i < count(); i++) 
    {
        JointListItem *jointListItem = (JointListItem*)itemWidget(item(i));
        if (jointListItem->get_nodeId() == nodeId)
        {
            qDebug() << "Removing joint from widget: " << nodeId;
            delete item(i);
        }
    }
}

void JointListWidget::add_jointToWidget(QJoint *joint)
{
    QListWidgetItem *newItem = new QListWidgetItem();
    JointListItem *jointListItem = new JointListItem(nullptr, joint);
    newItem->setSizeHint(jointListItem->sizeHint());
    newItem->setData(Qt::UserRole, joint->get_nodeId());
    int currentNodeId = joint->get_nodeId();
    bool inserted = false;

    // Insert the new joint in the correct order
    for (int i = 0; i < count(); i++) 
    {
        JointListItem *jointListItem = (JointListItem*)itemWidget(item(i));
        if (jointListItem->get_nodeId() > currentNodeId)
        {
            insertItem(i, newItem);
            inserted = true;
        }
    }

    if (!inserted)
    {
        addItem(newItem);
    }
    setItemWidget(newItem, jointListItem);  
}

void JointListWidget::display_jointListItem(QListWidgetItem* listWidgetItem)
{
    JointListItem *jointListItem = (JointListItem*)itemWidget(listWidgetItem);
    JointControlWidget *jointControlWidget = new JointControlWidget(jointListItem->get_joint());
    jointControlWidget->show();
    jointListItem->display_jointControlWidget();
    jointListItem->get_joint()->request_settings();
}
