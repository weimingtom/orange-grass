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
bool COGWeapon::Create (IOGActor* _pOwner, IOGWeaponParams* _pWeaponParams)
{
    m_pOwner = _pOwner;
	m_pWeaponParams = _pWeaponParams;

	m_WeaponCoolDownMax = m_pWeaponParams->cooldown;
    Vec3 vStart = _pOwner->GetPhysicalObject()->GetPosition();
	m_MissileList.reserve(10);
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
void COGWeapon::Fire ()
{
    Vec3 launches[3];
    int NumLaunch = 0;

    switch (m_pWeaponParams->pos)
    {
    case OG_WEAPONPOS_LEFT:
        NumLaunch = 1;
        m_pOwner->GetSgNode()->GetActivePoint(launches[0], "actpointweapon01");
        break;

    case OG_WEAPONPOS_RIGHT:
        NumLaunch = 1;
        m_pOwner->GetSgNode()->GetActivePoint(launches[0], "actpointweapon02");
        break;

    case OG_WEAPONPOS_CENTER:
        NumLaunch = 1;
        m_pOwner->GetSgNode()->GetActivePoint(launches[0], "actpointweapon03");
        break;

    case OG_WEAPONPOS_LEFTRIGHT:
        NumLaunch = 2;
        m_pOwner->GetSgNode()->GetActivePoint(launches[0], "actpointweapon01");
        m_pOwner->GetSgNode()->GetActivePoint(launches[1], "actpointweapon02");
        break;

    case OG_WEAPONPOS_CENTERLEFTRIGHT:
        NumLaunch = 3;
        m_pOwner->GetSgNode()->GetActivePoint(launches[0], "actpointweapon03");
        m_pOwner->GetSgNode()->GetActivePoint(launches[1], "actpointweapon01");
        m_pOwner->GetSgNode()->GetActivePoint(launches[2], "actpointweapon02");
        break;
    }

    int CurLaunch = NumLaunch;
    TMissileList::iterator iter = m_MissileList.begin();
    for (; iter != m_MissileList.end(); ++iter)
    {
        COGActorBullet* pMissile = *iter;
        if (!pMissile->IsActive())
        {
            pMissile->SetOwner(m_pOwner, launches[NumLaunch - CurLaunch]);
            pMissile->Fire();
            --CurLaunch;
            if (CurLaunch == 0)
            {
                m_WeaponCoolDown = 0;
                return;
            }
        }
    }
    if (CurLaunch != NumLaunch)
    {
        m_WeaponCoolDown = 0;
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
