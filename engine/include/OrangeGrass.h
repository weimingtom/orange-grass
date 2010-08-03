/*
 *  OrangeGrass.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef ORANGEGRASS_H_
#define ORANGEGRASS_H_

#include "OpenGL2.h"
#include "IOGCoreHelpers.h"
#include "IOGResourceMgr.h"
#include "IOGLevelManager.h"
#include "IOGSceneGraph.h"
#include "IOGActorManager.h"
#include "IOGSprite.h"
#include "IOGCamera.h"
#include "IOGLight.h"
#include "IOGSerializer.h"
#include "IOGDeserializer.h"


IOGResourceMgr* GetResourceMgr ();
IOGLevelManager* GetLevelManager ();
IOGSceneGraph* GetSceneGraph ();
IOGActorManager* GetActorManager ();
IOGCamera* GetCamera ();
IOGLight* GetLight ();
IOGSprite* CreateSprite (const char* _pAlias);
IOGSerializer* GetSerializer (const char* _pFilename);
IOGDeserializer* GetDeserializer (const char* _pFilename);

#endif