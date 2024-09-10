#pragma once
#include "joint.h"
#include "FreckleProtocol.h"
#include "inverseKinematics.h"

class Leg
{

public:
    Leg(uint8_t legNumber = 0);
    ~Leg();



    void set_position(int x, int y, int z);
    void calibrate();
    uint8_t add_joint(Joint* joint);
    void set_joints(Joint* hipYaw, Joint* hipPitch, Joint* kneePitch);
    void set_enabled(uint8_t enabled);
    void enable() { set_enabled(1); }
    void disable() { set_enabled(0); }

    void command_allJoints(int command);
    void set_mode(int mode);
    void goto_home();

    bool check_joints();





protected:
    uint8_t m_legNumber;
    Joint* m_hipYaw;
    Joint* m_hipPitch;
    Joint* m_kneePitch;

private:
    IKParams_t m_ikParams;
    IKPoint_t m_ikPoint;
    IKAngles_t m_ikAngles;
    



};