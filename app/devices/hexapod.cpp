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
