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
    virtual void SetLevelBorders (const Vec3& _vStart, const Vec3& _vFinish, float _fWidth);

    // Get borders at point
    virtual void GetBordersAtPoint (const Vec3& _vPos, Vec3& _vLeft, Vec3& _vRight);

private:

	typedef std::vector<IOGPhysicalObject*>	TObjList;

    IOGPhysicalObject*	m_pPlayer;
	TObjList			m_StaticObjList;
	TObjList			m_BotObjList;
	TObjList			m_MissileObjList;
	TObjList			m_BonusObjList;

	Vec3				m_vLeftBorder[3];
    Vec3				m_vRightBorder[3];
};

#endif
