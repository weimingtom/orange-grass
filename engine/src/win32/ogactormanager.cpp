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


// Get nearest intersected actor.
IOGActor* COGActorManager::GetNearestIntersectedActor (
    const Vec3& _LineStart, 
    const Vec3& _LineEnd )
{
    std::vector<IOGActor*> IntersectedList;
    std::vector<IOGActor*>::iterator iter = m_ActorsList.begin();
    for (; iter != m_ActorsList.end(); ++iter)
    {
        if ((*iter)->CheckIntersection_AABB(_LineStart, _LineEnd))
            IntersectedList.push_back(*iter);
    }
    if (IntersectedList.empty())
        return NULL;

    if (IntersectedList.size() == 1)
        return *IntersectedList.begin();

    std::vector<IOGActor*>::iterator inters_iter = IntersectedList.begin();
    IOGActor* pNearest = *inters_iter;
    float fDist = Dist3D(_LineStart, pNearest->GetSgNode()->GetTransformedAABB().GetCenter());
    ++iter;
    for (; inters_iter != IntersectedList.end(); ++inters_iter)
    {
        IOGActor* pCur = *inters_iter;
        float curDist = Dist3D(_LineStart, pCur->GetSgNode()->GetTransformedAABB().GetCenter());
        if (curDist < fDist)
        {
            fDist = curDist;
            pNearest = pCur;
        }
    }
    return pNearest;
}
