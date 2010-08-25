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


class COGSceneGraph : public IOGSceneGraph
{
public:
	COGSceneGraph ();
	virtual ~COGSceneGraph ();

	// Clear scene graph
	virtual void Clear ();

	// Create scene graph node
	virtual IOGSgNode* CreateNode (IOGRenderable* _pRenderable);

	// Add scene graph node
	virtual void AddNode (IOGSgNode* _pNode);

	// Remove scene graph node
	virtual void RemoveNode (IOGSgNode* _pNode);

	// Render.
	virtual void Render (const MATRIX& _mView);

	// Render the whole scene.
	virtual void RenderAll (const MATRIX& _mView);

	// Get scene camera.
	virtual IOGCamera* GetCamera ();

	// Get scene light.
	virtual IOGLight* GetLight ();

private:

    std::list<IOGSgNode*>	m_NodesList;
	IOGCamera*				m_pCamera;
	IOGLight*				m_pLight;
};

#endif
