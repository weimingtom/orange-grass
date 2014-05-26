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
#include "Game.h"
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
void COGSgEffectNode::Render (IOGCamera* _pCamera, OGRenderPass _Pass)
{
    if (!m_bActive)
        return;

    const OGMatrix& mWorld = m_pPhysics->GetWorldTransform();
    m_pRenderable->Render(mWorld, _Pass);
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
