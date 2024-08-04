#pragma once
#include <QObject>
#include "can.hpp"

class QJoint : public QObject, public Joint
{
    Q_OBJECT

public:

    QJoint(uint8_t nodeId = 0);
    ~QJoint();
    
    void send_CANMessage(CAN_Message_t message) override;

signals:
    void settings_changed();    

public slots: 
    void set_modeSlot(uint8_t mode) { set_mode(mode); }
    void enableSlot() { enable(); }
    void disableSlot() { disable(); }
    void send_commandSlot(int command) { send_command(command); }



private:
    CAN_Message_t canMessage;
};

// bool get_jointFromList(QList<Joint*> jointList, Joint* joint, uint8_t nodeId);
// void add_jointToList(QList<Joint*> jointList, Joint* joint);

// extern QList<Joint*> g_joints;
