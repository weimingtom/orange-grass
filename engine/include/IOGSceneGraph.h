#ifndef IOGSCENEGRAPH_H_
#define IOGSCENEGRAPH_H_

#include "IOGSgNode.h"


class IOGSceneGraph
{
public:
	// destructor
	virtual ~IOGSceneGraph () {}

	// Add scene graph node
	virtual void AddNode (IOGSgNode* _pNode) = 0;

	// Render.
	virtual void Render (const MATRIX& _mView) = 0;
};

#endif
