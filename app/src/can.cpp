#include "can.hpp"
#include "JointsList.h"

FreckleCAN g_can;


void FreckleCAN::decode_CAN_frame(CAN_Message_t *message)
{
    uint8_t nodeID;
    Joint* joint;

    decode_nodeID(message, &nodeID);

    if (g_joints.get_joint(&joint, nodeID))
    {
        qDebug() << "Decoding ID: " <<  message->id <<  " packet to: " << nodeID;

        decode_packet(message, joint);
    }
    else {
        qDebug() << "Joint not found!";

        // Make new joint
        Joint* newJoint = new Joint(nodeID);

        g_joints.add_joint(newJoint); 
        decode_packet(message, newJoint);
    }
}


void FreckleCAN::decode_packet(CAN_Message_t *message, Joint* joint)
{
        // qDebug() << "Found joint!";
        if (decodeStatusAPacketStructure(message, &joint->settings.statusA) |
            decodeStatusBPacketStructure(message, &joint->settings.statusB) |
            decodeStatusCPacketStructure(message, &joint->settings.statusC) |
            decodeJointSettingsPacketStructure(message, &joint->settings.joint) |
            decodeTelemetrySettingsPacketStructure(message, &joint->settings.telemetry) |
            decodeCommandSettingsPacketStructure(message, &joint->settings.command))
        {
            // qDebug() << "Decoded packet!";
            joint->settings_changed();
        }
        else {
            qDebug() << "Unknown packet type!";
            qDebug() << "ID: " <<  QString::number(getFrecklePacketID(message), 16);
        }
}

// Extracts and removes the node ID from the CAN message ID
void FreckleCAN::decode_nodeID(CAN_Message_t *message, uint8_t *nodeID)
{
    *nodeID = (message->id & 0x001F);
    message->id = message->id >> 5;
}

