#pragma once
#include "joint.h"

class Leg
{

public:
    Joint* hipYaw;
    Joint* hipPitch;
    Joint* kneePitch;
    uint8_t calibrated;



    void set_position(int x, int y, int z);
    void calibrate();


    Leg(uint8_t legNumber = 0);
    ~Leg();


private:
    uint8_t m_legNumber;
    



};