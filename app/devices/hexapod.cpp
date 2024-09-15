#include "hexapod.h"

Hexapod::Hexapod()
{

}

Hexapod::~Hexapod()
{
}

void Hexapod::set_enabled(uint8_t enabled)
{
    for (int i = 0; i < 6; i++)
    {
        m_legs[i]->set_enabled(enabled);
    }
}

void Hexapod::allocate_legs(Leg *leg0, Leg *leg1, Leg *leg2, Leg *leg3, Leg *leg4, Leg *leg5)
{
    m_legs[0] = leg0;
    m_legs[1] = leg1;
    m_legs[2] = leg2;
    m_legs[3] = leg3;
    m_legs[4] = leg4;
    m_legs[5] = leg5;
}

void Hexapod::set_allLegPositions(int x, int y, int z)
{
    for (int i = 0; i < 6; i++)
    {
        m_legs[i]->set_position(x, y, z);
    }
}

void Hexapod::step(int timeMs)
{
    float x;
    float y;
    float z;
    float frequency = 1/(settings.step.period/1000.0f);


    float angleRads = settings.step.angle * 0.1f * M_PI / 180.0f;

    float xs[6];
    float ys[6];
    float zs[6];

    for (int i = 0; i < 6; i++)
    {
        angleRads = (settings.step.angle + (3600 - i * settings.physical.legAngularSeparation)) * 0.1f * M_PI / 180.0f;
        directionalSemiCirclePath(settings.step.radius/1000.0f, frequency, timeMs/1000.0f,  angleRads, settings.step.xOffset/1000.0f,&xs[i], &ys[i], &zs[i]);
        timeMs += settings.step.period/2;
    } 

    for (int i = 0; i < 6; i++)
    {
        set_legPosition(i, xs[i]*1000, ys[i]*1000, zs[i]*1000+settings.step.height);
    }
}


void Hexapod::set_legPosition(uint8_t legNumber, int x, int y, int z)
{
    if (legNumber < 6)
    {
        m_legs[legNumber]->set_position(x, y, z);
    }
}
