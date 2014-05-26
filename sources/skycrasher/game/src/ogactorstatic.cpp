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
#include "ogactorstatic.h"


COGActorStatic::COGActorStatic()
{
}


COGActorStatic::~COGActorStatic()
{
}


// Create actor.
bool COGActorStatic::Create (IOGActorParams* _pParams,
                             const OGVec3& _vPos,
                             const OGVec3& _vRot,
                             const OGVec3& _vScale)
{
    m_pParams = _pParams;

    m_pModel = GetResourceMgr()->GetModel(OG_RESPOOL_GAME, m_pParams->model_alias);
    
    m_pPhysicalObject = m_pPhysics->CreateObject(&m_pParams->physics, m_pModel->GetAABB(), this);
    m_pPhysicalObject->SetWorldTransform(_vPos, _vRot, _vScale);

    m_pNode = m_pSg->CreateNode(m_pModel, m_pPhysicalObject);

    return true;
}


// Adding to actor manager event handler.
void COGActorStatic::OnAddedToManager ()
{
    COGActor::OnAddedToManager();
    m_pSg->AddStaticNode(m_pNode);
}
