#include "QHexapod.h"



QHexapod::QHexapod()
{
    // for (int i = 0; i < 6; i++)
    // {
    //     m_legs[i].set_legNumber(i);
    // }
    // move each leg to its on thread

    leg0.moveToThread(&legThreads[0]);
    leg1.moveToThread(&legThreads[1]);
    leg2.moveToThread(&legThreads[2]);
    leg3.moveToThread(&legThreads[3]);
    leg4.moveToThread(&legThreads[4]);
    leg5.moveToThread(&legThreads[5]);

    for (int i = 0; i < 6; i++)
    {
        legThreads[i].start();
    }

    // m_legs = {&leg0, &leg1, &leg2, &leg3, &leg4, &leg5};

    m_legs[0] = &leg0;
    m_legs[1] = &leg1;
    m_legs[2] = &leg2;
    m_legs[3] = &leg3;
    m_legs[4] = &leg4;
    m_legs[5] = &leg5;

    for (int i = 0; i < 6; i++)
    {
        connect(m_legs[i], &QLeg::calibration_complete, this, &QHexapod::leg_calibrationComplete);
        connect(this, &QHexapod::set_allLegPositionsSignal, m_legs[i], &QLeg::set_position);
    }

    Hexapod::allocate_legs(&leg0, &leg1, &leg2, &leg3, &leg4, &leg5);

    connect(&g_joints, &JointsList::joint_added, this, &QHexapod::allocate_joints);
    connect(&calibrationTimer, &QTimer::timeout, this, &QHexapod::calibrate);



    allocate_joints();
}

QHexapod::~QHexapod()
{
}

QLeg *QHexapod::get_leg(int legNumber)
{
    // return  _legs[legNumber];
    return nullptr;
}

void QHexapod::allocate_joints()
{
    for (int i = 0; i < 6; i++)
    {
        m_legs[i]->allocate_jointsFromList(&g_joints);
    }
}


void QHexapod::start_calibration()
{
    qDebug() << "Starting hexapod calibration";
    calibrationStep = 0;
    calibrationTimer.start(100);
}


void QHexapod::calibrate()
{
    switch (calibrationStep)
    {
    case 0:
        qDebug() << "Calibrating leg 0";
        leg0.start_calibration();
        leg2.start_calibration();
        leg4.start_calibration();
        calibrationStep++;
        break;
    case 4:
        qDebug() << "Calibrating leg 1";
        leg1.start_calibration();
        leg3.start_calibration();
        leg5.start_calibration();
        calibrationStep++;
        break;
    case 8:
        qDebug() << "Hexapod calibration complete";
        calibrationTimer.stop();
        emit calibration_complete();
        break;
    default:
        return;
    }

}