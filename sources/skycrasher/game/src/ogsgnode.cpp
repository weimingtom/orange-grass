/*
 *  ogsgnode.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "Game.h"
#include "ogsgnode.h"
#include "oganimationcontroller.h"


COGSgNode::COGSgNode () :
    m_pRenderable(NULL),
    m_pPhysics(NULL),
    m_pAnimator(NULL),
    m_bActive(false)
{
    m_AnimFrame = 0;
	m_fSpin = 0.0f;
}


COGSgNode::COGSgNode (IOGModel* _pRenderable, IOGPhysicalObject* _pPhysics) :   
    m_pRenderable(_pRenderable),
    m_pPhysics(_pPhysics),
    m_pAnimator(NULL),
    m_bActive(true)
{
    m_pAnimator = new COGAnimationController();
    m_AnimFrame = 0;
	m_fSpin = 0.0f;
	
	unsigned int NumOBBs = _pRenderable->GetNumRenderables();
	m_TransformedOBBs.reserve(_pRenderable->GetNumRenderables());
	for (unsigned int i = 0; i < NumOBBs; ++i)
	{
		IOGObb obb;
		m_TransformedOBBs.push_back(obb);
	}
}


COGSgNode::~COGSgNode () 
{
	m_TransformedOBBs.clear();
    m_pRenderable = NULL;
    m_pPhysics = NULL;
    OG_SAFE_DELETE(m_pAnimator);
}


// get world transform.
const OGMatrix& COGSgNode::GetWorldTransform () const
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

	m_fSpin += 0.5f;

    if (m_pAnimator->GetCurrentAnimation())
    {
        m_pAnimator->UpdateAnimation(_ElapsedTime);
        m_AnimFrame = (unsigned int)m_pAnimator->GetCurrentAnimationProgress();
	
		const OGMatrix& mWorld = m_pPhysics->GetWorldTransform();
		unsigned int NumOBBs = m_TransformedOBBs.size();
		for (unsigned int i = 0; i < NumOBBs; ++i)
		{
			m_pRenderable->GetTransformedOBB(m_TransformedOBBs[i], i, m_AnimFrame, mWorld);
		}
    }
}


// render.
void COGSgNode::Render ()
{
	if (!m_bActive)
		return;

    const OGMatrix& mWorld = m_pPhysics->GetWorldTransform();
    m_pRenderable->Render(mWorld, m_AnimFrame);
}


// render transparent parts.
void COGSgNode::RenderTransparent ()
{
	if (!m_bActive)
		return;

    const OGMatrix& mWorld = m_pPhysics->GetWorldTransform();
    m_pRenderable->RenderTransparentParts(mWorld, m_AnimFrame, m_fSpin);
}


// get physics.
IOGPhysicalObject* COGSgNode::GetPhysics ()
{
    return m_pPhysics;
}


// Get active point
bool COGSgNode::GetActivePoint (OGVec3& _point, const std::string& _Alias)
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
