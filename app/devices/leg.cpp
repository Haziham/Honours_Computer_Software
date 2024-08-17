#include "leg.h"

Leg::Leg(uint8_t legNumber)
{
    m_legNumber = legNumber;

    m_ikParams.invert = false;
    m_ikParams.joint1Length = 0;
    m_ikParams.joint2Length = 0.1;
    m_ikParams.joint3Length = 0.1; 
}

void Leg::set_position(int x, int y, int z)
{

    m_ikPoint.x = x/1000.0;
    m_ikPoint.y = y/1000.0;
    m_ikPoint.z = z/1000.0;

    inverseKinematics(&m_ikParams, &m_ikPoint, &m_ikAngles);

    // convert angles to degrees and multiply by 10
    m_ikAngles.hipYaw = m_ikAngles.hipYaw * 180 / M_PI * 10;
    m_ikAngles.hipPitch = m_ikAngles.hipPitch * 180 / M_PI * 10;
    m_ikAngles.kneePitch = m_ikAngles.kneePitch * 180 / M_PI * 10;

    // print
    fprintf(stderr, "Leg %d: %d %d %d\n", m_legNumber, (int)m_ikAngles.hipYaw, (int)m_ikAngles.hipPitch, (int)m_ikAngles.kneePitch);




    m_hipYaw->send_command((int)m_ikAngles.hipYaw);
    m_hipPitch->send_command((int)m_ikAngles.hipPitch);
    // m_kneePitch->send_command((int)m_ikAngles.kneePitch);
}

uint8_t Leg::add_joint(Joint *joint)
{
    switch (joint->get_jointType())
    {
    case JOINT_HIP_YAW:
        m_hipYaw = joint;
        break;
    case JOINT_HIP_PITCH:
        m_hipPitch = joint;
        break;
    case JOINT_KNEE_PITCH:
        m_kneePitch = joint;
        break;
    default:
        return 0;    
        break;
    }
    return 1;
}



void Leg::set_joints(Joint *hipYaw, Joint *hipPitch, Joint *kneePitch)
{
    m_hipYaw = hipYaw;
    m_hipPitch = hipPitch;
    m_kneePitch = kneePitch;
}

Leg::~Leg()
{
}