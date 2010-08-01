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
#include <vector>


class COGSceneGraph : public IOGSceneGraph
{
public:
	COGSceneGraph ();
	virtual ~COGSceneGraph ();

	// Create scene graph node
	virtual IOGSgNode* CreateNode (IOGRenderable* _pRenderable);

	// Add scene graph node
	virtual void AddNode (IOGSgNode* _pNode);

	// Remove scene graph node
	virtual void RemoveNode (IOGSgNode* _pNode);

	// Render.
	virtual void Render (const MATRIX& _mView);

private:

    std::vector<IOGSgNode*> m_NodesList;
};

#endif
