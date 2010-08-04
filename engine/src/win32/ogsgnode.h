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
	COGSgNode (IOGRenderable* _pRenderable);
	virtual ~COGSgNode ();

	// get world transform.
	virtual const MATRIX& GetWorldTransform () const;

	// update transform.
	virtual void Update (const MATRIX& _mT, const IOGObb& _Obb);

	// Get OBB
	virtual const IOGObb& GetOBB () const;

	// get renderable.
	virtual IOGRenderable* GetRenderable ();

private:

    IOGRenderable*  m_pRenderable;
    MATRIX          m_mWorld;
	IOGObb			m_Obb;
};

#endif
