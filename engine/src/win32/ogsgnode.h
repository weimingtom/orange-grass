/*
 *  ogsgnode.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGSGNODE_H_
#define OGSGNODE_H_

#include "Mathematics.h"
#include "IOGSgNode.h"


class COGSgNode : public IOGSgNode
{
	COGSgNode ();

public:
	COGSgNode (IOGRenderable* _pRenderable, IOGPhysicalObject* _pPhysics);
	virtual ~COGSgNode ();

	// get world transform.
	virtual const MATRIX& GetWorldTransform () const;

	// Get OBB
	virtual const IOGObb& GetOBB () const;

	// update transform.
	virtual void Update (unsigned long _ElapsedTime);

	// get renderable.
	virtual IOGRenderable* GetRenderable ();

	// get physics.
	virtual IOGPhysicalObject* GetPhysics ();

protected:

    IOGRenderable*      m_pRenderable;
    IOGPhysicalObject*  m_pPhysics;
};

#endif
