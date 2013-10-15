/*
*  IOGSceneGraph.h
*  OrangeGrass
*
*  Created by Viacheslav Bogdanov on 12.11.09.
*  Copyright 2009 __MyCompanyName__. All rights reserved.
*
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
    virtual void AddStaticNode (IOGSgNode* _pNode, IOGTexture* _pTexture) = 0;

    // Remove scene graph node
    virtual void RemoveNode (IOGSgNode* _pNode) = 0;

    // Update scene graph.
    virtual void Update (unsigned long _ElapsedTime) = 0;

    // Render scene graph.
    virtual void RenderScene (IOGCamera* _pCamera) = 0;

    // Render landscape.
    virtual void RenderLandscape (IOGCamera* _pCamera) = 0;

    // Render effects.
    virtual void RenderEffects (IOGCamera* _pCamera) = 0;

    // Render all effects.
    virtual void RenderAllEffects (IOGCamera* _pCamera) = 0;

    // Render the whole scene - for editor.
    virtual void RenderAll (IOGCamera* _pCamera) = 0;
};

#endif
