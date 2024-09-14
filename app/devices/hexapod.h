#pragma once
#include "leg.h"


class Hexapod
{

public:
    Hexapod();
    ~Hexapod();


    Leg* get_leg(uint8_t legNumber);
    void set_enabled(uint8_t enabled);
    void enable() { set_enabled(1); }
    void disable() { set_enabled(0); }
    void allocate_legs(Leg* leg0, Leg* leg1, Leg* leg2, Leg* leg3, Leg* leg4, Leg* leg5);

    void set_allLegPositions(int x, int y, int z); 

private:

    Leg leg0;
    Leg leg1;
    Leg leg2;
    Leg leg3;
    Leg leg4;
    Leg leg5;

    Leg* m_legs[6] = {&leg0, &leg1, &leg2, &leg3, &leg4, &leg5};

};