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
    m_vScaling = Vec3(1);
    m_Obb.Create (_pRenderable->GetAABB());
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
void COGSgNode::SetWorldTransform (const Vec3& _vPos, const Vec3& _vRot, const Vec3& _vScale)
{
    m_vPosition = _vPos;
    m_vRotation = _vRot;
    m_vScaling = _vScale;
}


// get position.
const Vec3& COGSgNode::GetPosition () const
{
    return m_vPosition;
}


// get rotation.
const Vec3& COGSgNode::GetRotation () const
{
    return m_vRotation;
}


// get scaling.
const Vec3& COGSgNode::GetScaling () const
{
    return m_vScaling;
}


// set position.
void COGSgNode::SetPosition (const Vec3& _vPos)
{
    m_vPosition = _vPos;
}

// set rotation.
void COGSgNode::SetRotation (const Vec3& _vRot)
{
    m_vRotation = _vRot;
}


// set scaling.
void COGSgNode::SetScaling (const Vec3& _vScale)
{
    m_vScaling = _vScale;
}


// Get transformed AABB
const IOGAabb& COGSgNode::GetTransformedAABB () const
{
	return m_TransformedAabb;
}


// Get OBB
const IOGObb& COGSgNode::GetOBB () const
{
    return m_Obb;
}


// Update transforms.
void COGSgNode::Update (int _ElapsedTime)
{
    WorldMatrixFromTransforms(m_mWorld, m_vPosition, m_vRotation, m_vScaling);

	const IOGAabb& origAABB = m_pRenderable->GetAABB();
	m_TransformedAabb.SetMinMax(origAABB.GetMin(), origAABB.GetMax());
	m_TransformedAabb.UpdateTransform(m_mWorld);

    m_Obb.UpdateTransform(m_mWorld);
}


// get renderable.
IOGRenderable* COGSgNode::GetRenderable ()
{
    return m_pRenderable;
}
