#include "hexapod.h"

Hexapod::Hexapod()
{

    update_offsets();
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
        directionalSemiCirclePath(settings.step.radius/1000.0f, frequency, timeMs/1000.0f,  angleRads, settings.position.xOffset/1000.0f,&xs[i], &ys[i], &zs[i]);
        timeMs += settings.step.period/2;
    } 

    for (int i = 0; i < 6; i++)
    {
        set_legPosition(i, xs[i]*1000, ys[i]*1000, zs[i]*1000+settings.position.height);
    }
}

void Hexapod::move(uint32_t timeMs)
{
    static uint32_t previousTime = 0;
    uint32_t deltaTime = timeMs - previousTime;
    previousTime = timeMs;

    static uint32_t walkingTime = 0; 
    walkingTime += deltaTime * settings.walking.speed;

    int16_t xs[6];
    int16_t ys[6];
    int16_t zs[6];

    if (settings.movementModes[MOVEMENT_MODE_IDLE])
    {
        for (int i = 0; i < NUMBER_LEGS; i++)
        {
            xs[i] = 0; ys[i] = 0; zs[i] = 0;
        }
        set_offsetLegPositions(xs, ys, zs);
        return;
    }
    if (settings.movementModes[MOVEMENT_MODE_WALKING])
    {
        printf("Walking\n");
        printf("SPeed %f\n", settings.walking.speed);
        calculate_walkingLegPositions(walkingTime, xs, ys, zs);
        set_offsetLegPositions(xs, ys, zs);
    }

}


void Hexapod::set_legPosition(uint8_t legNumber, int x, int y, int z)
{
    if (legNumber < 6)
    {
        m_legs[legNumber]->set_position(x, y, z);
    }
}

void Hexapod::set_legPositions(int16_t *xs, int16_t *ys, int16_t *zs)
{
    for (int i = 0; i < m_numberLegs; i++)
    {
        m_legs[i]->set_position(xs[i], ys[i], zs[i]);
    }
}

void Hexapod::set_offsetLegPositions(int16_t *x, int16_t *y, int16_t *z)
{
    offset_legPositions(x, y, z);
    set_legPositions(x, y, z);
}

void Hexapod::offset_legPositions(int16_t *x, int16_t *y, int16_t *z)
{
    for (int i = 0; i < m_numberLegs; i++)
    {
        x[i] += settings.offsets.x[i];
        y[i] += settings.offsets.y[i];
        z[i] += settings.offsets.z[i];
    }
}

void Hexapod::update_offsets()
{
    for (int i = 0; i < NUMBER_LEGS; i++)
    {
        settings.offsets.z[i] = settings.position.height;
        settings.offsets.x[i] = settings.position.xOffset;
    }
}

void Hexapod::joystick_moveControl(float x, float y)
{
    printf("x: %f, y: %f\n", x, y);
    if (x == 0 && y == 0)
    {
        settings.movementModes[MOVEMENT_MODE_WALKING] = 0;
        return;
    }
    settings.walking.direction = (atan2(y, x) * 180.0f / M_PI) * 10;
    // printf("x*x: %f, y*y: %f\n", x*x, y*y);
    // printf("sqrt(x*x + y*y): %f\n", sqrt(x*x + y*y));
    // printf("sqrt(x*x + y*y)/sqrt(2.0f): %f\n", sqrt(x*x + y*y)/sqrt(2.0f));
    settings.walking.speed = sqrt(x*x + y*y)/sqrt(2.0f);

    printf("direction: %f, speed: %f\n", settings.walking.direction, settings.walking.speed);
    settings.movementModes[MOVEMENT_MODE_WALKING] = 1;
}

void Hexapod::joystick_tiltControl(float x, float y)
{
}

void Hexapod::joystick_rotateControl(float x, float y)
{
}

void Hexapod::update_positionSettings(Hexapod::PositionSettings_t settings)
{
    this->settings.position = settings;
    update_offsets();
}

void Hexapod::powerOff()
{
    enable();
    for (int i = 0; i < 6; i++)
    {
        m_legs[i]->home_hipYaw();
    }


    usleep(1000000);


    for (int i = 0; i < 6; i++)
    {
        m_legs[i]->home_hipPitch();
    }

    usleep(1000000);

    for (int i = 0; i < 6; i++)
    {
        m_legs[i]->home_kneePitch();
    }

    usleep(1000000);
    disable();
}

void Hexapod::powerOn()
{
    enable();

    for (int i = 0; i < 6; i++)
    {
        m_legs[i]->wake_hipYaw();
    }


    usleep(1000000);

    for (int i = 0; i < 6; i++)
    {
        m_legs[i]->wake_kneePitch();
    }

    usleep(1000000);
    for (int i = 0; i < 6; i++)
    {
        m_legs[i]->wake_hipPitch();
    }

    usleep(1000000);
    disable();
}

void Hexapod::calculate_walkingLegPositions(uint32_t timeMs, int16_t *xs, int16_t *ys, int16_t *zs)
{
        float frequency = 1;
        float period = 1/frequency;
        float angleRads = settings.walking.direction * 0.1f * M_PI / 180.0f;
        float xsf, ysf, zsf;

        for (int i = 0; i < 6; i++)
        {
            angleRads = (settings.walking.direction + (3600 - i * settings.physical.legAngularSeparation)) * 0.1f * M_PI / 180.0f;
            directionalSemiCirclePath(settings.step.radius/1000.0f, frequency, timeMs/1000.0f,  angleRads, 0 ,&xsf, &ysf, &zsf);
            timeMs += (period/2)*1000;
            xs[i] = xsf * 1000;
            ys[i] = ysf * 1000;
            zs[i] = zsf * 1000;
        } 
}
