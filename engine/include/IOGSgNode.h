/*
 *  IOGSgNode.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGSGNODE_H_
#define IOGSGNODE_H_

#include "Mathematics.h"
#include "IOGObb.h"


class IOGSgNode
{
public:
	// destructor
	virtual ~IOGSgNode () {}

	// get world transform.
	virtual const MATRIX& GetWorldTransform () const = 0;

	// update transform.
	virtual void Update (
		unsigned long _ElapsedTime, 
		const MATRIX& _mT, 
		const IOGObb& _Obb) = 0;

	// Get OBB
	virtual const IOGObb& GetOBB () const = 0;

	// get renderable.
	virtual IOGRenderable* GetRenderable () = 0;
};

#endif
