/*
 *  ogcamera.mm
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


// setup camera.
void COGCamera::Setup (const Vec3& _vPosition, const Vec3& _vDirection, const Vec3& _vUp)
{
	m_Position = _vPosition;
	m_Direction = _vDirection;
	m_Up = _vUp;
	m_bDirty = true;
}


// rotate view.
void COGCamera::RotateView (float _fAngle, const Vec3& _vAxis)
{
	Vec3 vNewView;
	Vec3 vView = m_Direction - m_Position;		
	float cosTheta = cosf(_fAngle);
	float sinTheta = sinf(_fAngle);
	
	vNewView.x  = (cosTheta + (1 - cosTheta) * _vAxis.x * _vAxis.x) * vView.x;
	vNewView.x += ((1 - cosTheta) * _vAxis.x * _vAxis.y - _vAxis.z * sinTheta)	* vView.y;
	vNewView.x += ((1 - cosTheta) * _vAxis.x * _vAxis.z + _vAxis.y * sinTheta)	* vView.z;
	
	vNewView.y  = ((1 - cosTheta) * _vAxis.x * _vAxis.y + _vAxis.z * sinTheta)	* vView.x;
	vNewView.y += (cosTheta + (1 - cosTheta) * _vAxis.y * _vAxis.y)	* vView.y;
	vNewView.y += ((1 - cosTheta) * _vAxis.y * _vAxis.z - _vAxis.x * sinTheta)	* vView.z;
	
	vNewView.z  = ((1 - cosTheta) * _vAxis.x * _vAxis.z - _vAxis.y * sinTheta)	* vView.x;
	vNewView.z += ((1 - cosTheta) * _vAxis.y * _vAxis.z + _vAxis.x * sinTheta)	* vView.y;
	vNewView.z += (cosTheta + (1 - cosTheta) * _vAxis.z * _vAxis.z)	* vView.z;
	
	m_Direction = m_Position + vNewView;
	m_bDirty = true;
}


// move camera in defined direction
void COGCamera::Strafe(float _fSpeed, const Vec3& _vDir)
{	
	m_Position.x += _vDir.x * _fSpeed;
	m_Position.z += _vDir.z * _fSpeed;
	m_Direction.x += _vDir.x * _fSpeed;
	m_Direction.z += _vDir.z * _fSpeed;
	m_bDirty = true;
}


// move camera forward/backward
void COGCamera::Move(float _fSpeed)
{
	Vec3 vVector = m_Direction - m_Position;
	vVector.normalize();
	
	m_Position.x += vVector.x * _fSpeed;
	m_Position.y += vVector.y * _fSpeed;
	m_Position.z += vVector.z * _fSpeed;
	m_Direction.x += vVector.x * _fSpeed;
	m_Direction.y += vVector.y * _fSpeed;
	m_Direction.z += vVector.z * _fSpeed;

	m_bDirty = true;
}


// update camera.
void COGCamera::Update ()
{
	if (m_bDirty)
	{
		MatrixLookAtRH(m_View, m_Position, m_Direction, m_Up);
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
    _vLeft = m_Direction + Vec3(-1.0f, 0, 0) * width;
    _vRight = m_Direction + Vec3(1.0f, 0, 0) * width;
}
