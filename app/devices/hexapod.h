#pragma once
#include "leg.h"
#include "hexapodMaths.h"
#include <math.h>


class Hexapod
{

public:
    Hexapod();
    ~Hexapod();


    struct 
    {
        struct{
            uint16_t radius = 100; // mm
            uint16_t period = 2000; // mHz
            uint16_t angle = 0; // degrees * 0.1
            int16_t height = -20; // mm
            uint16_t xOffset = 117; //mm

        } step;
        struct {
            uint16_t legAngularSeparation = 600;  // degrees * 0.1
        } physical;

    } settings;

    Leg* get_leg(uint8_t legNumber);
    void set_enabled(uint8_t enabled);
    void enable() { set_enabled(1); }
    void disable() { set_enabled(0); }
    void allocate_legs(Leg* leg0, Leg* leg1, Leg* leg2, Leg* leg3, Leg* leg4, Leg* leg5);

    void set_allLegPositions(int x, int y, int z); 

    void step(int timeMs);
    virtual void set_legPosition(uint8_t legNumber, int x, int y, int z);

private:

    Leg leg0;
    Leg leg1;
    Leg leg2;
    Leg leg3;
    Leg leg4;
    Leg leg5;

    Leg* m_legs[6] = {&leg0, &leg1, &leg2, &leg3, &leg4, &leg5};

};