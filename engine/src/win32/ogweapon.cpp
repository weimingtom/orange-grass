/*
 *  ogweapon.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogweapon.h"
#include "IOGMath.h"


COGWeapon::COGWeapon()
{
}


COGWeapon::~COGWeapon()
{
	m_MissileList.clear();
}


// Create weapon.
bool COGWeapon::Create (IOGActor* _pOwner, const std::string& _Alias)
{
    m_pOwner = _pOwner;
    Vec3 vStart = _pOwner->GetPhysicalObject()->GetPosition();
    for (int i = 0; i < 10; ++i)
    {
        IOGActor* pMissile = GetActorManager()->CreateActor(
            _Alias, 
            Vec3(0,0,0),
            Vec3(0,0,0),
            Vec3(1,1,1));
        GetActorManager()->AddActor(pMissile);
        m_MissileList.push_back((COGActorBullet*)pMissile);
    }
    return true;
}


// Fire missile.
void COGWeapon::Fire (const Vec3& _vTarget)
{
    std::list<COGActorBullet*>::iterator iter = m_MissileList.begin();
    for (; iter != m_MissileList.end(); ++iter)
    {
        COGActorBullet* pMissile = *iter;
        if (!pMissile->IsActive())
        {
            pMissile->SetOwner(m_pOwner, Vec3(-3,0,-7));
            pMissile->Fire(_vTarget);
            return;
        }
    }
}
