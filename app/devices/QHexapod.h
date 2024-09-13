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



public slots:
    void calibrate();

private: 
    // QLeg* m_legs[6] = {&leg1, &leg2, &leg3, &leg4, &leg5, &leg6}; 
};