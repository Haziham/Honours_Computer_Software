#include "QLeg.h"

QLeg::QLeg(uint8_t legNumber) : Leg(legNumber)
{
    connect(&calibrationTimer, &QTimer::timeout, this, &QLeg::calibrate);

}

QLeg::~QLeg()
{
}


void QLeg::start_calibration()
{
    if (!check_joints())
    {
        // Do no calibrate if joints are not connected
        return;
    }
    calibrationStep = 0;
    calibrationTimer.start(1000);
}

void QLeg::calibrate()
{
    qDebug() << "Calibrating leg: " << m_legNumber;
    static bool calibrationCmdSent = false;
    Joint *joint = nullptr;

    switch (calibrationStep)
    {
    case 0:
        joint = m_kneePitch;
        break;
    case 1:
        m_kneePitch->send_command(0);
        joint = m_hipPitch;
        break;
    case 2:
        m_kneePitch->send_command(-900);
        m_hipPitch->goto_angleMax();
        joint = m_hipYaw;
        break;
    default:
        calibrationTimer.stop();
        goto_home();
        emit calibration_complete();
        return;
    }

    if (!joint->is_calibrated())
    {
        if (!calibrationCmdSent)
        {
            joint->calibrate();
            calibrationCmdSent = true;
        }
    }
    else {
        calibrationCmdSent = false;
        calibrationStep++;        
    }
}
