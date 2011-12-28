/*
 *  ogseffectgnode.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogsgeffectnode.h"


COGSgEffectNode::COGSgEffectNode () :   
    m_pRenderable(NULL),
    m_pPhysics(NULL),
    m_bActive(false)
{
}


COGSgEffectNode::COGSgEffectNode (IOGEffect* _pRenderable, IOGPhysicalObject* _pPhysics) :   
    m_pRenderable(_pRenderable),
    m_pPhysics(_pPhysics),
    m_bActive(true)
{
}


COGSgEffectNode::~COGSgEffectNode () 
{
    m_pRenderable = NULL;
    m_pPhysics = NULL;
}


// get world transform.
const OGMatrix& COGSgEffectNode::GetWorldTransform () const
{
    return m_pPhysics->GetWorldTransform();
}


// Get OBB
const IOGObb& COGSgEffectNode::GetOBB () const
{
    return m_pPhysics->GetOBB();
}


// update transform.
void COGSgEffectNode::Update (unsigned long _ElapsedTime)
{
	if (!m_bActive)
		return;

    m_pRenderable->Update(_ElapsedTime);
}


// render.
void COGSgEffectNode::Render ()
{
	if (!m_bActive)
		return;

    const OGMatrix& mWorld = m_pPhysics->GetWorldTransform();
    m_pRenderable->Render(mWorld);
}


// get physics.
IOGPhysicalObject* COGSgEffectNode::GetPhysics ()
{
    return m_pPhysics;
}


// Get active point
bool COGSgEffectNode::GetActivePoint (OGVec3& _point, const std::string& _Alias)
{
    return false;
}


// start animation.
void COGSgEffectNode::StartAnimation (const std::string& _Alias)
{
}


// Set active state
void COGSgEffectNode::Activate (bool _bActive)
{
	m_bActive = _bActive;
}


// Set billboard basis vectors.
void COGSgEffectNode::SetBillboardVectors (const OGVec3& _vLook, const OGVec3& _vUp, const OGVec3& _vRight)
{
    m_pRenderable->SetBillboardVectors(_vLook, _vUp, _vRight);
}
