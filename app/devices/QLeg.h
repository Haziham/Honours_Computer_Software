#pragma once
#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QThread>
#include "JointsList.h" 
#include "QJoint.h"
#include  "leg.h" 

class JointsList;
class QJoint;

class QLeg : public QObject, public Leg
{
    Q_OBJECT

public:
    QLeg(uint8_t legNumber = 0);
    ~QLeg();

    uint8_t get_legNumber() { return m_legNumber; }
    void set_legNumber(uint8_t legNumber) { m_legNumber = legNumber; }
    void allocate_joints(QJoint *hipYaw, QJoint *hipPitch, QJoint *kneePitch);
    void allocate_jointsFromList(JointsList *jointsList);
    void get_joints(QJoint** hipYaw, QJoint** hipPitch, QJoint** kneePitch);

public slots:
    void start_calibration();
    void set_position(int x, int y, int z) { Leg::set_position(x, y, z); }

signals:
    void calibration_complete();




private:    
    QTimer calibrationTimer;
    int calibrationStep;
    int calibrationCount;
    bool calibrationCmdSent = false;
    void calibrate();

    QJoint* m_hipYaw;
    QJoint* m_hipPitch;
    QJoint* m_kneePitch;
};