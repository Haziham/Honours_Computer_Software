#include "can.hpp"

FreckleCAN g_can;


void FreckleCAN::decode_CAN_frame(CAN_Message_t *message)
{
    uint8_t nodeID;
    QJoint* joint;

    decode_nodeID(message, &nodeID);

    uint16_t packetType = message->id;


    // qDebug() << "NodeID: " << QString::number(nodeID) << " PacketType: " << QString::number(packetType);

    if (g_joints.get_joint(&joint, nodeID))
    {
        // qDebug() << "Decoding ID: " <<  message->id <<  " packet to: " << nodeID;


        decode_packet(message, joint);
        joint->resetTimeout();

    }
    else {
        qDebug() << "New Joint! Thread: " << QThread::currentThread()->objectName();

        // Make new joint
        QJoint* newJoint = new QJoint(nodeID);

        decode_packet(message, newJoint);
        g_joints.add_joint(newJoint); 
        qDebug() << "Requesting settings for joint: " << newJoint->settings.joint.nodeId;
        // newJoint->request_settings();
    }
}


void FreckleCAN::decode_packet(CAN_Message_t *message, QJoint* joint)
{
        // qDebug() << "Found joint!";
        if (decodeStatusAPacketStructure(message, &joint->statusA) |
            decodeStatusBPacketStructure(message, &joint->statusB) |
            decodeStatusCPacketStructure(message, &joint->statusC) |
            decodeJointSettingsPacketStructure(message, &joint->settings.joint) |
            decodeTelemetrySettingsPacketStructure(message, &joint->settings.telemetry) |
            decodeCommandSettingsPacketStructure(message, &joint->settings.command) |
            decodeCalibrationSettingsPacketStructure(message, &joint->settings.calibration) |
            decodeControlSettingsPacketStructure(message, &joint->settings.control) | 
            decodeMotorSettingsPacketStructure(message, &joint->settings.motor))

        {
            // qDebug() << "Decoded packet!";
            joint->settings_changed();
        }
        else {
            qDebug() << "Unknown packet type!";
            qDebug() << "ID: " <<  QString::number(getFrecklePacketID(message), 16);
            qDebug() << "ID: " <<  QString::number(getFrecklePacketID(message));
        }
}

// Extracts and removes the node ID from the CAN message ID
void FreckleCAN::decode_nodeID(CAN_Message_t *message, uint8_t *nodeID)
{
    *nodeID = (message->id & 0x001F);
    message->id = message->id >> 5;
}

