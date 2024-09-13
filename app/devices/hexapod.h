#pragma once
#include "leg.h"


class Hexapod
{

public:
    Hexapod();
    ~Hexapod();


    Leg* get_leg(uint8_t legNumber);

private:

};