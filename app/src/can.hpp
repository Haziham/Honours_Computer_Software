#pragma once

#include "usb2can.hpp"
#include "joint.h"

class Joint; // Forward declaration

class FreckleCAN : public USB2CAN
{

public:
    void send_and_request_CAN_message(CAN_Message_t *message);
    void request_CAN_message(CAN_Message_t *message);


public slots:
    void decode_CAN_frame(CAN_Message_t *message) override;


private:
    void decode_nodeID(CAN_Message_t *message, uint8_t *nodeID);
    void encode_nodeID(CAN_Message_t *message, uint8_t nodeID);
    void decode_packet(CAN_Message_t *message, Joint *joint);



};

extern FreckleCAN g_can;