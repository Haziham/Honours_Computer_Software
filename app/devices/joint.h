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

    JointSettings_t jointSettings;
    StatusA_t statusA;
    StatusB_t statusB;
    TelemetrySettings_t telemetrySettings;

public slots:
    void set_enabled(bool enabled);
    void set_mode(int mode); // Use commandModes enum from freckle_protocol.h
    void send_command(int value);
    void enable() { set_enabled(ENABLE); }
    void disable() { set_enabled(DISABLE); }

private:
    CAN_Message_t canMessage;
};


extern Joint joint;
