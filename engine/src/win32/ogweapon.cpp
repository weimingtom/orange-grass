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


COGWeapon::COGWeapon()
{
	m_pOwner = NULL;
	m_pWeaponParams = NULL;
    m_WeaponCoolDownMax = 200;
    m_WeaponCoolDown = m_WeaponCoolDownMax;
}


COGWeapon::~COGWeapon()
{
	m_MissileList.clear();
}


// Create weapon.
bool COGWeapon::Create (IOGActor* _pOwner, IOGWeaponParams* _pWeaponParams, const Vec3& _vLaunchPos)
{
    m_pOwner = _pOwner;
	m_pWeaponParams = _pWeaponParams;
    m_vLaunchPos = _vLaunchPos;
	m_WeaponCoolDownMax = m_pWeaponParams->cooldown;
    Vec3 vStart = _pOwner->GetPhysicalObject()->GetPosition();
    for (int i = 0; i < 10; ++i)
    {
        IOGActor* pMissile = GetActorManager()->CreateActor(
			m_pWeaponParams->actor, Vec3(0,0,0), Vec3(0,0,0), Vec3(1,1,1));
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
            pMissile->SetOwner(m_pOwner, m_vLaunchPos);
            pMissile->Fire(_vTarget);
            m_WeaponCoolDown = 0;
            return;
        }
    }
}


// Update actor.
void COGWeapon::Update (unsigned long _ElapsedTime)
{
    if (m_WeaponCoolDown < m_WeaponCoolDownMax)
    {
        m_WeaponCoolDown += _ElapsedTime;
        if (m_WeaponCoolDown >= m_WeaponCoolDownMax)
        {
            m_WeaponCoolDown = m_WeaponCoolDownMax;
        }
    }
}


// Is ready.
bool COGWeapon::IsReady () const
{
    return (m_WeaponCoolDown == m_WeaponCoolDownMax);
}
