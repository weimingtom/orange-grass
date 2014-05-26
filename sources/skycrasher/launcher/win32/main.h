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
#ifndef MAIN_H_
#define MAIN_H_

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "resource.h"
#include <stdlib.h>
#include <string>
#include <OpenGL2.h>


HINSTANCE			shInstance = NULL;
HWND				shWnd = NULL;
HDC				    shDC;
HGLRC               shRC;
DWORD				sElapsedTime = 0;
DWORD				sPrevTime = 0;
DWORD				sCurTime = 0;
int                 sMouseX = 0;
int                 sMouseY = 0;

bool                bTouch = false;
int                 sTouchX = 0;
int                 sTouchY = 0;

#endif