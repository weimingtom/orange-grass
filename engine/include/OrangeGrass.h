#ifndef ORANGEGRASS_H_
#define ORANGEGRASS_H_

#include "OpenGL2.h"
#include "IOGResourceMgr.h"
#include "IOGLevelManager.h"
#include "IOGSprite.h"
#include "IOGCamera.h"


IOGResourceMgr* GetResourceMgr ();
IOGLevelManager* GetLevelManager ();
IOGCamera* GetCamera ();
IOGSprite* CreateSprite (const char* _pAlias);

#endif