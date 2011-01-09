/*
 *  ogcamera.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 14.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogcamera.h"


COGCamera::COGCamera () : m_bDirty(true)
{
}


COGCamera::~COGCamera ()
{
}


// setup camera viewport.
void COGCamera::SetupViewport (const MATRIX& _mProjection, float _fFOV)
{
	m_Projection = _mProjection;
	m_fFOV = _fFOV;
}


// setup camera.
void COGCamera::Setup (const Vec3& _vPosition, const Vec3& _vTarget, const Vec3& _vUp)
{
	m_Position = _vPosition;
	m_Target = _vTarget;
	m_Up = _vUp;
	m_Direction = m_Target - m_Position;
	m_Direction.normalize();
	m_Right = m_Up.cross(m_Direction);
	m_Right.normalize();
	m_bDirty = true;
}


// move camera in defined direction
void COGCamera::Strafe(float _fSpeed, const Vec3& _vDir)
{	
	m_Position.x += _vDir.x * _fSpeed;
	m_Position.z += _vDir.z * _fSpeed;
	m_Target.x += _vDir.x * _fSpeed;
	m_Target.z += _vDir.z * _fSpeed;
	m_bDirty = true;
}


// move camera forward/backward
void COGCamera::Move(float _fSpeed)
{
	m_Position.x += m_Direction.x * _fSpeed;
	m_Position.y += m_Direction.y * _fSpeed;
	m_Position.z += m_Direction.z * _fSpeed;
	m_Target.x += m_Direction.x * _fSpeed;
	m_Target.y += m_Direction.y * _fSpeed;
	m_Target.z += m_Direction.z * _fSpeed;

	m_bDirty = true;
}


// update camera.
void COGCamera::Update ()
{
	if (m_bDirty)
	{
		MatrixLookAtRH(m_View, m_Position, m_Target, m_Up);
		MatrixMultiply(m_ViewProj, m_View, m_Projection);
		m_Frustum.Update(m_ViewProj, true);
		m_bDirty = false;
	}
}


// get camera view matrix.
const MATRIX& COGCamera::GetViewMatrix () const
{
	return m_View;
}


// get left and right edges.
void COGCamera::GetEdges (Vec3& _vLeft, Vec3& _vRight, float _fFOV, float _fDist)
{
    float width = tanf(_fFOV / 2) * _fDist;
    _vLeft = m_Target + Vec3(-1.0f, 0, 0) * width;
    _vRight = m_Target + Vec3(1.0f, 0, 0) * width;
}
