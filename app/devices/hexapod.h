#pragma once
#include "leg.h"


class Hexapod
{

public:
    Hexapod();
    ~Hexapod();

    void calibrate();


private:
    Leg m_legs[6];

};