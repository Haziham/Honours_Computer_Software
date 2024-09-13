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

}

QHexapod::~QHexapod()
{
}

QLeg *QHexapod::get_leg(int legNumber)
{
    // return  _legs[legNumber];
}

void QHexapod::calibrate()
{
    leg0.start_calibration();
    leg2.start_calibration();
    leg4.start_calibration();
}
