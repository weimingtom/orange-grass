/*
 *  ogscenegraph.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogphysics.h"
#include "ogstaticphysicalobject.h"
#include "ogairphysicalobject.h"
#include "oglandphysicalobject.h"
#include "ogplayerphysicalobject.h"
#include "ogmissilephysicalobject.h"
#include "ogbonusphysicalobject.h"
#include <algorithm>


COGPhysics::COGPhysics ()
{
    m_pPlayer = NULL;

	m_StaticObjList.reserve(256);
	m_BotObjList.reserve(64);
	m_MissileObjList.reserve(64);
	m_BonusObjList.reserve(64);
}


COGPhysics::~COGPhysics ()
{
	Clear();
}


// Clear scene graph
void COGPhysics::Clear ()
{
	OG_SAFE_DELETE(m_pPlayer);

	TObjList::iterator iter;

	for (iter = m_StaticObjList.begin(); iter != m_StaticObjList.end(); ++iter)
	{
		OG_SAFE_DELETE((*iter));
	}
	m_StaticObjList.clear();

	for (iter = m_BotObjList.begin(); iter != m_BotObjList.end(); ++iter)
	{
		OG_SAFE_DELETE((*iter));
	}
	m_BotObjList.clear();

	for (iter = m_MissileObjList.begin(); iter != m_MissileObjList.end(); ++iter)
	{
		OG_SAFE_DELETE((*iter));
	}
	m_MissileObjList.clear();

	for (iter = m_BonusObjList.begin(); iter != m_BonusObjList.end(); ++iter)
	{
		OG_SAFE_DELETE((*iter));
	}
	m_BonusObjList.clear();
}


// Create object
IOGPhysicalObject* COGPhysics::CreateObject (
	IOGPhysicalParams* _pParams,
	const IOGAabb& _Aabb,
    void* _pActor)
{
	switch (_pParams->type)
	{
	case OG_PHYSICS_STATIC:
		{
			COGStaticPhysicalObject* pObj = new COGStaticPhysicalObject();
			pObj->Create (_Aabb, _pParams, _pActor);
			return pObj;
		}
		break;

	case OG_PHYSICS_LANDBOT:
		{
			COGLandPhysicalObject* pObj = new COGLandPhysicalObject();
			pObj->Create (_Aabb, _pParams, _pActor);
			return pObj;
		}
		break;

	case OG_PHYSICS_MISSILE:
		{
			COGMissilePhysicalObject* pObj = new COGMissilePhysicalObject();
			pObj->Create (_Aabb, _pParams, _pActor);
			return pObj;
		}
		break;

	case OG_PHYSICS_AIRBOT:
		{
			COGAirPhysicalObject* pObj = new COGAirPhysicalObject();
			pObj->Create (_Aabb, _pParams, _pActor);
			return pObj;
		}
		break;

	case OG_PHYSICS_PLAYER:
		{
			COGPlayerPhysicalObject* pObj = new COGPlayerPhysicalObject();
			pObj->Create (_Aabb, _pParams, _pActor);
			return pObj;
		}
		break;

	case OG_PHYSICS_BONUS:
		{
			COGBonusPhysicalObject* pObj = new COGBonusPhysicalObject();
			pObj->Create (_Aabb, _pParams, _pActor);
			return pObj;
		}
		break;
            
    case OG_PHYSICS_NONE:
        return NULL;
	}

	return NULL;
}


// Add object
void COGPhysics::AddObject (IOGPhysicalObject* _pObject)
{
	switch (_pObject->GetPhysicsType())
	{
	case OG_PHYSICS_STATIC:
		m_StaticObjList.push_back(_pObject);
		break;

	case OG_PHYSICS_MISSILE:
		m_MissileObjList.push_back(_pObject);
		break;

	case OG_PHYSICS_BONUS:
		m_BonusObjList.push_back(_pObject);
		break;

    case OG_PHYSICS_LANDBOT:
	case OG_PHYSICS_AIRBOT:
		m_BotObjList.push_back(_pObject);
		break;

    case OG_PHYSICS_PLAYER:
        m_pPlayer = _pObject;
        break;

	default:
		break;
	}
}


// Remove object
void COGPhysics::RemoveObject (IOGPhysicalObject* _pObject)
{
	TObjList::iterator iter;

	switch (_pObject->GetPhysicsType())
	{
	case OG_PHYSICS_STATIC:
		iter = std::find(m_StaticObjList.begin(), m_StaticObjList.end(), _pObject);
		if (iter != m_StaticObjList.end())
		{
			OG_SAFE_DELETE((*iter));
			m_StaticObjList.erase(iter);
		}
		break;

	case OG_PHYSICS_MISSILE:
		iter = std::find(m_MissileObjList.begin(), m_MissileObjList.end(), _pObject);
		if (iter != m_MissileObjList.end())
		{
			OG_SAFE_DELETE((*iter));
			m_MissileObjList.erase(iter);
		}
		break;

	case OG_PHYSICS_BONUS:
		iter = std::find(m_BonusObjList.begin(), m_BonusObjList.end(), _pObject);
		if (iter != m_BonusObjList.end())
		{
			OG_SAFE_DELETE((*iter));
			m_BonusObjList.erase(iter);
		}
		break;

    case OG_PHYSICS_LANDBOT:
	case OG_PHYSICS_AIRBOT:
		iter = std::find(m_BotObjList.begin(), m_BotObjList.end(), _pObject);
		if (iter != m_BotObjList.end())
		{
			OG_SAFE_DELETE((*iter));
			m_BotObjList.erase(iter);
		}
		break;

    case OG_PHYSICS_PLAYER:
        {
    	    OG_SAFE_DELETE(m_pPlayer);
        }
        break;

	default:
		break;
	}
}


// Update transforms.
void COGPhysics::Update (unsigned long _ElapsedTime)
{
    if (m_pPlayer)
    {
        m_pPlayer->Update(_ElapsedTime);
    }

    TObjList::iterator iter = m_BotObjList.begin();
    for (; iter != m_BotObjList.end(); ++iter)
    {
		(*iter)->Update(_ElapsedTime);
    }

    iter = m_BonusObjList.begin();
    for (; iter != m_BonusObjList.end(); ++iter)
    {
		(*iter)->Update(_ElapsedTime);
		(*iter)->CheckCollision(m_pPlayer);
    }

    iter = m_MissileObjList.begin();
    for (; iter != m_MissileObjList.end(); ++iter)
    {
        IOGPhysicalObject* pMissile = (*iter);
		pMissile->Update(_ElapsedTime);
        OGTeam team = ((IOGActor*)pMissile->GetActor())->GetTeam();
        switch (team)
        {
        case TEAM_PLAYER:
            {
                TObjList::iterator coll_iter = m_BotObjList.begin();
                for (; coll_iter != m_BotObjList.end(); ++coll_iter)
                {
                    if (pMissile->CheckCollision((*coll_iter)))
                        break;
                }
            }
            break;

        case TEAM_ENEMY:
            {
                if (pMissile->CheckCollision(m_pPlayer))
                {
                }
            }
            break;
                
        case TEAM_NEUTRAL:
            break;
        }
    }
}


// Update transforms for the whole scene.
void COGPhysics::UpdateAll (unsigned long _ElapsedTime)
{
    if (m_pPlayer)
    {
        m_pPlayer->Update(_ElapsedTime);
    }

    TObjList::iterator iter;
	for (iter = m_BotObjList.begin(); iter != m_BotObjList.end(); ++iter)
    {
		(*iter)->Update(_ElapsedTime);
    }

	for (iter = m_StaticObjList.begin(); iter != m_StaticObjList.end(); ++iter)
    {
		(*iter)->Update(_ElapsedTime);
    }

	for (iter = m_MissileObjList.begin(); iter != m_MissileObjList.end(); ++iter)
    {
		(*iter)->Update(_ElapsedTime);
    }

	for (iter = m_BonusObjList.begin(); iter != m_BonusObjList.end(); ++iter)
    {
		(*iter)->Update(_ElapsedTime);
    }
}


// Set level borders
void COGPhysics::SetLevelBorders (const OGVec3& _vStart, const OGVec3& _vFinish, float _fWidth)
{
    float fHalfW = _fWidth / 2.0f;
    m_vLeftBorder[0] = OGVec3(_vStart.x - fHalfW, 0, _vStart.z);
    m_vLeftBorder[1] = OGVec3(_vFinish.x - fHalfW, 0, _vFinish.z);
    m_vLeftBorder[2] = (m_vLeftBorder[1] - m_vLeftBorder[0]).normalized();

    m_vRightBorder[0] = OGVec3(_vStart.x + fHalfW, 0, _vStart.z);
    m_vRightBorder[1] = OGVec3(_vFinish.x + fHalfW, 0, _vFinish.z);
    m_vRightBorder[2] = (m_vRightBorder[1] - m_vRightBorder[0]).normalized();
}


// Get borders at point
void COGPhysics::GetBordersAtPoint (const OGVec3& _vPos, OGVec3& _vLeft, OGVec3& _vRight)
{
    _vLeft = m_vLeftBorder[0] + m_vLeftBorder[2] * _vPos.z;
    _vRight = m_vRightBorder[0] + m_vRightBorder[2] * _vPos.z;
}
