/*
 *  OGPhysics.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGPHYSICS_H_
#define OGPHYSICS_H_

#include "IOGPhysics.h"
#include <list>


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
    virtual void SetLevelBorders (const Vec3& _vStart, const Vec3& _vFinish, float _fWidth);

    // Get borders at point
    virtual void GetBordersAtPoint (const Vec3& _vPos, Vec3& _vLeft, Vec3& _vRight);

private:

    IOGPhysicalObject*              m_pPlayer;
	std::list<IOGPhysicalObject*>	m_StaticObjList;
	std::list<IOGPhysicalObject*>	m_BotObjList;
	std::list<IOGPhysicalObject*>	m_MissileObjList;
	std::list<IOGPhysicalObject*>	m_BonusObjList;

	Vec3    m_vLeftBorder[3];
    Vec3    m_vRightBorder[3];
};

#endif
