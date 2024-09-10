#pragma once
#include <QObject>
#include "hexapod.h"


class QHexapod : public QObject, public Hexapod
{
    Q_OBJECT

public:
    QHexapod();
    ~QHexapod();

};