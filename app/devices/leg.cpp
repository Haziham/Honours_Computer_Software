#include "leg.h"

uint8_t Leg::add_joint(Joint *joint)
{
    switch (joint->get_jointType())
    {
    case JOINT_HIP_YAW:
        hipYaw = joint;
        break;
    case JOINT_HIP_PITCH:
        hipPitch = joint;
        break;
    case JOINT_KNEE_PITCH:
        kneePitch = joint;
        break;
    default:
        return 0;    
        break;
    }
    return 1;
}

Leg::Leg(uint8_t legNumber)
{
    m_legNumber = legNumber;

}

Leg::~Leg()
{
}
