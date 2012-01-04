#ifdef WIN32
#include <windows.h>
#endif
#include "ogfpscounter.h"


COGFPSCounter::COGFPSCounter()
{
#ifdef WIN32
    QueryPerformanceCounter (&framedelay);
    QueryPerformanceFrequency (&tickspersecond);
#endif
}


COGFPSCounter::~COGFPSCounter()
{
}


// updating FPS COUNTER
void COGFPSCounter::Update ()
{
#ifdef WIN32
    QueryPerformanceCounter (&currentticks);
    speedfactor = (float)(currentticks.QuadPart - framedelay.QuadPart) / ((float)tickspersecond.QuadPart );
    fps = 1 / speedfactor;
    if (speedfactor <= 0) 
        speedfactor = 1;
    framedelay = currentticks;
#endif
}
