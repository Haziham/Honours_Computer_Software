#include "QJoint.h"

QJoint::QJoint(uint8_t nodeId) : Joint(nodeId)
{
    timeoutTimer.setSingleShot(true);
    timeoutTimer.setInterval(5000);
    connect(&timeoutTimer, &QTimer::timeout, this,  [this]() {
            qDebug() << "Joint " << settings.joint.nodeId << " timed out";
            emit jointDestroyed(settings.joint.nodeId);
            delete this;
        });


    if (nodeId != 0x1F)
    {
        timeoutTimer.start();
    }
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

