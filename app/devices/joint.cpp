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
    encodeStatusAPacketStructure(&canMessage, &statusA);
    can.request_CAN_message(&canMessage);
}

// Use commandModes enum from freckle_protocol.h
void Joint::set_mode(int mode)
{
    CommandSettings_t commandSettings;
    commandSettings.mode = mode;
    encodeCommandSettingsPacketStructure(&canMessage, &commandSettings);
    can.send_CAN_message(&canMessage);
    // can.send_and_request_CAN_message(&canMessage);
}

uint32_t map_value(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max) {
    return out_min +  (out_max - out_min) * ((double) (x - in_min) / (in_max - in_min));
}

void Joint::send_command(int value)
{
    JointCommand_t commandSettings;
    commandSettings.value = map_value(abs(value), 0, 100, 0, 65535);

    if (value < 0)
    {
        commandSettings.direction = DIR_BACKWARD;
    } else {
        commandSettings.direction = DIR_FORWARD;
    }

    CAN_Message_t message;
    encodeJointCommandPacketStructure(&message, &commandSettings);
    can.send_CAN_message(&message);
}