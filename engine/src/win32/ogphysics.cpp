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
#include <algorithm>


COGPhysics::COGPhysics ()
{
}


COGPhysics::~COGPhysics ()
{
	Clear();
}


// Clear scene graph
void COGPhysics::Clear ()
{
    std::list<IOGPhysicalObject*>::iterator iter;

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
}


// Create object
IOGPhysicalObject* COGPhysics::CreateObject (
	IOGPhysicalParams* _pParams,
	const IOGAabb& _Aabb )
{
	switch (_pParams->type)
	{
	case OG_PHYSICS_STATIC:
		{
			COGStaticPhysicalObject* pObj = new COGStaticPhysicalObject();
			pObj->Create (_Aabb, _pParams);
			return pObj;
		}
		break;

	case OG_PHYSICS_LANDBOT:
		{
			COGLandPhysicalObject* pObj = new COGLandPhysicalObject();
			pObj->Create (_Aabb, _pParams);
			return pObj;
		}
		break;

	case OG_PHYSICS_MISSILE:
		{
			COGMissilePhysicalObject* pObj = new COGMissilePhysicalObject();
			pObj->Create (_Aabb, _pParams);
			return pObj;
		}
		break;

	case OG_PHYSICS_AIRBOT:
		{
			COGAirPhysicalObject* pObj = new COGAirPhysicalObject();
			pObj->Create (_Aabb, _pParams);
			return pObj;
		}
		break;

	case OG_PHYSICS_PLAYER:
		{
			COGPlayerPhysicalObject* pObj = new COGPlayerPhysicalObject();
			pObj->Create (_Aabb, _pParams);
			return pObj;
		}
		break;

	default:
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
	case OG_PHYSICS_LANDBOT:
	case OG_PHYSICS_AIRBOT:
	case OG_PHYSICS_PLAYER:
		m_BotObjList.push_back(_pObject);
		break;

	default:
		break;
	}
}


// Remove object
void COGPhysics::RemoveObject (IOGPhysicalObject* _pObject)
{
	std::list<IOGPhysicalObject*>::iterator iter;

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
	case OG_PHYSICS_LANDBOT:
	case OG_PHYSICS_AIRBOT:
	case OG_PHYSICS_PLAYER:
		iter = std::find(m_BotObjList.begin(), m_BotObjList.end(), _pObject);
		if (iter != m_BotObjList.end())
		{
			OG_SAFE_DELETE((*iter));
			m_BotObjList.erase(iter);
		}
		break;

	default:
		break;
	}
}


// Update transforms.
void COGPhysics::Update (unsigned long _ElapsedTime)
{
    std::list<IOGPhysicalObject*>::iterator iter = m_BotObjList.begin();
    for (; iter != m_BotObjList.end(); ++iter)
    {
		(*iter)->Update(_ElapsedTime);
    }
}


// Update transforms for the whole scene.
void COGPhysics::UpdateAll (unsigned long _ElapsedTime)
{
    std::list<IOGPhysicalObject*>::iterator iter;

    for (iter = m_BotObjList.begin(); iter != m_BotObjList.end(); ++iter)
    {
		(*iter)->Update(_ElapsedTime);
    }

	for (iter = m_StaticObjList.begin(); iter != m_StaticObjList.end(); ++iter)
    {
		(*iter)->Update(_ElapsedTime);
    }
}


// Set level borders
void COGPhysics::SetLevelBorders (const Vec3& _vStart, const Vec3& _vFinish, float _fWidth)
{
    float fHalfW = _fWidth / 2.0f;
    m_vLeftBorder[0] = Vec3(_vStart.x - fHalfW, 0, _vStart.z);
    m_vLeftBorder[1] = Vec3(_vFinish.x - fHalfW, 0, _vFinish.z);
    m_vLeftBorder[2] = (m_vLeftBorder[1] - m_vLeftBorder[0]).normalized();

    m_vRightBorder[0] = Vec3(_vStart.x + fHalfW, 0, _vStart.z);
    m_vRightBorder[1] = Vec3(_vFinish.x + fHalfW, 0, _vFinish.z);
    m_vRightBorder[2] = (m_vRightBorder[1] - m_vRightBorder[0]).normalized();
}


// Get borders at point
void COGPhysics::GetBordersAtPoint (const Vec3& _vPos, Vec3& _vLeft, Vec3& _vRight)
{
    _vLeft = m_vLeftBorder[0] + m_vLeftBorder[2] * _vPos.z;
    _vRight = m_vRightBorder[0] + m_vRightBorder[2] * _vPos.z;
}
