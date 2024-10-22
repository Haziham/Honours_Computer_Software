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

void zeroPositions(int16_t *xs, int16_t *ys, int16_t *zs)
{
    for (int i = 0; i < 6; i++)
    {
        xs[i] = 0;
        ys[i] = 0;
        zs[i] = 0;
    }
}
void Hexapod::step(int timeMs)
{
    float x;
    float y;
    float z;
    float frequency = 1/(settings.step.period/1000.0f);


    // float angleRads = settings.step.angle * 0.1f * M_PI / 180.0f;

    // float xs[6];
    // float ys[6];
    // float zs[6];

    // for (int i = 0; i < 6; i++)
    // {
    //     angleRads = (settings.step.angle + (3600 - i * settings.physical.legAngularSeparation)) * 0.1f * M_PI / 180.0f;
    //     directionalSemiCirclePath(settings.step.radius/1000.0f, frequency, timeMs/1000.0f,  angleRads, settings.position.xOffset/1000.0f,&xs[i], &ys[i], &zs[i]);
    //     timeMs += settings.step.period/2;
    // } 

    // for (int i = 0; i < 6; i++)
    // {
    //     set_legPosition(i, xs[i]*1000, ys[i]*1000, zs[i]*1000+settings.position.height);
    // }
}

float Hexapod::getWalkingSpeed()
{
    float speedup = settings.walking.speed/(4*settings.step.radius);
    // print walking speed
    printf("Walking speed: %f\n", settings.walking.speed);
    printf("Step radius: %d\n", settings.step.radius);
    return speedup;
}

void Hexapod::move(uint32_t timeMs)
{
    uint32_t deltaTime = timeMs - previousTime;
    previousTime = timeMs;


    int16_t xs[6];
    int16_t ys[6];
    int16_t zs[6];

    if (settings.movementModes[MOVEMENT_MODE_IDLE])
    {
        printf("Idle\n");
        walkingTime = 0;
        idleTime += deltaTime;
        settings.position.height = -60;
        settings.position.xOffset = 75;
        update_offsets();
        idle(idleTime);
    }
    else if (settings.movementModes[MOVEMENT_MODE_WALKING])
    {
        printf("Walking\n");
        idleTime = 0;
        stateStartTime = 0;
        legNumber = rand() % 6;
        transition = false;
        firstSideStep = true;
        m_idleState = 0;
        printf("Delta time: %d\n", deltaTime);
        walkingTime += deltaTime * getWalkingSpeed();
        printf("Walking time: %d\n", walkingTime);
        printf("Walking speed: %f\n", getWalkingSpeed());   
        calculate_walkingLegPositions(walkingTime, xs, ys, zs);
        if (settings.walking.speed == 0)
        {
            zeroPositions(xs, ys, zs);
        }
        set_offsetLegPositions(xs, ys, zs);
    }
    else 
    {
        printf("No movement mode selected\n");
        idleTime = 0;
        walkingTime = 0;
        stateStartTime = 0;
        legNumber = rand() % 6;
        transition = false;
        firstSideStep = true;
        m_idleState = 0;
        zeroPositions(xs, ys, zs);
        set_offsetLegPositions(xs, ys, zs);
    }

}


void Hexapod::idle(uint32_t timeMs)
{

    int16_t xs[6];
    int16_t ys[6];
    int16_t zs[6];


    if (transition)
    {
        if (timeMs - stateStartTime > 2000)
        {
            transition = false;
            stateStartTime = timeMs;
        }
        else
        {
            return;
        }
    }

    int stateDuration = timeMs - stateStartTime;
    int state1Length = 10000;
    int state2Length = 10000;
    int state3Length = 10000;
    int state4Length = 5000;
    int tempStateDuration;

    switch (m_idleState)
    {
        case 0:
        calculate_idleLegPositions(stateDuration, state1Length/2, xs, ys, zs);

        if (stateDuration > state1Length)
        {
            m_idleState = 1;
            transition = true;
            stateStartTime = timeMs;
        }
        break;
        case 1:
        calculate_idleTwistPositions(stateDuration, state2Length, xs, ys, zs);
        if (stateDuration > state2Length)
        {
            m_idleState = 2;
            transition = true;
            stateStartTime = timeMs;
            legNumber = rand() % 6;
        }
        break;
        case 2:
        calculate_waveLegPositions(stateDuration, state3Length, legNumber, xs, ys, zs);

        if (stateDuration > state3Length)
        {
            m_idleState = 3;
            transition = true;
            stateStartTime = timeMs;
        }
        break;
        case 3:
        tempStateDuration = stateDuration;
        if (!firstSideStep)
        {
            tempStateDuration =  state4Length - stateDuration;
        }
            
        calculate_sideStepPositions(tempStateDuration, state4Length, xs, ys, zs);

        if (stateDuration > state4Length)
        {
            zeroPositions(xs, ys, zs);
            m_idleState = 0;
            transition = true;
            stateStartTime = timeMs;
            firstSideStep = !firstSideStep;
        } 
        break;

        default:
        m_idleState = 0;
        stateStartTime = timeMs;
        break;
    }

    // printf("Leg positions: \n");
    // for (int i = 0; i < 6; i++)
    // {
    //     printf("Leg %d: x: %d, y: %d, z: %d\n", i, xs[i], ys[i], zs[i]);
    // }
    set_offsetLegPositions(xs, ys, zs);


    // display leg positions

}

void Hexapod::quickFunction(float time, float period, float *x, float *y, float *z)
{
    float radius = (settings.position.xOffset + 75);
    float stepSize = 80;
    float stepHeight = 50;
    float totalPos = stepSize/radius;

    float posStart = (3 * M_PI/2) - totalPos/2;
    float cycleTime = fmod(time, period);
    float cyclePercentage = (cycleTime/period)*2 - 1;
    float t = 0;
    // printf("cyclePercentage: %f\n", cyclePercentage);

    if (cyclePercentage < 0)
    {
        t = posStart + (1 + cyclePercentage)  * totalPos;    
        // printf t
        *z = 0;

    }
    else 
    {
        t = posStart + totalPos - cyclePercentage * totalPos;
        float temp = cyclePercentage * stepHeight * 2 - stepHeight;
        *z = sqrt(stepHeight*stepHeight - temp*temp); 
    }

    // printf("t: %f\n", t);
    *y = radius * cos(t);
    *x = radius * sin(t) + radius;

}


void Hexapod::calculate_sideStepPositions(uint32_t timeMs, int period, int16_t *xs, int16_t *ys, int16_t *zs)
{
    period = period/1000.0f;
    float steps = 1;
    float stepPeriod = period/steps;
    // float minPos = (3* M_PI/2) - (totalPos/(2));
    // float maxPos = (3* M_PI/2) + (totalPos/(2));

    float time = timeMs/1000.0f;

    // add quater a stepPeriod
    time += stepPeriod/4;

    float oddx = 0;
    float oddy = 0;
    float oddz = 0;

    float evenx = 0;
    float eveny = 0;
    float evenz = 0;

// printf("tesm\n");   
    quickFunction(time, stepPeriod, &oddx, &oddy, &oddz);
    quickFunction(time + stepPeriod/2, stepPeriod, &evenx, &eveny, &evenz);

// printf("tesm\n");
    for (int i = 0; i < 6; i++)
    {
        if (i % 2 == 0)
        {
            xs[i] = evenx;
            ys[i] = eveny;
            zs[i] = evenz;
        }
        else
        {
            xs[i] = oddx;
            ys[i] = oddy;
            zs[i] = oddz;
        }
    }

}

float easeOutQuint(float x)
{
    return 1 - pow(1 - x, 5);
    // return sin(x * M_PI/2);
}

void Hexapod::calculate_waveLegPositions(uint32_t timeMs, int period, int legNumber, int16_t *xs, int16_t *ys, int16_t *zs)
{

    for (int i = 0; i < 6; i++)
    {
        xs[i] = 0;
        ys[i] = 0;
        zs[i] = 0;
    }
    // random number between 0 and 5
    float time = timeMs/1000.0f;
    period = period/1000.0f;
    float liftFraction = 3;
    float waveFraction = 1;
    float waitFraction = 1;
    float lowerFraction = 3;
    float totalFraction = waitFraction + liftFraction + waveFraction + lowerFraction;

    float liftTime = period * liftFraction / totalFraction;
    float waveTime = period * waveFraction / totalFraction;
    float lowerTime = period * lowerFraction / totalFraction;
    float waitTime = period * waitFraction / totalFraction;

    float liftStartTime = 0;
    float waveStartTime = liftTime;
    float waitStartTime = waveStartTime + waveTime;
    float lowerStartTime = waitStartTime + waitTime;


    int waveHeight = 200;
    if (time > lowerStartTime )
    {
        float currentLowerTime = time - lowerStartTime;
        float percentage = currentLowerTime / lowerTime;
        percentage = easeOutQuint(percentage);
        zs[legNumber] = static_cast<int>(waveHeight - waveHeight * percentage);
    }
    else if (time > waitStartTime)
    {
        zs[legNumber] = waveHeight;
    }
    else if (time > waveStartTime)
    {
        float currentWaveTime = time - waveStartTime;
        float waveFrequency = (5) * (2*M_PI);
        float waveAmplitude = 25;
        float wavey = waveAmplitude * sin(waveFrequency * currentWaveTime);
        zs[legNumber] = waveHeight;
        ys[legNumber] = wavey;
    }
    else if (time > liftStartTime)
    {
        float currentLiftTime = time - liftStartTime;
        float percentage = currentLiftTime / liftTime;
        percentage = easeOutQuint(percentage);


        zs[legNumber] = static_cast<int>(waveHeight * percentage);
    }
    else
    {
        zs[legNumber] = 0;
    }
    xs[legNumber] = 0;
    
}

void Hexapod::calculate_idleLegPositions(uint32_t timeMs, int period, int16_t *xs, int16_t *ys, int16_t *zs)
{
    float time = timeMs/1000.0f;

    float zAmp = 25;

    period = period/1000.0f;


    float z = zAmp * sin(2*M_PI/period * time);
    // float y = yAmp * sin(2*M_PI/period * time);
    float y = 0;
    float x = 0;
    
    for (int i = 0; i < 6; i++)
    {
        xs[i] = x;
        ys[i] = y;
        zs[i] = z;
    }
}

void Hexapod::calculate_idleTwistPositions(uint32_t timeMs, int period, int16_t *xs, int16_t *ys, int16_t *zs) 
{
    float time = timeMs/1000.0f;

    float yAmp = 25;

    period = period/1000.0f;

    // float z = zAmp * sin(2*M_PI/period * time);
    float y = yAmp * sin(2*M_PI/period * time);
    // float y = 0;
    float z = 0;
    float x = 0;
    
    for (int i = 0; i < 6; i++)
    {
        xs[i] = x;
        ys[i] = y;
        zs[i] = z;
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
    if (x == 0 && y == 0)
    {
        settings.movementModes[MOVEMENT_MODE_WALKING] = 0;
        return;
    }

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
        float period = settings.step.period;
        float frequency = 1/period;
        float angleRads = settings.walking.direction * 0.1f * M_PI / 180.0f;
        float xsf, ysf, zsf;

        for (int i = 0; i < 6; i++)
        {
            angleRads = (settings.walking.direction + (i * settings.physical.legAngularSeparation)) * 0.1f * M_PI / 180.0f;
            directionalSemiCirclePath(settings.step.radius/1000.0f, frequency, timeMs/1000.0f,  angleRads, 0 ,&xsf, &ysf, &zsf);
            timeMs += (period/2)*1000;
            xs[i] = xsf * 1000;
            ys[i] = ysf * 1000;
            zs[i] = zsf * 1000;
        } 

}

// void Hexapod::calculate_waveLegPositions(uint32_t timeMs, int period, int16_t *xs, int16_t *ys, int16_t *zs)
// {

//     for (int i = 0; i < 6; i++)
//     {
//         xs[i] = 0;
//         ys[i] = 0;
//         zs[i] = 0;
//     }
//     // random number between 0 and 5
//     int legNumber = rand() % 6;
//     float time = timeMs/1000.0f;
//     period = period/1000.0f;
//     float liftFraction = 3;
//     float waveFraction = 3;
//     float lowerFraction = 3;
//     float totalFraction = liftFraction + waveFraction + lowerFraction;

//     float liftTime = period * liftFraction / totalFraction;
//     float waveTime = period * waveFraction / totalFraction;
//     float lowerTime = period * lowerFraction / totalFraction;

//     float liftStartTime = 0;
//     float waveStartTime = liftTime;
//     float lowerStartTime = liftTime + waveTime;


//     int waveHeight = 50;
//     if (time > lowerStartTime )
//     {
//         float currentLowerTime = time - lowerStartTime;
//         float percentage = currentLowerTime / lowerTime;
//         percentage = easeOutQuint(percentage);
//         int targetHeight = 0;
//         zs[legNumber] = static_cast<int>(targetHeight * percentage);
//     }
//     else if (time > waveStartTime)
//     {
//         float numWaves = 2;
//         float currentWaveTime = time - waveStartTime;
//         float wavePeriod = waveTime / numWaves;
//         float waveFrequency = (1/wavePeriod) * (2*M_PI);
//         float waveAmplitude = 25;
//         float wavey = waveAmplitude * sin(waveFrequency * currentWaveTime);
//         zs[legNumber] = waveHeight;
//         ys[legNumber] = wavey;
//     }
//     else if (time > liftStartTime)
//     {
//         float currentLiftTime = time - liftStartTime;
//         float percentage = liftTime / liftTime;
//         percentage = easeOutQuint(percentage);


//         zs[legNumber] = static_cast<int>(waveHeight * percentage);
//     }
//     else
//     {
//         zs[legNumber] = 0;
//     }
//     xs[legNumber] = 0;
    
// }