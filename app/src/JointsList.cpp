#include "JointsList.h"

JointsList g_joints;

JointsList::JointsList()
{
}

void JointsList::add_joint(QJoint *joint)
{
    m_joints.insert(joint->get_nodeId(), joint);
    emit joint_added(joint);
}


bool JointsList::get_joint(QJoint **joint, uint8_t nodeId)
{
    if (m_joints.contains(nodeId))
    {
        *joint = m_joints.value(nodeId);
        return true;
    }
    return false;
}

bool JointsList::get_legJoints(QJoint** hipYawJoint, QJoint** hipPitchJoint, QJoint** kneePitchJoint, uint8_t legNumber)
{
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
    return true;
}

void JointsList::remove_joint(int nodeId)
{
    m_joints.remove(nodeId);
    emit joint_removed(nodeId);
}


