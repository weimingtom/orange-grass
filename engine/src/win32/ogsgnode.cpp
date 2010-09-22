/*
 *  ogsgnode.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogsgnode.h"
#include "IOGMath.h"


COGSgNode::COGSgNode () : m_pRenderable(NULL)
{
}


COGSgNode::COGSgNode (IOGRenderable* _pRenderable) : m_pRenderable(_pRenderable)
{
}


COGSgNode::~COGSgNode () 
{
    m_pRenderable = NULL;
}


// get world transform.
const MATRIX& COGSgNode::GetWorldTransform () const
{
    return m_mWorld;
}


// update transform.
void COGSgNode::Update (unsigned long _ElapsedTime, 
						const MATRIX& _mT, 
						const IOGObb& _Obb)
{
    m_mWorld = _mT;
    m_Obb = _Obb;
}


// Get OBB
const IOGObb& COGSgNode::GetOBB () const
{
    return m_Obb;
}


// get renderable.
IOGRenderable* COGSgNode::GetRenderable ()
{
    return m_pRenderable;
}
