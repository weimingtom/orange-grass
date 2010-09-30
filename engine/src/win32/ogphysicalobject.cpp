/*
 *  ogphysicalobject.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogphysicalobject.h"


COGPhysicalObject::COGPhysicalObject () :	m_Type (OG_PHYSICS_NONE),
											m_pParams(NULL),
											m_bUpdated(false)
{
    m_vScaling = Vec3(1);
    m_vLook = Vec3(0,0,-1);
    m_vUp = Vec3(0,1,0);
    m_vRight = Vec3(1,0,0);
    m_vMove = Vec3(0,0,0);
    m_vTorque = Vec3(0,0,0);
}


COGPhysicalObject::~COGPhysicalObject ()
{
}


// get world transform.
const MATRIX& COGPhysicalObject::GetWorldTransform () const
{
	return m_mWorld;
}


// set world transform.
void COGPhysicalObject::SetWorldTransform (
	const Vec3& _vPos, 
	const Vec3& _vRot, 
	const Vec3& _vScale)
{
    m_vPosition = _vPos;
    m_vRotation = _vRot;
    m_vScaling = _vScale;
    m_vMove = Vec3(0,0,0);
    m_vTorque = Vec3(0,0,0);

	m_bUpdated = false;
}


// get position.
const Vec3& COGPhysicalObject::GetPosition () const
{
	return m_vPosition;
}


// get rotation.
const Vec3& COGPhysicalObject::GetRotation () const
{
	return m_vRotation;
}


// get scaling.
const Vec3& COGPhysicalObject::GetScaling () const
{
	return m_vScaling;
}


// get direction.
const Vec3& COGPhysicalObject::GetDirection () const
{
    return m_vLook;
}


// set position.
void COGPhysicalObject::SetPosition (const Vec3& _vPos)
{
	m_vPosition = _vPos;
	m_bUpdated = false;
}


// set rotation.
void COGPhysicalObject::SetRotation (const Vec3& _vRot)
{
	m_vRotation = _vRot;
	m_bUpdated = false;
}


// set scaling.
void COGPhysicalObject::SetScaling (const Vec3& _vScale)
{
	m_vScaling = _vScale;
	m_bUpdated = false;
}


// strafe.
void COGPhysicalObject::Strafe (float _fDir)
{
	m_bUpdated = false;
}


// accelerate.
void COGPhysicalObject::Accelerate (float _fDir)
{
	m_vMove += m_vLook * (_fDir * 0.01f);
    float fSpeed = m_vMove.length();
	if (fSpeed > m_pParams->fMaxSpeed)
    {
        m_vMove.normalize();
        m_vMove *= m_pParams->fMaxSpeed;
    }

	m_bUpdated = false;
}


// orient on point.
bool COGPhysicalObject::Orient (const Vec3& _vPoint)
{
    Vec3 vDirOnTarget = (_vPoint - m_vPosition).normalized();
    float fAngle = GetAngle(m_vLook, vDirOnTarget);
    if (fabsf(fAngle) < 0.1f)
    {
        return true;
    }

    if (fAngle > 0)
        m_vTorque.y -= 0.003f;
    else
        m_vTorque.y += 0.003f;

	m_bUpdated = false;
    return false;
}


// strabilize object.
bool COGPhysicalObject::Stabilize ()
{
    float fAngle = GetAngle(m_vLook, Vec3(0,0,-1.0f));
    if (fabsf(fAngle) < 0.05f)
    {
        return true;
    }

    if (fAngle > 0)
        m_vTorque.y -= 0.0006f;
    else
        m_vTorque.y += 0.0006f;

	m_bUpdated = false;
    return false;
}


// get physics type.
OGPhysicsType COGPhysicalObject::GetPhysicsType () const
{
	return m_Type;
}


// get OBB.
const IOGObb& COGPhysicalObject::GetOBB () const
{
    return m_Obb;
}


// Update transforms.
void COGPhysicalObject::Update (unsigned long _ElapsedTime)
{
	if (m_bUpdated)
		return;

    m_vPosition += m_vMove * (float)_ElapsedTime;
    m_vRotation += m_vTorque * (float)_ElapsedTime;
    m_vTorque = Vec3(0,0,0);

	WorldMatrixFromTransforms(m_mWorld, m_vPosition, m_vRotation, m_vScaling);
	m_Obb.UpdateTransform(m_mWorld);

    MatrixVec3Multiply(m_vLook, Vec3(0,0,-1), m_mWorld);
	m_vLook.normalize();
    MatrixVec3Multiply(m_vRight, Vec3(1,0,0), m_mWorld);
	m_vRight.normalize();
    MatrixVec3Multiply(m_vUp, Vec3(0,1,0), m_mWorld);
	m_vUp.normalize();

    m_bUpdated = true;
}
