#pragma once
#include <QDebug>
#include "freckle_protocol.h"
#include "can.hpp"
#include "jointcontrolwidget.h"


#define ENABLE 1
#define DISABLE 0

#define ENABLED 1
#define DISABLED 0

class Joint : public QObject
{
    Q_OBJECT

public:

    Joint(uint8_t nodeId = 0);
    // ~Joint();
    
    JointControlWidget display = JointControlWidget(this); 


    struct {
        JointSettings_t joint;
        StatusA_t statusA;
        StatusB_t statusB;
        StatusC_t statusC;
        TelemetrySettings_t telemetry;
        CommandSettings_t command;
    } settings;


    void test_class();
    uint8_t get_nodeId() { return settings.joint.nodeId; }

signals:
    void settings_changed();    

public slots:
    void set_enabled(bool enabled);
    void set_mode(int mode); // Use commandModes enum from freckle_protocol.h
    void send_command(int value);
    void enable() { set_enabled(ENABLE); }
    void disable() { set_enabled(DISABLE); }

    void send_jointSettings(JointSettings_t settings);
    void send_telemetrySettings(TelemetrySettings_t settings);
    void send_commandSettings(CommandSettings_t settings);
    
    void send_CANMessage(CAN_Message_t *message);
    void request_CANMessage(CAN_Message_t *message);
    void send_and_request_CANMessage(CAN_Message_t *message);



private:
    CAN_Message_t canMessage;
};

// bool get_jointFromList(QList<Joint*> jointList, Joint* joint, uint8_t nodeId);
// void add_jointToList(QList<Joint*> jointList, Joint* joint);

// extern QList<Joint*> g_joints;
