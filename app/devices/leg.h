#pragma once
#include "joint.h"
#include "FreckleProtocol.h"
#include "inverseKinematics.h"

class Leg
{

public:
    uint8_t calibrated;



    void set_position(int x, int y, int z);
    void calibrate();
    uint8_t add_joint(Joint* joint);
    void set_joints(Joint* hipYaw, Joint* hipPitch, Joint* kneePitch);


    Leg(uint8_t legNumber = 0);
    ~Leg();


private:
    uint8_t m_legNumber;
    IKParams_t m_ikParams;
    IKPoint_t m_ikPoint;
    IKAngles_t m_ikAngles;
    

    Joint* m_hipYaw;
    Joint* m_hipPitch;
    Joint* m_kneePitch;


};