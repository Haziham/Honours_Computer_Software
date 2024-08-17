#include "joint.h"
#include "canQueue.h"

// list<Joint*> g_joints;

Joint::Joint(uint8_t nodeId)
{
    // Set all settings to 0
    for (int i = 0; i < sizeof(settings); i++)
    {
        ((uint8_t*)&settings)[i] = 0;
    }

    settings.joint.nodeId = nodeId;
}  


void Joint::set_enabled(bool enabled)
{
    encodeEnablePacket(&canMessage, enabled);
    send_CANMessage(canMessage);
    encodeStatusAPacketStructure(&canMessage, &statusA);
    request_CANMessage(canMessage);
}

// Use commandModes enum from freckle_protocol.h
void Joint::set_mode(int mode)
{
    CommandSettings_t commandSettings;
    // commandSettings.mode = mode;
    encodeCommandSettingsPacketStructure(&canMessage, &commandSettings);
    send_and_request_CANMessage(canMessage);
}

int map_value(int x, int in_min, int in_max, int out_min, int out_max) {
    return out_min +  (out_max - out_min) * ((double) (x - in_min) / (in_max - in_min));
}

void Joint::send_command(int value)
{
    CAN_Message_t message;
    // JointCommand_t command;

    // switch (settings.command.mode)
    // {
    // case CMD_PWM:
    //     command.value = map_value(value, -100, 100, -65535, 65535);
    //     break;
    // case CMD_POSITION:
    //     command.value = map_value(value, -100, 100, -1800, 1800);
    //     break;
    // case CMD_VELOCITY:
    // case CMD_TORQUE:
    // default:
    //     command.value = 0;
    //     break;
    // }


    // commandSettings.value = map_value(abs(value), 0, 100, 0, 65535);
    // encodeJointCommandPacketStructure(&message, &command);
    encodeJointCommandPacket(&message, value);
    send_CANMessage(message);
}

void Joint::send_jointSettings(JointSettings_t settings)
{
    encodeJointSettingsPacketStructure(&canMessage, &settings);
    send_and_request_CANMessage(canMessage);
}

void Joint::send_telemetrySettings(TelemetrySettings_t settings)
{
    encodeTelemetrySettingsPacketStructure(&canMessage, &settings);
    send_and_request_CANMessage(canMessage);
}

void Joint::send_commandSettings(CommandSettings_t settings)
{
    encodeCommandSettingsPacketStructure(&canMessage, &settings);
    send_and_request_CANMessage(canMessage);
}

void Joint::send_controlSettings(ControlSettings_t settings)
{
    encodeControlSettingsPacketStructure(&canMessage, &settings);
    send_and_request_CANMessage(canMessage);
}

void Joint::send_calibrationSettings(CalibrationSettings_t settings)
{
    encodeCalibrationSettingsPacketStructure(&canMessage, &settings);
    send_and_request_CANMessage(canMessage);
}

void Joint::send_CANMessage(CAN_Message_t message)
{
    // message.id <<= 5;
    // message.id |= settings.joint.nodeId;
    // g_can.send_CAN_message(&message);
}

void Joint::request_CANMessage(CAN_Message_t message)
{
    message.len = 0; // Signals a request
    send_CANMessage(message);
}

void Joint::send_and_request_CANMessage(CAN_Message_t message)
{
    send_CANMessage(message);
    request_CANMessage(message);
}

void Joint::request_settings()
{
    canMessage.id = PKT_JOINT_SETTINGS;
    request_CANMessage(canMessage);
    canMessage.id = PKT_COMMAND_SETTINGS;
    request_CANMessage(canMessage);
    canMessage.id = PKT_TELEMETRY_SETTINGS;
    request_CANMessage(canMessage);
    canMessage.id = PKT_CALIBRATION_SETTINGS;
    request_CANMessage(canMessage);
    canMessage.id = PKT_CONTROL_SETTINGS;
    request_CANMessage(canMessage);
}

// bool get_jointFromList(QList<Joint*> jointList, Joint* joint, uint8_t nodeId)
// {
//     for (Joint* j : jointList)
//     {
//         if (j->get_nodeId() == nodeId)
//         {
//             joint = j;
//             return true;
//         }
//     }

//     return false;
// }

// void add_jointToList(QList<Joint *> jointList, Joint *joint)
// {
//     jointList.push_back(joint);
// }
