/*
 *  ogsglandscapenode.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogsglandscapenode.h"


COGSgLandscapeNode::COGSgLandscapeNode () :   
    m_pRenderable(NULL),
    m_bActive(false)
{
}


COGSgLandscapeNode::COGSgLandscapeNode (IOGTerrain* _pRenderable) :   
    m_pRenderable(_pRenderable),
    m_bActive(true)
{
    m_OBB.Create(m_pRenderable->GetAABB());
    MatrixIdentity(m_World);
}


COGSgLandscapeNode::~COGSgLandscapeNode () 
{
    m_pRenderable = NULL;
}


// get world transform.
const MATRIX& COGSgLandscapeNode::GetWorldTransform () const
{
    return m_World;
}


// Get OBB
const IOGObb& COGSgLandscapeNode::GetOBB () const
{
    return m_OBB;
}


// update transform.
void COGSgLandscapeNode::Update (unsigned long _ElapsedTime)
{
}


// render.
void COGSgLandscapeNode::Render ()
{
	if (!m_bActive)
		return;

    m_pRenderable->Render(m_World);
}


// render all nodes.
void COGSgLandscapeNode::RenderAll ()
{
    m_pRenderable->RenderAll(m_World);
}


// get physics.
IOGPhysicalObject* COGSgLandscapeNode::GetPhysics ()
{
    return NULL;
}


// Get active point
bool COGSgLandscapeNode::GetActivePoint (Vec3& _point, const std::string& _Alias)
{
    return false;
}


// start animation.
void COGSgLandscapeNode::StartAnimation (const std::string& _Alias)
{
}


// Set active state
void COGSgLandscapeNode::Activate (bool _bActive)
{
	m_bActive = _bActive;
}
