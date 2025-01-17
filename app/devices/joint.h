#pragma once
#include "freckle_protocol.h"
#include "canQueue.h"

#define ENABLE 1
#define DISABLE 0

#define ENABLED 1
#define DISABLED 0


class Joint 
{

public:

    Joint(uint8_t nodeId = 0);
    // ~Joint();
    
    // JointControlWidget display = JointControlWidget(this); 



    StatusA_t statusA;
    StatusB_t statusB;
    StatusC_t statusC;
    struct {
        JointSettings_t joint;
        TelemetrySettings_t telemetry;
        CommandSettings_t command;
        CalibrationSettings_t calibration;
        ControlSettings_t control;
        MotorSettings_t motor;
        struct {
            int32_t targetCommand;
        } internal;
    } settings;


    uint8_t get_nodeId() { return settings.joint.nodeId; }
    uint8_t get_legNumber() { return settings.joint.legNumber; }
    uint8_t get_jointType() { return settings.joint.jointType; }
    uint16_t get_minAngle() { return settings.calibration.minAngle; }
    uint16_t get_maxAngle() { return settings.calibration.maxAngle; }
    
    uint16_t get_externalADC() { return statusB.externalADC; }


    void goto_angleMin() { send_command(settings.calibration.minAngle); }
    void goto_angleMax() { send_command(settings.calibration.maxAngle); }
    void goto_home();

    void set_enabled(bool enabled);
    void set_mode(int mode); // Use commandModes enum from freckle_protocol.h
    void send_command(int value);
    void enable() { set_enabled(ENABLE); }
    void disable() { set_enabled(DISABLE); }

    void toggle_debugMode();
    void zero_force();


    void calibrate();
    uint8_t is_calibrating() {return statusA.calibrating;};
    uint8_t is_calibrated() {return statusA.calibrated;};

    float get_force() {return statusB.externalADC;};

    void send_jointSettings(JointSettings_t settings);
    void send_telemetrySettings(TelemetrySettings_t settings);
    void send_commandSettings(CommandSettings_t settings);
    void send_controlSettings(ControlSettings_t settings);
    void send_calibrationSettings(CalibrationSettings_t settings);
    void send_motorSettings(MotorSettings_t settings);
    
    virtual void send_CANMessage(CAN_Message_t message);
    void request_CANMessage(CAN_Message_t message);
    void send_and_request_CANMessage(CAN_Message_t message);

    void request_settings();

private:
    CAN_Message_t canMessage;


    
};

// bool get_jointFromList(QList<Joint*> jointList, Joint* joint, uint8_t nodeId);
// void add_jointToList(QList<Joint*> jointList, Joint* joint);

// extern QList<Joint*> g_joints;
