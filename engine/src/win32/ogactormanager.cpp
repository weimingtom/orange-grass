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
	Clear();
}


// Clear actors manager
void COGActorManager::Clear ()
{
    std::vector<IOGActor*>::iterator iter = m_ActorsList.begin();
    for (; iter != m_ActorsList.end(); ++iter)
    {
		OG_SAFE_DELETE((*iter));
	}
	m_ActorsList.clear();
}


// Create actor
IOGActor* COGActorManager::CreateActor (
	OGActorType _Type,
	const std::string& _ModelAlias,
	const Vec3& _vPos,
	const Vec3& _vRot,
    const Vec3& _vScale)
{
	COGActor* pActor = new COGActor(_Type);
	if (pActor->Create(_ModelAlias, _vPos, _vRot, _vScale) == NULL)
	{
		OG_SAFE_DELETE(pActor);
		return NULL;
	}
	return pActor;
}


// Add actor to the list.
void COGActorManager::AddActor (IOGActor* _pActor)
{
    _pActor->OnAddedToManager();
	m_ActorsList.push_back(_pActor);
}


// Destroy actor and remove from list.
void COGActorManager::DestroyActor (IOGActor* _pActor)
{
	std::vector<IOGActor*>::iterator iter = std::find(m_ActorsList.begin(), m_ActorsList.end(), _pActor);
	if (iter != m_ActorsList.end())
	{
		OG_SAFE_DELETE((*iter));
		m_ActorsList.erase(iter);
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
    const Vec3& _RayStart, 
    const Vec3& _RayDir )
{
    std::vector<IOGActor*> IntersectedList;
    std::vector<IOGActor*>::iterator iter = m_ActorsList.begin();
    for (; iter != m_ActorsList.end(); ++iter)
    {
        if ((*iter)->CheckIntersection(_RayStart, _RayDir))
            IntersectedList.push_back(*iter);
    }
    if (IntersectedList.empty())
        return NULL;

    if (IntersectedList.size() == 1)
        return *IntersectedList.begin();

    std::vector<IOGActor*>::iterator inters_iter = IntersectedList.begin();
    IOGActor* pNearest = *inters_iter;
    float fDist = Dist3D(_RayStart, pNearest->GetSgNode()->GetOBB().m_vCenter);
    ++inters_iter;
    for (; inters_iter != IntersectedList.end(); ++inters_iter)
    {
        IOGActor* pCur = *inters_iter;
        float curDist = Dist3D(_RayStart, pCur->GetSgNode()->GetOBB().m_vCenter);
        if (curDist < fDist)
        {
            fDist = curDist;
            pNearest = pCur;
        }
    }
    return pNearest;
}


// Get actors list.
const std::vector<IOGActor*>& COGActorManager::GetActorsList () const
{
    return m_ActorsList;
}
