#ifndef OPENGL2_H_
#define OPENGL2_H_

#ifdef WIN32
#include <windows.h>
#include "glew.h"
#include "wglew.h"
#else
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 30000
#include <TargetConditionals.h>
#include <Availability.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#endif
#endif

#endif
