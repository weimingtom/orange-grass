/*
 *  ogphysicalobject.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "Game.h"
#include "ogphysicalobject.h"


COGPhysicalObject::COGPhysicalObject () :	m_Type (OG_PHYSICS_NONE),
											m_pParams(NULL),
                                            m_pListener(NULL),
                                            m_pActor(NULL),
                                            m_bUpdated(false)
{
    m_fStrafe = 0.0f;
    m_vScaling = OGVec3(1);
    m_vLook = OGVec3(0,0,-1);
    m_vUp = OGVec3(0,1,0);
    m_vRight = OGVec3(1,0,0);
    m_vMove = OGVec3(0,0,0);
	m_vAcceleration = OGVec3(0,0,0);
    m_vTorque = OGVec3(0,0,0);
}


COGPhysicalObject::~COGPhysicalObject ()
{
}


// add collision handler.
void COGPhysicalObject::AddCollisionListener (IOGCollisionListener* _pListener)
{
    m_pListener = _pListener;
}


// check collision.
bool COGPhysicalObject::CheckCollision (IOGPhysicalObject* _pObject)
{
    return false;
}


// respond on a collision.
bool COGPhysicalObject::RespondOnCollision (const IOGCollision& _Collision)
{
	if (!m_pListener)
		return false;

	return m_pListener->OnCollision(_Collision);
}


// Set active state.
void COGPhysicalObject::Activate (bool _bActive)
{
	m_bActive = _bActive;
	m_bUpdated = !m_bActive;
}


// get world transform.
const OGMatrix& COGPhysicalObject::GetWorldTransform () const
{
	return m_mWorld;
}


// set world transform.
void COGPhysicalObject::SetWorldTransform (
	const OGVec3& _vPos, 
	const OGVec3& _vRot, 
	const OGVec3& _vScale)
{
    m_vPosition = _vPos;
    m_vRotation = _vRot;
    m_vScaling = _vScale;
    m_vMove = OGVec3(0,0,0);
	m_vAcceleration = OGVec3(0,0,0);
    m_vTorque = OGVec3(0,0,0);
    m_fStrafe = 0.0f;

	WorldMatrixFromTransforms(m_mWorld, m_vPosition, m_vRotation, m_vScaling);
	m_Obb.UpdateTransform(m_mWorld);
	UpdateDirections();

	m_bUpdated = false;
}


// get position.
const OGVec3& COGPhysicalObject::GetPosition () const
{
	return m_vPosition;
}


// get rotation.
const OGVec3& COGPhysicalObject::GetRotation () const
{
	return m_vRotation;
}


// get scaling.
const OGVec3& COGPhysicalObject::GetScaling () const
{
	return m_vScaling;
}


// get direction.
const OGVec3& COGPhysicalObject::GetDirection () const
{
    return m_vLook;
}


// set position.
void COGPhysicalObject::SetPosition (const OGVec3& _vPos)
{
	m_vPosition = _vPos;
	m_bUpdated = false;
}


// set rotation.
void COGPhysicalObject::SetRotation (const OGVec3& _vRot)
{
	m_vRotation = _vRot;
	m_bUpdated = false;
}


// set scaling.
void COGPhysicalObject::SetScaling (const OGVec3& _vScale)
{
	m_vScaling = _vScale;
	m_bUpdated = false;
}


// strafe.
void COGPhysicalObject::Strafe (float _fDir)
{
    m_fStrafe += _fDir;
	m_bUpdated = false;
}


// accelerate.
void COGPhysicalObject::Accelerate (float _fDir)
{
	m_vAcceleration += m_vLook * (_fDir * m_pParams->fAcceleration);
    float fSpeed = m_vAcceleration.length();
	if (fSpeed > m_pParams->fMaxSpeed)
    {
        m_vAcceleration.normalize();
        m_vAcceleration *= m_pParams->fMaxSpeed;
    }

	m_bUpdated = false;
}


// move.
void COGPhysicalObject::Move (const OGVec3& _vDir)
{
	m_vMove = _vDir * m_pParams->fMaxSpeed;
	m_bUpdated = false;
}


// orient on point.
bool COGPhysicalObject::Orient (const OGVec3& _vPoint)
{
	bool bDone = false;
    OGVec3 vDirOnTarget = (_vPoint - m_vPosition).normalized();
    float fAngle = GetAngle(m_vLook, vDirOnTarget);

	float fTorqueAngle = (fAngle > 0) ? -m_pParams->fTorque : m_pParams->fTorque;
    if (fabsf(fAngle) < m_pParams->fTorque)
    {
		fTorqueAngle = (fAngle > 0) ? -fAngle : fAngle;
		bDone = true;
    }

    m_vTorque.y += fTorqueAngle;
	m_bUpdated = false;
    return bDone;
}


// strabilize object.
bool COGPhysicalObject::Stabilize ()
{
	bool bDone = false;
    float fAngle = GetAngle(m_vLook, OGVec3(0,0,-1.0f));

	float fTorqueAngle = (fAngle > 0) ? -m_pParams->fTorque : m_pParams->fTorque;
    if (fabsf(fAngle) < m_pParams->fTorque)
    {
		fTorqueAngle = (fAngle > 0) ? -fAngle : fAngle;
		m_vRotation.y = 0.0f;
		bDone = true;
    }

    m_vTorque.y += fTorqueAngle;
	m_bUpdated = false;
    return bDone;
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

    m_vPrevPosition = m_vPosition;

    m_vPosition += m_vMove;
    m_vPosition += m_vAcceleration;
    m_vPosition.x += m_fStrafe * m_pParams->fStrafeMaxSpeed;

	m_vRotation += m_vTorque;
    m_vRotation.z += m_fStrafe * m_pParams->fRollSpeed;
    m_vRotation.x += fabsf(m_fStrafe) * m_pParams->fPitchSpeed;

	OG_CLAMP(m_vRotation.x, -m_pParams->fMaxPitchAngle, m_pParams->fMaxPitchAngle);
    OG_CLAMP(m_vRotation.z, -m_pParams->fMaxRollAngle, m_pParams->fMaxRollAngle);

	BoundPosition();

	WorldMatrixFromTransforms(m_mWorld, m_vPosition, m_vRotation, m_vScaling);
	m_Obb.UpdateTransform(m_mWorld);

	UpdateDirections();
	StabilizeRotation();

    m_vTorque = OGVec3(0,0,0);
	m_vMove = OGVec3(0,0,0);
    m_fStrafe /= 1.08f;

    m_bUpdated = true;
}


// Update directions.
void COGPhysicalObject::UpdateDirections ()
{
    OGMatrix mR;
    MatrixRotationY(mR, m_vRotation.y);

    MatrixVec3Multiply(m_vLook, OGVec3(0,0,-1), mR);
	m_vLook.normalize();
    MatrixVec3Multiply(m_vRight, OGVec3(1,0,0), mR);
	m_vRight.normalize();
    MatrixVec3Multiply(m_vUp, OGVec3(0,1,0), mR);
	m_vUp.normalize();
}


// Bound object position to be in level space.
bool COGPhysicalObject::BoundPosition ()
{
	return false;
}


// Stabilize rotation.
bool COGPhysicalObject::StabilizeRotation ()
{
	return false;
}
