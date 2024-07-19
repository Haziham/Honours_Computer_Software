#pragma once
#include <QDebug>
#include "freckle_protocol.h"
#include "can.hpp"

#define ENABLE 1
#define DISABLE 0

#define ENABLED 1
#define DISABLED 0

class Joint : public QObject
{
public:
    void test_class();

    struct {
        JointSettings_t joint;
        StatusA_t statusA;
        StatusB_t statusB;
        StatusC_t statusC;
        TelemetrySettings_t telemetry;
        CommandSettings_t command;
    } settings;
    

public slots:
    void set_enabled(bool enabled);
    void set_mode(int mode); // Use commandModes enum from freckle_protocol.h
    void send_command(int value);
    void enable() { set_enabled(ENABLE); }
    void disable() { set_enabled(DISABLE); }

    void send_jointSettings(JointSettings_t settings);
    void send_telemetrySettings(TelemetrySettings_t settings);
    void send_commandSettings(CommandSettings_t settings);
    


private:
    CAN_Message_t canMessage;
};


extern Joint joint;
