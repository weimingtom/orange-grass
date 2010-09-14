#include <windows.h>
#include "Timer.h"


CFPSCounter::CFPSCounter()
{
    QueryPerformanceCounter (&framedelay);
    QueryPerformanceFrequency (&tickspersecond);
}

CFPSCounter::~CFPSCounter()
{
}

// updating FPS COUNTER
void CFPSCounter::Update ()
{
    QueryPerformanceCounter (&currentticks);
    speedfactor = (float)(currentticks.QuadPart - framedelay.QuadPart) / ((float)tickspersecond.QuadPart );
    fps = 1 / speedfactor;
    if (speedfactor <= 0) speedfactor = 1;
    framedelay = currentticks;
}
