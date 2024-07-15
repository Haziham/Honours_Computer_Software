#include "can.hpp"


Can can;


void Can::decode_CAN_frame(CAN_Message_t *message)
{
    if (decodeStatusAPacketStructure(message, &joint.statusA) |
        decodeStatusBPacketStructure(message, &joint.statusB) |
        decodeJointSettingsPacketStructure(message, &joint.jointSettings) |
        decodeTelemetrySettingsPacketStructure(message, &joint.telemetrySettings))
    {
        // qDebug() << "Decoded packet!";
    }
    else {
        qDebug() << "Unknown packet type!";
    }

}

void Can::send_and_request_CAN_message(CAN_Message_t *message)
{
    send_CAN_message(message);
    request_CAN_message(message);
}

void Can::request_CAN_message(CAN_Message_t *message)
{
    message->len = 0; // Signals a request
    send_CAN_message(message);
}
