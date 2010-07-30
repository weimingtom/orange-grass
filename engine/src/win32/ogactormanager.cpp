/*
 *  ogactormanager.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "orangegrass.h"
#include "ogactormanager.h"
#include "ogactor.h"
#include "IOGMath.h"
#include <algorithm>


COGActorManager::COGActorManager ()
{
}


COGActorManager::~COGActorManager ()
{
    std::vector<IOGActor*>::iterator iter = m_ActorsList.begin();
    for (; iter != m_ActorsList.end(); ++iter)
    {
		OG_SAFE_DELETE((*iter));
	}
	m_ActorsList.clear();
}


// Create static actor
IOGActor* COGActorManager::CreateStaticActor (
	const char* _pModelAlias,
	const MATRIX& _mWorld)
{
	COGActor* pActor = new COGActor(OG_ACTOR_STATIC);
	if (pActor->Create(_pModelAlias, _mWorld) == NULL)
	{
		OG_SAFE_DELETE(pActor);
		return NULL;
	}

	m_ActorsList.push_back(pActor);
	return pActor;
}


// Create bot actor
IOGActor* COGActorManager::CreateBotActor (
	const char* _pModelAlias,
	const Vec3& _vPos,
	const Vec3& _vRot)
{
	COGActor* pActor = new COGActor(OG_ACTOR_LANDBOT);
	if (pActor->Create(_pModelAlias, _vPos, _vRot) == NULL)
	{
		OG_SAFE_DELETE(pActor);
		return NULL;
	}

	m_ActorsList.push_back(pActor);
	return pActor;
}


// Destroy actor and remove from list.
void COGActorManager::DestroyActor (IOGActor* _pActor)
{
	std::vector<IOGActor*>::iterator iter = std::find(m_ActorsList.begin(), m_ActorsList.end(), _pActor);
	if (iter != m_ActorsList.end())
	{
		m_ActorsList.erase(iter);
		OG_SAFE_DELETE((*iter));	
	}
}


// Update actors.
void COGActorManager::Update (int _ElapsedTime)
{
    std::vector<IOGActor*>::iterator iter = m_ActorsList.begin();
    for (; iter != m_ActorsList.end(); ++iter)
    {
		(*iter)->Update(_ElapsedTime);
    }
}
