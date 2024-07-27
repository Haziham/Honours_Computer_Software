#include "JointsList.h"

JointsList g_joints;

JointsList::JointsList()
{
}

void JointsList::add_joint(Joint *joint)
{
    m_joints.insert(joint->get_nodeId(), joint);
    emit joint_added(joint);
}


bool JointsList::get_joint(Joint **joint, uint8_t nodeId)
{
    if (m_joints.contains(nodeId))
    {
        *joint = m_joints.value(nodeId);
        return true;
    }
    return false;
}

void JointsList::remove_joint(int nodeId)
{
    m_joints.remove(nodeId);
    emit joint_removed(nodeId);
}


