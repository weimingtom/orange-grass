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
    std::vector<IOGPhysicalObject*>::iterator iter = m_ObjList.begin();
    for (; iter != m_ObjList.end(); ++iter)
    {
		OG_SAFE_DELETE((*iter));
	}
	m_ObjList.clear();
}


// Create object
IOGPhysicalObject* COGPhysics::CreateObject (
	OGPhysicsType _Type,
	const IOGAabb& _Aabb )
{
	switch (_Type)
	{
	case OG_PHYSICS_STATIC:
		{
			COGStaticPhysicalObject* pObj = new COGStaticPhysicalObject();
			pObj->Create (_Aabb);
			return pObj;
		}
		break;

	case OG_PHYSICS_LANDBOT:
		{
			COGLandPhysicalObject* pObj = new COGLandPhysicalObject();
			pObj->Create (_Aabb);
			return pObj;
		}
		break;

	case OG_PHYSICS_AIRBOT:
		{
			COGAirPhysicalObject* pObj = new COGAirPhysicalObject();
			pObj->Create (_Aabb);
			return pObj;
		}
		break;

	case OG_PHYSICS_PLAYER:
		{
			COGPlayerPhysicalObject* pObj = new COGPlayerPhysicalObject();
			pObj->Create (_Aabb);
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
    m_ObjList.push_back(_pObject);
}


// Remove object
void COGPhysics::RemoveObject (IOGPhysicalObject* _pObject)
{
	std::vector<IOGPhysicalObject*>::iterator iter = std::find(m_ObjList.begin(), m_ObjList.end(), _pObject);
	if (iter != m_ObjList.end())
	{
		OG_SAFE_DELETE((*iter));
		m_ObjList.erase(iter);
	}
}


// Update transforms.
void COGPhysics::Update (unsigned long _ElapsedTime)
{
    std::vector<IOGPhysicalObject*>::iterator iter = m_ObjList.begin();
    for (; iter != m_ObjList.end(); ++iter)
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
