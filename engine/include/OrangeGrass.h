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
#include "IOGPhysics.h"
#include "IOGInputDispatcher.h"
#include "IOGRenderer.h"
#include "common.h"
#include <vector>
#include <string>


IOGResourceMgr* GetResourceMgr ();
IOGLevelManager* GetLevelManager ();
IOGSceneGraph* GetSceneGraph ();
IOGActorManager* GetActorManager ();
IOGPhysics* GetPhysics ();
IOGInputDispatcher* GetInput ();
IOGRenderer* GetRenderer ();

IOGSprite* CreateSprite (const std::string& _Alias);

#endif