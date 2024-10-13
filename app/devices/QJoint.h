#pragma once
#include <QObject>
#include <QTimer>
#include "can.hpp"
#include <unordered_set>

class QJoint : public QObject, public Joint
{
    Q_OBJECT

public:

    QJoint(uint8_t nodeId = 0);
    ~QJoint();
    
    void send_CANMessage(CAN_Message_t message) override;

signals:
    void settings_changed();    
    void jointDestroyed(int nodeId);

public slots: 
    void set_modeSlot(uint8_t mode) { set_mode(mode); }
    void enableSlot() { enable(); }
    void disableSlot() { disable(); }
    void toggle_debugMode() { Joint::toggle_debugMode(); }
    void zero_force() { Joint::zero_force(); }  
    void send_commandSlot(int command) { send_command(command); }
    void resetTimeout() { /*timeoutTimer.start();*/ }
    void startResolutionTest(); 
    void resolutionTest();
    // void update_settings();



private:


    CAN_Message_t canMessage;
    QTimer timeoutTimer;
    QTimer* resolutionTestTimer;
    int resolutionTestStep = 0;
};

// bool get_jointFromList(QList<Joint*> jointList, Joint* joint, uint8_t nodeId);
// void add_jointToList(QList<Joint*> jointList, Joint* joint);

// extern QList<Joint*> g_joints;
