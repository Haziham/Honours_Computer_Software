#pragma once

#include <QWidget>
#include <QListWidget>
#include "joint.h"
#include "jointlistitem.h"
#include "jointcontrolwidget.h"
#include "JointsList.h"

class JointListWidget : public QListWidget
{
    Q_OBJECT

public:
    explicit JointListWidget(QWidget *parent = nullptr);

    public:
        void assign_joints(JointsList* joints); 

    private:
        JointsList* m_joints;

        void remove_jointFromWidget(int nodeId);
        void add_jointToWidget(QJoint* joint);

    private slots:
        void display_jointListItem(QListWidgetItem* listWidgetItem);
};
