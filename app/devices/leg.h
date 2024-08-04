#pragma once
#include "joint.h"
#include "FreckleProtocol.h"

class Leg
{

public:
    Joint* hipYaw;
    Joint* hipPitch;
    Joint* kneePitch;
    uint8_t calibrated;



    void set_position(int x, int y, int z);
    void calibrate();
    uint8_t add_joint(Joint* joint);


    Leg(uint8_t legNumber = 0);
    ~Leg();


private:
    uint8_t m_legNumber;
    



};