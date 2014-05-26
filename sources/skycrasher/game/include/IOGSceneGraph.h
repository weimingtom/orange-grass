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
#ifndef IOGSCENEGRAPH_H_
#define IOGSCENEGRAPH_H_

#include "IOGSgNode.h"
#include "IOGCamera.h"
#include "IOGTexture.h"
#include "IOGEffect.h"
#include "IOGModel.h"


class IOGSceneGraph
{
public:
    // destructor
    virtual ~IOGSceneGraph () {}

    // Clear scene graph
    virtual void Clear () = 0;

    // Create scene graph node
    virtual IOGSgNode* CreateNode (IOGModel* _pRenderable, IOGPhysicalObject* _pPhysics) = 0;

    // Create scene graph effect node
    virtual IOGSgNode* CreateEffectNode (IOGEffect* _pRenderable, IOGPhysicalObject* _pPhysics) = 0;

    // Create scene graph landscape node
    virtual IOGSgNode* CreateLandscapeNode (IOGModel* _pRenderable) = 0;

    // Add scene graph node
    virtual void AddNode (IOGSgNode* _pNode) = 0;

    // Add landscape scene graph node
    virtual void AddLandscapeNode (IOGSgNode* _pNode) = 0;

    // Add effect scene graph node
    virtual void AddEffectNode (IOGSgNode* _pNode) = 0;

    // Add static scene graph node
    virtual void AddStaticNode (IOGSgNode* _pNode) = 0;

    // Remove scene graph node
    virtual void RemoveNode (IOGSgNode* _pNode) = 0;

    // Update scene graph.
    virtual void Update (unsigned long _ElapsedTime) = 0;

    // Render scene graph.
    virtual void RenderScene (IOGCamera* _pCamera) = 0;
};

#endif
