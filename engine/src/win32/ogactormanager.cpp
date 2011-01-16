/*
 *  ogactormanager.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogactormanager.h"
#include "ogactorstatic.h"
#include "ogactorlandbot.h"
#include "ogactorairbot.h"
#include "ogactorplayer.h"
#include "ogactorplasmamissile.h"
#include "ogactormissile.h"
#include "ogactorgaussray.h"
#include "ogactorbonus.h"
#include "IOGMath.h"
#include <algorithm>


COGActorManager::COGActorManager ()	: m_pPlayersActor(NULL)
{
	m_pGlobalVars = GetGlobalVars();
	m_fViewDistance = m_pGlobalVars->GetFVar("view_distance");
}


COGActorManager::~COGActorManager ()
{
	Clear();
}


// Clear actors manager
void COGActorManager::Clear ()
{
	OG_SAFE_DELETE(m_pPlayersActor);

    TActorsList::iterator iter = m_ActorsList.begin();
    for (; iter != m_ActorsList.end(); ++iter)
    {
		OG_SAFE_DELETE((*iter));
	}
	m_ActorsList.clear();

	TActorsList::iterator m_iter = m_MissileActorsList.begin();
    for (; m_iter != m_MissileActorsList.end(); ++m_iter)
    {
		OG_SAFE_DELETE((*m_iter));
	}
	m_MissileActorsList.clear();
}


// Create actor
IOGActor* COGActorManager::CreateActor (
	const std::string& _Alias,
	const Vec3& _vPos,
	const Vec3& _vRot,
    const Vec3& _vScale)
{
	IOGActorParams* pParams = GetActorParamsMgr()->GetParams(_Alias);
	if (!pParams)
	{
		OG_LOG_ERROR("Trying to create actor of unknown alias %s", _Alias.c_str());
		return NULL;
	}

	switch (pParams->type)
	{
	case OG_ACTOR_STATIC:
		{
			COGActorStatic* pActor = new COGActorStatic();
			if (pActor->Create(pParams, _vPos, _vRot, _vScale) == false)
			{
				OG_SAFE_DELETE(pActor);
				return NULL;
			}
			return pActor;
		}
		break;

	case OG_ACTOR_LANDBOT:
		{
			COGActorLandBot* pActor = new COGActorLandBot();
			if (pActor->Create(pParams, _vPos, _vRot, _vScale) == false)
			{
				OG_SAFE_DELETE(pActor);
				return NULL;
			}
			return pActor;
		}
		break;

	case OG_ACTOR_AIRBOT:
		{
			COGActorAirBot* pActor = new COGActorAirBot();
			if (pActor->Create(pParams, _vPos, _vRot, _vScale) == false)
			{
				OG_SAFE_DELETE(pActor);
				return NULL;
			}
			return pActor;
		}
		break;

	case OG_ACTOR_PLAYER:
		{
			COGActorPlayer* pActor = new COGActorPlayer();
			if (pActor->Create(pParams, _vPos, _vRot, _vScale) == false)
			{
				OG_SAFE_DELETE(pActor);
				return NULL;
			}
			return pActor;
		}
		break;

	case OG_ACTOR_PLASMAMISSILE:
		{
			COGActorPlasmaMissile* pActor = new COGActorPlasmaMissile();
			if (pActor->Create(pParams, _vPos, _vRot, _vScale) == false)
			{
				OG_SAFE_DELETE(pActor);
				return NULL;
			}
			return pActor;
		}
		break;

	case OG_ACTOR_MISSILE:
		{
			COGActorMissile* pActor = new COGActorMissile();
			if (pActor->Create(pParams, _vPos, _vRot, _vScale) == false)
			{
				OG_SAFE_DELETE(pActor);
				return NULL;
			}
			return pActor;
		}
		break;

	case OG_ACTOR_GAUSSRAY:
		{
			COGActorGaussRay* pActor = new COGActorGaussRay();
			if (pActor->Create(pParams, _vPos, _vRot, _vScale) == false)
			{
				OG_SAFE_DELETE(pActor);
				return NULL;
			}
			return pActor;
		}
		break;

	case OG_ACTOR_BONUS:
		{
			COGActorBonus* pActor = new COGActorBonus();
			if (pActor->Create(pParams, _vPos, _vRot, _vScale) == false)
			{
				OG_SAFE_DELETE(pActor);
				return NULL;
			}
			return pActor;
		}
		break;

	case OG_ACTOR_NONE:
	default:
		OG_LOG_ERROR("Trying to create actor of unknown type %d from model %s", pParams->type, _Alias.c_str());
		break;
	}

	return NULL;
}


// Add actor to the list.
void COGActorManager::AddActor (IOGActor* _pActor)
{
    _pActor->OnAddedToManager();

    switch (_pActor->GetType())
	{
	case OG_ACTOR_NONE:
		break;

	case OG_ACTOR_MISSILE:
	case OG_ACTOR_PLASMAMISSILE:
	case OG_ACTOR_GAUSSRAY:
	    m_MissileActorsList.push_back(_pActor);
		break;

	case OG_ACTOR_PLAYER:
		m_pPlayersActor = _pActor;
        break;

	default:
	    m_ActorsList.push_back(_pActor);
		break;
    }
}


// Destroy actor and remove from list.
void COGActorManager::DestroyActor (IOGActor* _pActor)
{
	if (_pActor == m_pPlayersActor)
	{
		OG_SAFE_DELETE(m_pPlayersActor);
		return;
	}

	TActorsList::iterator iter = std::find(m_ActorsList.begin(), m_ActorsList.end(), _pActor);
	if (iter != m_ActorsList.end())
	{
		OG_SAFE_DELETE((*iter));
		m_ActorsList.erase(iter);
	}
}


// Update actors.
void COGActorManager::Update (unsigned long _ElapsedTime)
{
	IOGCamera* pCamera = GetRenderer()->GetCamera();
	float fCameraZ = pCamera->GetPosition().z;

	m_pPlayersActor->Update(_ElapsedTime);

    TActorsList::iterator iter = m_ActorsList.begin();
    for (; iter != m_ActorsList.end(); ++iter)
    {
        IOGActor* pActor = (*iter);
		switch (pActor->GetType())
		{
		case OG_ACTOR_AIRBOT:
		case OG_ACTOR_LANDBOT:
		case OG_ACTOR_BONUS:
			{
				//float fObjectZ = pActor->GetPhysicalObject()->GetPosition().z;
				//if (fObjectZ <= fCameraZ)
				//{
				//	if ((fCameraZ - fObjectZ) < m_fViewDistance)
				//	{
				//		pActor->Activate(true);
				//	}
				//}
				//else
				//{
				//	if (pActor->IsActive())
				//		pActor->Activate(false);
				//}
				if (pCamera->GetFrustum().CheckObb(pActor->GetSgNode()->GetOBB()))
				{
					if (!pActor->IsActive())
						pActor->Activate(true);
				}
				else
				{
					if (pActor->IsActive())
						pActor->Activate(false);
				}
			}
			break;
                
        default:
            break;
		}
		pActor->Update(_ElapsedTime);
    }

    TActorsList::iterator m_iter = m_MissileActorsList.begin();
    for (; m_iter != m_MissileActorsList.end(); ++m_iter)
    {
		(*m_iter)->Update(_ElapsedTime);
	}
}


// Update actors in editor.
void COGActorManager::UpdateEditor (unsigned long _ElapsedTime)
{
    if (m_pPlayersActor)
	    m_pPlayersActor->UpdateEditor(_ElapsedTime);

	TActorsList::iterator iter = m_ActorsList.begin();
    for (; iter != m_ActorsList.end(); ++iter)
    {
        IOGActor* pActor = (*iter);
		pActor->Activate(true);
		pActor->UpdateEditor(_ElapsedTime);
    }

	TActorsList::iterator m_iter = m_MissileActorsList.begin();
    for (; m_iter != m_MissileActorsList.end(); ++m_iter)
    {
        IOGActor* pActor = (*m_iter);
		pActor->Activate(false);
	}
}


// Get nearest intersected actor.
IOGActor* COGActorManager::GetNearestIntersectedActor (
    const Vec3& _RayStart, 
    const Vec3& _RayDir )
{
    TActorsList IntersectedList;
    TActorsList::iterator iter = m_ActorsList.begin();
    for (; iter != m_ActorsList.end(); ++iter)
    {
        if ((*iter)->CheckIntersection(_RayStart, _RayDir))
            IntersectedList.push_back(*iter);
    }
    if (IntersectedList.empty())
        return NULL;

    if (IntersectedList.size() == 1)
        return *IntersectedList.begin();

    TActorsList::iterator inters_iter = IntersectedList.begin();
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
const IOGActorManager::TActorsList& COGActorManager::GetActorsList () const
{
    return m_ActorsList;
}


// Get player's actor.
IOGActor* COGActorManager::GetPlayersActor ()
{
	return m_pPlayersActor;
}
