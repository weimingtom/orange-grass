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


COGSgNode::COGSgNode () :   m_pRenderable(NULL),
                            m_pPhysics(NULL)
{
}


COGSgNode::COGSgNode (IOGRenderable* _pRenderable,
                      IOGPhysicalObject* _pPhysics) :   m_pRenderable(_pRenderable),
                                                        m_pPhysics(_pPhysics)
{
}


COGSgNode::~COGSgNode () 
{
    m_pRenderable = NULL;
    m_pPhysics = NULL;
}


// get world transform.
const MATRIX& COGSgNode::GetWorldTransform () const
{
    return m_pPhysics->GetWorldTransform();
}


// Get OBB
const IOGObb& COGSgNode::GetOBB () const
{
    return m_pPhysics->GetOBB();
}


// update transform.
void COGSgNode::Update (unsigned long _ElapsedTime)
{
    m_pRenderable->Update(_ElapsedTime);
}


// get renderable.
IOGRenderable* COGSgNode::GetRenderable ()
{
    return m_pRenderable;
}


// get physics.
IOGPhysicalObject* COGSgNode::GetPhysics ()
{
    return m_pPhysics;
}
