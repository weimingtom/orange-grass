/*
 * OrangeGrass
 * Copyright (C) 2009 Vyacheslav Bogdanov.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/lgpl-3.0-standalone.html>.
 */
#ifndef OGPHYSICS_H_
#define OGPHYSICS_H_

#include "IOGPhysics.h"
#include <vector>


class COGPhysics : public IOGPhysics
{
public:
	COGPhysics ();
	virtual ~COGPhysics ();

	// Clear physics
	virtual void Clear ();

	// Create object
	virtual IOGPhysicalObject* CreateObject (
		IOGPhysicalParams* _pParams,
		const IOGAabb& _Aabb,
        void* _pActor);

	// Add object
	virtual void AddObject (IOGPhysicalObject* _pObject);

	// Remove object
	virtual void RemoveObject (IOGPhysicalObject* _pObject);

	// Update transforms.
	virtual void Update (unsigned long _ElapsedTime);

	// Update transforms for the whole scene.
	virtual void UpdateAll (unsigned long _ElapsedTime);

    // Set level borders
    virtual void SetLevelBorders (const OGVec3& _vStart, const OGVec3& _vFinish, float _fWidth);

    // Get borders at point
    virtual void GetBordersAtPoint (const OGVec3& _vPos, OGVec3& _vLeft, OGVec3& _vRight);

private:

	typedef std::vector<IOGPhysicalObject*>	TObjList;

    IOGPhysicalObject*	m_pPlayer;
	TObjList			m_StaticObjList;
	TObjList			m_BotObjList;
	TObjList			m_MissileObjList;
	TObjList			m_BonusObjList;

	OGVec3				m_vLeftBorder[3];
    OGVec3				m_vRightBorder[3];
};

#endif
