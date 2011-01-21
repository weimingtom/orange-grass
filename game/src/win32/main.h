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