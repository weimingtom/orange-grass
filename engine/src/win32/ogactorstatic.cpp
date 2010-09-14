/*
 *  ogactorstatic.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogactorstatic.h"
#include "IOGMath.h"


COGActorStatic::COGActorStatic(OGActorType _Type) : COGActor(_Type)
{
}


COGActorStatic::~COGActorStatic()
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
bool COGActorStatic::Create (const std::string& _ModelAlias,
							 const Vec3& _vPos,
							 const Vec3& _vRot,
							 const Vec3& _vScale)
{
	if (m_Type == OG_ACTOR_NONE)
	{
		OG_LOG_ERROR("Creating COGActorStatic from model %s failed, actor type is OG_ACTOR_NONE", _ModelAlias.c_str());
		return false;
	}

	m_pModel = GetResourceMgr()->GetModel(_ModelAlias);
	if (!m_pModel)
	{
		OG_LOG_ERROR("Creating COGActorStatic failed, cannot get model %s", _ModelAlias.c_str());
		return false;
	}

	m_pNode = GetSceneGraph()->CreateNode(m_pModel);
	if (!m_pNode)
	{
		OG_LOG_ERROR("Creating COGActorStatic failed, cannot create SG node");
		return false;
	}
	
    m_pPhysicalObject = GetPhysics()->CreateObject(OG_PHYSICS_STATIC, m_pModel->GetAABB());
    if (!m_pPhysicalObject)
	{
		OG_LOG_ERROR("Creating COGActorStatic failed, cannot create physical object");
        return false;
	}

	m_pPhysicalObject->SetWorldTransform(_vPos, _vRot, _vScale);
	return true;
}


// Adding to actor manager event handler.
void COGActorStatic::OnAddedToManager ()
{
    GetPhysics()->AddObject(m_pPhysicalObject);
	GetSceneGraph()->AddStaticNode(m_pNode, m_pModel->GetTexture());
    m_bAdded = true;
}
