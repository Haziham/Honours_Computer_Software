#include "JointsList.h"

JointsList g_joints;

JointsList::JointsList()
{
}

void JointsList::add_joint(QJoint *joint)
{
    connect(joint, &QJoint::jointDestroyed, this, &JointsList::remove_joint);
    jointListMutex.lock();
    m_joints.insert(joint->get_nodeId(), joint);
    jointListMutex.unlock();
    emit joint_added(joint);
}


bool JointsList::get_joint(QJoint **joint, uint8_t nodeId)
{
    bool found = false;
    jointListMutex.lock();
    if (m_joints.contains(nodeId))
    {
        *joint = m_joints.value(nodeId);
        found = true;
    }
    jointListMutex.unlock();
    return found;
}

bool JointsList::get_legJoints(QJoint** hipYawJoint, QJoint** hipPitchJoint, QJoint** kneePitchJoint, uint8_t legNumber)
{
    jointListMutex.lock();
    for (QJoint* joint : m_joints)
    {
        if (joint->get_legNumber() == legNumber)
        {
            switch (joint->get_jointType())
            {
                case JOINT_HIP_YAW:
                    *hipYawJoint = joint;
                    break;
                case JOINT_HIP_PITCH:
                    *hipPitchJoint = joint;
                    break;
                case JOINT_KNEE_PITCH:
                    *kneePitchJoint = joint;
                    break;
            }
        }
    }
    jointListMutex.unlock();
    return true;
}

void JointsList::remove_joint(int nodeId)
{
    jointListMutex.lock();
    m_joints.remove(nodeId);
    jointListMutex.unlock();
    emit joint_removed(nodeId);
}


