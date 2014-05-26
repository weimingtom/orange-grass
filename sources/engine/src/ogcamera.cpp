/*
 * OrangeGrass
 * Copyright (C) 2009 Vyacheslav Bogdanov.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/lgpl-3.0-standalone.html>.
 */
#include "ogcamera.h"


COGCamera::COGCamera ()
    : m_bDirty(true)
{
}


COGCamera::~COGCamera ()
{
}


// setup camera viewport.
void COGCamera::SetupViewport (const OGMatrix& _mProjection)
{
    m_Projection = _mProjection;
}


// setup camera.
void COGCamera::Setup (const OGVec3& _vPosition, const OGVec3& _vTarget, const OGVec3& _vUp)
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
void COGCamera::Strafe(float _fSpeed, const OGVec3& _vDir)
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
        m_Frustum.Update(m_ViewProj);
        m_bDirty = false;
    }
}


// get camera view matrix.
const OGMatrix& COGCamera::GetViewMatrix () const
{
    return m_View;
}


// get left and right edges.
void COGCamera::GetEdges (OGVec3& _vLeft, OGVec3& _vRight, float _fFOV, float _fDist)
{
    float width = tanf(_fFOV / 2) * _fDist;
    _vLeft = m_Target + OGVec3(-1.0f, 0, 0) * width;
    _vRight = m_Target + OGVec3(1.0f, 0, 0) * width;
}
