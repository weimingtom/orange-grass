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
#ifndef OGSCENEGRAPH_H_
#define OGSCENEGRAPH_H_

#include "IOGSceneGraph.h"
#include "IOGRenderTypes.h"
#include <list>
#include <map>
#include "IOGGlobalVarsTable.h"


class COGSceneGraph : public IOGSceneGraph
{
public:
    COGSceneGraph ();
    virtual ~COGSceneGraph ();

    // Clear scene graph
    virtual void Clear ();

    // Create scene graph node
    virtual IOGSgNode* CreateNode (IOGModel* _pRenderable, IOGPhysicalObject* _pPhysics);

    // Create scene graph effect node
    virtual IOGSgNode* CreateEffectNode (IOGEffect* _pRenderable, IOGPhysicalObject* _pPhysics);

    // Create scene graph landscape node
    virtual IOGSgNode* CreateLandscapeNode (IOGModel* _pRenderable);

    // Add scene graph node
    virtual void AddNode (IOGSgNode* _pNode);

    // Add static scene graph node
    virtual void AddStaticNode (IOGSgNode* _pNode);

    // Add landscape scene graph node
    virtual void AddLandscapeNode (IOGSgNode* _pNode);

    // Add effect scene graph node
    virtual void AddEffectNode (IOGSgNode* _pNode);

    // Remove scene graph node
    virtual void RemoveNode (IOGSgNode* _pNode);

    // Update scene graph.
    virtual void Update (unsigned long _ElapsedTime);

    // Render scene graph.
    virtual void RenderScene (IOGCamera* _pCamera);

private:
    typedef std::list<IOGSgNode*>   TNodesList;

private:

    // Remove node from list
    bool RemoveNodeFromList(IOGSgNode* _pNode, TNodesList& _List);

    // clear nodes list
    void ClearNodesList(TNodesList& _List);

    // render nodes list
    void RenderNodesList(IOGCamera* _pCamera, TNodesList& _List, OGRenderPass _Pass);

    // check object visibility
    bool IsVisible(const IOGCamera* _pCamera, const IOGSgNode* _pNode) const;

    // Render effects.
    void RenderEffects (IOGCamera* _pCamera, OGRenderPass _Pass);

private:
    IOGGlobalVarsTable* m_pGlobalVars;
    IOGSgNode*          m_pLandscapeNode;
    TNodesList          m_StaticNodes;
    TNodesList          m_NodesList;
    TNodesList          m_EffectNodesList;
    float               m_fViewDistance;
};

#endif
