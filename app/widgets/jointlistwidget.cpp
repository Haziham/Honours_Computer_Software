#include "jointlistwidget.h"

JointListWidget::JointListWidget(QWidget *parent) : QListWidget(parent)
{
    connect(this, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(display_jointListItem(QListWidgetItem*)));
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
            qDebug() << "Removing joint from widget";
            delete item(i);
        }
    }
}

void JointListWidget::add_jointToWidget(Joint *joint)
{
    QListWidgetItem *newItem = new QListWidgetItem();
    JointListItem *jointListItem = new JointListItem(&joint);
    newItem->setSizeHint(jointListItem->sizeHint());
    addItem(newItem);
    setItemWidget(newItem, jointListItem);  
    qDebug() << "Adding joint to widget";
}

void JointListWidget::display_jointListItem(QListWidgetItem* listWidgetItem)
{
    JointListItem *jointListItem = (JointListItem*)itemWidget(listWidgetItem);
    jointListItem->display_jointControlWidget();
}
