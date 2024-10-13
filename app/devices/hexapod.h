#pragma once
#include "leg.h"
#include "hexapodMaths.h"
#include <math.h>


#define NUMBER_LEGS 6

class Hexapod
{

public:
    Hexapod();
    ~Hexapod();

    enum 
    {
        MOVEMENT_MODE_IDLE,
        MOVEMENT_MODE_WALKING,
        MOVEMENT_END_ENUM
    } MOVEMENT_MODES;

    // unsigned int numberLegs() { return m_numberLegs; }
    const unsigned int numberLegs = 6;

    typedef struct {
        uint16_t tiltDirection = 0; // degrees * 0.1
        uint16_t tiltAngle = 0; // degrees * 0.1    
        int16_t height = -20; // mm
        uint16_t xOffset = 117; //mm
    } PositionSettings_t;

    struct 
    {
        struct{
            uint16_t radius = 50; // mm
            uint16_t period = 2000; // mHz
            // uint16_t angle = 0; // degrees * 0.1
        } step;
        struct {
            uint16_t legAngularSeparation = 600;  // degrees * 0.1
        } physical;
        uint8_t movementModes[MOVEMENT_END_ENUM] = {0};
        struct {
            float speed = 1;
            uint16_t direction = 0; // degrees * 0.1
        } walking;
        PositionSettings_t position;
        struct {
            int16_t x[NUMBER_LEGS] = {0}; // mm
            int16_t y[NUMBER_LEGS] = {0}; // mm
            int16_t z[NUMBER_LEGS] = {0}; // mm
        } offsets;
    } settings;

    Leg* get_leg(uint8_t legNumber);
    void set_enabled(uint8_t enabled);
    void enable() { set_enabled(1); }
    void disable() { set_enabled(0); }
    void allocate_legs(Leg* leg0, Leg* leg1, Leg* leg2, Leg* leg3, Leg* leg4, Leg* leg5);

    void set_allLegPositions(int x, int y, int z); 

    void step(int timeMs);
    void move(uint32_t timeMs);
    virtual void set_legPosition(uint8_t legNumber, int x, int y, int z);
    void set_legPositions(int16_t* xs, int16_t* ys, int16_t* zs);
    void set_offsetLegPositions(int16_t* x, int16_t* y, int16_t* z);
    void offset_legPositions(int16_t* x, int16_t* y, int16_t* z);
    void update_offsets();

    void joystick_moveControl(float x, float y);
    void joystick_tiltControl(float x, float y);
    void joystick_rotateControl(float x, float y);

    void toggle_idle() { settings.movementModes[MOVEMENT_MODE_IDLE] = !settings.movementModes[MOVEMENT_MODE_IDLE]; }
    void update_positionSettings(Hexapod::PositionSettings_t settings);

    void powerOff();
    void powerOn(); 

private:
    unsigned int m_numberLegs = 6;
    
    Leg leg0;
    Leg leg1;
    Leg leg2;
    Leg leg3;
    Leg leg4;
    Leg leg5;

    Leg* m_legs[6] = {&leg0, &leg1, &leg2, &leg3, &leg4, &leg5};

    void calculate_walkingLegPositions(uint32_t timeMs, int16_t* xs, int16_t* ys, int16_t* zs);


};