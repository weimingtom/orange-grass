#ifndef OPENGL2_H_
#define OPENGL2_H_

#ifdef WIN32
#undef __GL_H__
#include <windows.h>
#include "glew.h"
#include "wglext.h"
#else
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#endif

#endif
