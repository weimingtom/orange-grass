/*
 *  ogactorplayer.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "orangegrass.h"
#include "ogactorplayer.h"
#include "IOGMath.h"


COGActorPlayer::COGActorPlayer(OGActorType _Type) : COGActor(_Type)
{
}


COGActorPlayer::~COGActorPlayer()
{
	if (m_pNode)
	{
        if (m_bAdded)
		    GetSceneGraph()->RemoveNode(m_pNode);
        else
            OG_SAFE_DELETE(m_pNode);
		m_pNode = NULL;
	}
    if (m_pPhysicalObject)
    {
        if (m_bAdded)
            GetPhysics()->RemoveObject(m_pPhysicalObject);
        else
            OG_SAFE_DELETE(m_pPhysicalObject);
        m_pPhysicalObject = NULL;
    }
}


// Create actor.
bool COGActorPlayer::Create (const std::string& _ModelAlias,
                             const Vec3& _vPos,
                             const Vec3& _vRot,
                             const Vec3& _vScale)
{
	if (m_Type == OG_ACTOR_NONE)
		return false;

	m_pModel = GetResourceMgr()->GetModel(_ModelAlias);
	if (!m_pModel)
		return false;

	m_pNode = GetSceneGraph()->CreateNode(m_pModel);
	if (!m_pNode)
		return false;
	
    m_pPhysicalObject = GetPhysics()->CreateObject(OG_PHYSICS_PLAYER, m_pModel->GetAABB());
    if (!m_pPhysicalObject)
        return false;

	m_pPhysicalObject->SetWorldTransform(_vPos, _vRot, _vScale);
	return true;
}
