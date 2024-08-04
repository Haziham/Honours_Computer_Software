#include "QJoint.h"

QJoint::QJoint(uint8_t nodeId) : Joint(nodeId)
{
}

QJoint::~QJoint() 
{
}


void QJoint::send_CANMessage(CAN_Message_t message)
{
    message.id <<= 5;
    message.id |= settings.joint.nodeId;
    g_can.send_CAN_message(&message);
}
