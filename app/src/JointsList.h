#pragma once

#include "QJoint.h"
#include "QLeg.h"
#include <QObject>

class JointsList : public QObject
{
    Q_OBJECT

public:
    JointsList();
    bool get_joint(QJoint** joint, uint8_t nodeId);

    bool get_legJoints(QJoint** hipYawJoint, QJoint** hipPitchJoint, QJoint** kneePitchJoint, uint8_t legNumber);

    void add_joint(QJoint* joint);
    void remove_joint(int nodeId);
    

signals:
    void joint_added(QJoint* joint);
    void joint_removed(int nodeId);



private:
    QMap<int, QJoint*> m_joints;

};

extern JointsList g_joints;