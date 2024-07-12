#include "can.hpp"


Can can;


void Can::decode_CAN_frame(CAN_Message_t *message)
{
    if (decodeStatusAPacketStructure(message, &joint.statusA) |
        decodeStatusBPacketStructure(message, &joint.statusB) |
        decodeJointSettingsPacketStructure(message, &joint.jointSettings) |
        decodeTelemetrySettingsPacketStructure(message, &joint.telemetrySettings))
    {
        qDebug() << "Decoded packet!";
    }
    else {
        qDebug() << "Unknown packet type!";
    }

}