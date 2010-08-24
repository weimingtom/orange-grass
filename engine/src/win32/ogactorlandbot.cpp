/*
 *  ogactorlandbot.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogactorlandbot.h"
#include "IOGMath.h"


COGActorLandBot::COGActorLandBot(OGActorType _Type) : COGActor(_Type)
{
}


COGActorLandBot::~COGActorLandBot()
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
bool COGActorLandBot::Create (const std::string& _ModelAlias,
                              const Vec3& _vPos,
                              const Vec3& _vRot,
                              const Vec3& _vScale)
{
	if (m_Type == OG_ACTOR_NONE)
	{
		OG_LOG_ERROR("Creating COGActorLandBot from model %s failed, actor type is OG_ACTOR_NONE", _ModelAlias.c_str());
		return false;
	}

	m_pModel = GetResourceMgr()->GetModel(_ModelAlias);
	if (!m_pModel)
	{
		OG_LOG_ERROR("Creating COGActorLandBot failed, cannot get model %s", _ModelAlias.c_str());
		return false;
	}

	m_pNode = GetSceneGraph()->CreateNode(m_pModel);
	if (!m_pNode)
	{
		OG_LOG_ERROR("Creating COGActorLandBot failed, cannot create SG node");
		return false;
	}
	
    m_pPhysicalObject = GetPhysics()->CreateObject(OG_PHYSICS_LANDBOT, m_pModel->GetAABB());
    if (!m_pPhysicalObject)
	{
		OG_LOG_ERROR("Creating COGActorLandBot failed, cannot create physical object");
        return false;
	}

	m_pPhysicalObject->SetWorldTransform(_vPos, _vRot, _vScale);
	return true;
}
