#include "QLeg.h"

QLeg::QLeg(uint8_t legNumber) : Leg(legNumber)
{

}

QLeg::~QLeg()
{
}

void QLeg::allocate_jointsFromList(JointsList *jointsList)
{
    QJoint* hipYawJoint = nullptr;
    QJoint* hipPitchJoint = nullptr;
    QJoint* kneePitchJoint = nullptr;

    // qDebug() << "Allocating joints: " << QString::number(get_legNumber());
    jointsList->get_legJoints(&hipYawJoint, &hipPitchJoint, &kneePitchJoint, get_legNumber());

    if (hipYawJoint != nullptr || hipPitchJoint != nullptr || kneePitchJoint != nullptr)
    {
        // qDebug() << "No Joints Found";
    }

    allocate_joints(hipYawJoint, hipPitchJoint, kneePitchJoint);
}

void QLeg::get_joints(QJoint **hipYaw, QJoint **hipPitch, QJoint **kneePitch)
{
    *hipYaw = m_hipYaw;
    *hipPitch = m_hipPitch;
    *kneePitch = m_kneePitch;
}

void QLeg::allocate_joints(QJoint *hipYaw, QJoint *hipPitch, QJoint *kneePitch) 
{
    m_hipYaw = hipYaw;
    m_hipPitch = hipPitch;
    m_kneePitch = kneePitch;
    Leg::allocate_joints(m_hipYaw, m_hipPitch, m_kneePitch);
}

void QLeg::start_calibration()
{
    qDebug() << "Thread: " << QThread::currentThread()->objectName();
    calibrationTimer = new QTimer();
    connect(calibrationTimer, &QTimer::timeout, this, &QLeg::calibrate);
    if (!check_joints())
    {
        // Do no calibrate if joints are not connected
        return;
    }
    calibrationStep = 0;
    calibrationCmdSent = false;
    calibrationCount = 0;
    calibrationTimer->start(100);

}

void QLeg::calibrate()
{
    qDebug() << "Calibrating leg: " << m_legNumber << " Step: " << calibrationStep << " Thread: " << QThread::currentThreadId() 
        << " CmdSent: " << calibrationCmdSent;
    Joint *joint = nullptr;

    switch (calibrationStep)
    {
    case 0:
        joint = m_kneePitch;
        break;
    case 1:
        joint = m_hipPitch;
        calibrationCount++;
        if (calibrationCount > 40)
        {
            m_kneePitch->goto_angleMin();
        }
        else {
            m_kneePitch->goto_angleMax();
        }
        break;
    case 2:
        m_kneePitch->send_command(-900);
        m_hipPitch->goto_angleMax();
        joint = m_hipYaw;
        break;
    default:
        calibrationTimer->stop();
        goto_home();
        emit calibration_complete();
        return;
    }

    if (!joint->is_calibrated())
    {
        if (!calibrationCmdSent)
        {
            qDebug() << "Calibrating joint: " << joint->get_nodeId();
            joint->calibrate();
            calibrationCmdSent = true;
        }


    }
    else {
        calibrationCmdSent = false;
        calibrationStep++;        
    }
}
