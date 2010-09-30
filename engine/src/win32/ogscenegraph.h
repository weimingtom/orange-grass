/*
 *  ogscenegraph.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGSCENEGRAPH_H_
#define OGSCENEGRAPH_H_

#include "IOGSceneGraph.h"
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
	virtual IOGSgNode* CreateNode (IOGRenderable* _pRenderable, IOGPhysicalObject* _pPhysics);

	// Add scene graph node
	virtual void AddNode (IOGSgNode* _pNode);

	// Add static scene graph node
	virtual void AddStaticNode (IOGSgNode* _pNode, IOGTexture* _pTexture);

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

	// Render landscape.
	virtual void RenderLandscape (IOGCamera* _pCamera);

	// Render effects.
	virtual void RenderEffects (IOGCamera* _pCamera);

	// Render the whole scene.
	virtual void RenderAll (IOGCamera* _pCamera);

private:
	typedef std::list<IOGSgNode*>				TNodesList;
	typedef std::map<IOGTexture*, TNodesList>	TStaticNodesMap;

private:

	// Remove node from list
	bool RemoveNodeFromList(IOGSgNode* _pNode, TNodesList& _List);

	// clear nodes list
	void ClearNodesList(TNodesList& _List);

	// render nodes list
	void RenderNodesList(IOGCamera* _pCamera, TNodesList& _List);

	// render whole nodes list
	void RenderWholeNodesList(IOGCamera* _pCamera, TNodesList& _List);

private:
	IOGGlobalVarsTable* m_pGlobalVars;
	IOGSgNode*			m_pLandscapeNode;
	TStaticNodesMap		m_StaticNodes;
	TNodesList			m_NodesList;
	TNodesList			m_EffectNodesList;
	float				m_fViewDistance;
};

#endif
