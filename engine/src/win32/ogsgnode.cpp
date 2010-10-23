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
#include "oganimationcontroller.h"


COGSgNode::COGSgNode () :   m_pRenderable(NULL),
                            m_pPhysics(NULL),
                            m_pAnimator(NULL),
							m_bActive(false)
{
    m_AnimFrame = 0;
}


COGSgNode::COGSgNode (IOGRenderable* _pRenderable,
                      IOGPhysicalObject* _pPhysics) :   m_pRenderable(_pRenderable),
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
    m_pRenderable->Update(_ElapsedTime);
}


// render.
void COGSgNode::Render ()
{
	if (!m_bActive)
		return;

    const MATRIX& mWorld = m_pPhysics->GetWorldTransform();
    m_pRenderable->Render(mWorld, m_AnimFrame);
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


// Get active point
bool COGSgNode::GetActivePoint (Vec3& _point, const std::string& _Alias)
{
    IOGActivePoint pt;
    if (!m_pRenderable->GetActivePoint(pt, _Alias, m_AnimFrame))
        return false;

    //MATRIX mModel;
    //MatrixMultiply(mModel, pt.mLocalTM, m_pPhysics->GetWorldTransform());
    //_point = pt.pos + Vec3(mModel.f[12], mModel.f[13], mModel.f[14]);
    //MatrixVec3Multiply(_point, pt.pos, mModel);
    //MatrixVec3Multiply(_point, pt.pos, pt.mLocalTM);

    //VECTOR4 v_in, v_out;
    //v_in.x = pt.pos.x; v_in.y = pt.pos.y; v_in.z = pt.pos.z; v_in.w = 1.0f;
    //MatrixVec4Multiply(v_out, v_in, m_pPhysics->GetWorldTransform());
    //_point.x = v_out.x; _point.y = v_out.y; _point.z = v_out.z;
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
