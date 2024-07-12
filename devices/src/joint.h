#pragma once
#include <QDebug>
#include "freckle_protocol.h"


class Joint {
public:
    void test_class();

    JointSettings_t jointSettings;
    StatusA_t statusA;
    StatusB_t statusB;
    TelemetrySettings_t telemetrySettings;
};


extern Joint joint;
