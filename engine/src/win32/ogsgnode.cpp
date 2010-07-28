/*
 *  ogsgnode.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "orangegrass.h"
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


// set world transform.
void COGSgNode::SetWorldTransform (const MATRIX& _mT)
{
    m_mWorld = _mT;
}


// set world transform.
void COGSgNode::SetWorldTransform (const Vec3& _vPos, const Vec3& _vRot)
{
    MatrixTranslation(m_mWorld, _vPos.x, _vPos.y, _vPos.z);
}


// get renderable.
IOGRenderable* COGSgNode::GetRenderable ()
{
    return m_pRenderable;
}
