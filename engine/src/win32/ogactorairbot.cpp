/*
 *  ogactorairbot.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogactorairbot.h"
#include "IOGMath.h"


COGActorAirBot::COGActorAirBot(OGActorType _Type) : COGActor(_Type)
{
}


COGActorAirBot::~COGActorAirBot()
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
bool COGActorAirBot::Create (const std::string& _ModelAlias,
                             const Vec3& _vPos,
                             const Vec3& _vRot,
                             const Vec3& _vScale)
{
	if (m_Type == OG_ACTOR_NONE)
	{
		OG_LOG_ERROR("Creating COGActorAirBot from model %s failed, actor type is OG_ACTOR_NONE", _ModelAlias.c_str());
		return false;
	}

	m_pModel = GetResourceMgr()->GetModel(_ModelAlias);
	if (!m_pModel)
	{
		OG_LOG_ERROR("Creating COGActorAirBot failed, cannot get model %s", _ModelAlias.c_str());
		return false;
	}

	m_pNode = GetSceneGraph()->CreateNode(m_pModel);
	if (!m_pNode)
	{
		OG_LOG_ERROR("Creating COGActorAirBot failed, cannot create SG node");
		return false;
	}
	
    m_pPhysicalObject = GetPhysics()->CreateObject(OG_PHYSICS_AIRBOT, m_pModel->GetAABB());
    if (!m_pPhysicalObject)
	{
		OG_LOG_ERROR("Creating COGActorAirBot failed, cannot create physical object");
        return false;
	}

	m_pPhysicalObject->SetWorldTransform(_vPos, _vRot, _vScale);
	return true;
}
