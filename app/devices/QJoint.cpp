#include "QJoint.h"

QJoint::QJoint(uint8_t nodeId) : Joint(nodeId)
{
    timeoutTimer.setSingleShot(true);
    timeoutTimer.setInterval(5000);
    connect(&timeoutTimer, &QTimer::timeout, this,  [this]() {
            qDebug() << "Joint " << settings.joint.nodeId << " timed out";
            emit jointDestroyed(settings.joint.nodeId);
        });


    if (nodeId != 0x1F)
    {
        // timeoutTimer.start();
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

void QJoint::startResolutionTest()
{
    resolutionTestTimer = new QTimer(this);
    connect(resolutionTestTimer, &QTimer::timeout, this, &QJoint::resolutionTest);
    resolutionTestStep = 0;
    resolutionTestTimer->setInterval(1000);
    resolutionTestTimer->start();
}

void QJoint::resolutionTest()
{
    QList<int> testValues = {-1000, -900, -800, -700, -600, -500, -400, -300, -200, -100, 0, 100, 200, 300, 400, 500, 600, 700, 800, 900, -900, 900, -900, -1001}; 

    if (resolutionTestStep > testValues.size())
    {
        resolutionTestTimer->stop();
        return;
    }

    send_command(testValues[resolutionTestStep]);
    resolutionTestStep++;
}
