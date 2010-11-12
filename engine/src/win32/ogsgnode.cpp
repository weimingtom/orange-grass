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
#include "oganimationcontroller.h"


COGSgNode::COGSgNode () :
    m_pRenderable(NULL),
    m_pPhysics(NULL),
    m_pAnimator(NULL),
    m_bActive(false)
{
    m_AnimFrame = 0;
}


COGSgNode::COGSgNode (IOGModel* _pRenderable, IOGPhysicalObject* _pPhysics) :   
    m_pRenderable(_pRenderable),
    m_pPhysics(_pPhysics),
    m_pAnimator(NULL),
    m_bActive(true)
{
    m_pAnimator = new COGAnimationController();
    m_AnimFrame = 0;
}


COGSgNode::~COGSgNode () 
{
    m_pRenderable = NULL;
    m_pPhysics = NULL;
    OG_SAFE_DELETE(m_pAnimator);
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
	if (!m_bActive)
		return;

    if (m_pAnimator->GetCurrentAnimation())
    {
        m_pAnimator->UpdateAnimation(_ElapsedTime);
        m_AnimFrame = (unsigned int)m_pAnimator->GetCurrentAnimationProgress();
    }
}


// render.
void COGSgNode::Render ()
{
	if (!m_bActive)
		return;

    const MATRIX& mWorld = m_pPhysics->GetWorldTransform();
    m_pRenderable->Render(mWorld, m_AnimFrame);
}


// get physics.
IOGPhysicalObject* COGSgNode::GetPhysics ()
{
    return m_pPhysics;
}


// Get active point
bool COGSgNode::GetActivePoint (Vec3& _point, const std::string& _Alias)
{
    IOGActivePoint pt;
    if (!m_pRenderable->GetActivePoint(pt, _Alias, m_AnimFrame))
        return false;

    _point = pt.pos;
    return true;
}


// start animation.
void COGSgNode::StartAnimation (const std::string& _Alias)
{
    m_AnimFrame = 0;
    IOGAnimation* pAnim = m_pRenderable->GetAnimation(_Alias);
    if (pAnim)
        m_pAnimator->StartAnimation(pAnim);
}


// Set active state
void COGSgNode::Activate (bool _bActive)
{
	m_bActive = _bActive;
}
