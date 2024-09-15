#pragma once
#include <QObject>
#include "hexapod.h"
#include "QLeg.h"
#include <QThread>


class QHexapod : public QObject, public Hexapod
{
    Q_OBJECT

public:
    QHexapod();
    ~QHexapod();

    QLeg* get_leg(int legNumber);

    QLeg leg0 = QLeg(0);
    QLeg leg1 = QLeg(1);
    QLeg leg2 = QLeg(2);
    QLeg leg3 = QLeg(3);
    QLeg leg4 = QLeg(4);
    QLeg leg5 = QLeg(5);

    QThread legThreads[6];
    QThread jointsThread;

    void set_legPosition(uint8_t legNumber, int x, int y, int z) override;



public slots:
    void allocate_joints();
    void set_enabled(uint8_t enabled) { Hexapod::set_enabled(enabled); }
    void enable() { set_enabled(1); }
    void disable() { set_enabled(0); }
    void start_calibration();
    void leg_calibrationComplete() { calibrationStep++; };
    void set_allLegPositions(int x, int y, int z) {emit set_allLegPositionsSignal(x, y, z); }
    void step(int timeMs) {Hexapod::step(timeMs);}
    void start_stepping();
    void stop_stepping();
    void update();

signals:
    void calibration_complete();
    void set_allLegPositionsSignal(int x, int y, int z);


private: 
    QLeg* m_legs[6]; 

    QTimer calibrationTimer;
    int calibrationStep;
    void calibrate();

    QElapsedTimer time;
    QTimer refreshTimer;

    const int refreshRate = 20; // ms
};