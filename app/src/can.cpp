#include "can.hpp"


Can can;


void Can::decode_CAN_frame(CAN_Message_t *message)
{
    if (decodeStatusAPacketStructure(message, &joint.settings.statusA) |
        decodeStatusBPacketStructure(message, &joint.settings.statusB) |
        decodeStatusCPacketStructure(message, &joint.settings.statusC) |
        decodeJointSettingsPacketStructure(message, &joint.settings.joint) |
        decodeTelemetrySettingsPacketStructure(message, &joint.settings.telemetry) |
        decodeCommandSettingsPacketStructure(message, &joint.settings.command))
    {
        // qDebug() << "Decoded packet!";
    }
    else {
        qDebug() << "Unknown packet type!";
        // print packet id in hex
        qDebug() << "ID: " <<  QString::number(getFrecklePacketID(message), 16);
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
