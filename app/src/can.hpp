#pragma once

#include "usb2can.hpp"
#include "joint.h"

class Can : public USB2CAN
{

public slots:
    void decode_CAN_frame(CAN_Message_t *message) override;

};

extern Can can;