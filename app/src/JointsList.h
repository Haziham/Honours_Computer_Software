#pragma once

#include "joint.h"
#include <QObject>

class JointsList : public QObject
{
    Q_OBJECT

public:
    JointsList();
    bool get_joint(Joint** joint, uint8_t nodeId);

    void add_joint(Joint* joint);
    void remove_joint(int nodeId);

signals:
    void joint_added(Joint* joint);
    void joint_removed(int nodeId);



private:
    QMap<int, Joint*> m_joints;

};

extern JointsList g_joints;