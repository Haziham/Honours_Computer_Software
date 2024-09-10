#pragma once
#include <QObject>
#include <QDebug>
#include <QTimer>
#include "leg.h"

class QLeg : public QObject, public Leg
{
    Q_OBJECT

public:
    QLeg(uint8_t legNumber = 0);
    ~QLeg();

    uint8_t get_legNumber() { return m_legNumber; }
    void set_legNumber(uint8_t legNumber) { m_legNumber = legNumber; }

public slots:
    void start_calibration();

signals:
    void calibration_complete();




private:    
    QTimer calibrationTimer;
    int calibrationStep;
    void calibrate();

};