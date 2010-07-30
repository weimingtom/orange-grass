#ifndef IOGSCENEGRAPH_H_
#define IOGSCENEGRAPH_H_

#include "IOGSgNode.h"


class IOGSceneGraph
{
public:
	// destructor
	virtual ~IOGSceneGraph () {}

	// Create scene graph node
	virtual IOGSgNode* CreateNode (IOGRenderable* _pRenderable) = 0;

	// Add scene graph node
	virtual void AddNode (IOGSgNode* _pNode) = 0;

	// Remove scene graph node
	virtual void RemoveNode (IOGSgNode* _pNode) = 0;

	// Render.
	virtual void Render (const MATRIX& _mView) = 0;
};

#endif
