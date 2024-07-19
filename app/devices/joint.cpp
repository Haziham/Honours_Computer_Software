#include "joint.h"
#include "canQueue.h"

Joint joint;

void Joint::test_class()
{
    qDebug() << "Hello from RC_Car class!";
}

void Joint::set_enabled(bool enabled)
{
    encodeEnablePacket(&canMessage, enabled);
    can.send_CAN_message(&canMessage);
    encodeStatusAPacketStructure(&canMessage, &settings.statusA);
    can.request_CAN_message(&canMessage);
}

// Use commandModes enum from freckle_protocol.h
void Joint::set_mode(int mode)
{
    CommandSettings_t commandSettings;
    commandSettings.mode = mode;
    encodeCommandSettingsPacketStructure(&canMessage, &commandSettings);
    can.send_and_request_CAN_message(&canMessage);
}

int map_value(int x, int in_min, int in_max, int out_min, int out_max) {
    return out_min +  (out_max - out_min) * ((double) (x - in_min) / (in_max - in_min));
}

void Joint::send_command(int value)
{
    JointCommand_t command;
    CAN_Message_t message;

    switch (settings.command.mode)
    {
    case CMD_PWM:
        command.value = map_value(value, -100, 100, -65535, 65535);
        break;
    case CMD_POSITION:
        command.value = map_value(value, -100, 100, -1800, 1800);
        break;
    case CMD_VELOCITY:
    case CMD_TORQUE:
    default:
        command.value = 0;
        break;
    }


    // commandSettings.value = map_value(abs(value), 0, 100, 0, 65535);

    encodeJointCommandPacketStructure(&message, &command);
    can.send_CAN_message(&message);
}

void Joint::send_jointSettings(JointSettings_t settings)
{
    encodeJointSettingsPacketStructure(&canMessage, &settings);
    can.send_and_request_CAN_message(&canMessage);
}

void Joint::send_telemetrySettings(TelemetrySettings_t settings)
{
    encodeTelemetrySettingsPacketStructure(&canMessage, &settings);
    can.send_and_request_CAN_message(&canMessage);
}

void Joint::send_commandSettings(CommandSettings_t settings)
{
    encodeCommandSettingsPacketStructure(&canMessage, &settings);
    can.send_and_request_CAN_message(&canMessage);
}
