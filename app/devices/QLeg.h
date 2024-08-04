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

private:    
};