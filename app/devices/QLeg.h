#pragma once
#include <QObject>
#include "leg.h"
#include "joint.h"

class QLeg : public QObject, public Leg
{
    Q_OBJECT

public:
    QLeg(uint8_t legNumber = 0);
    ~QLeg();

    uint8_t get_legNumber() { return m_legNumber; }


private:    
    uint8_t m_legNumber;
};