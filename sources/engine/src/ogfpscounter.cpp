/*
 * OrangeGrass
 * Copyright (C) 2009 Vyacheslav Bogdanov.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/lgpl-3.0-standalone.html>.
 */
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
