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
#include "Game.h"
#include "ogweapon.h"


static const int MaxMissiles = 32;


COGWeapon::COGWeapon()
{
	m_pOwner = NULL;
	m_pWeaponParams = NULL;
    m_WeaponCoolDownMax = 200;
    m_WeaponCoolDown = m_WeaponCoolDownMax;

	m_MissileList.reserve(MaxMissiles);
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
	m_WeaponCoolDown = m_WeaponCoolDownMax;

    for (int i = 0; i < MaxMissiles; ++i)
    {
        COGActorBullet* pMissile = (COGActorBullet*)GetActorManager()->CreateActor(
			m_pWeaponParams->actor, OGVec3(0,0,0), OGVec3(0,0,0), OGVec3(1,1,1));
        pMissile->SetTeam(_pOwner->GetTeam());
        pMissile->SetDamagePoints(m_pWeaponParams->hitpoints);
        GetActorManager()->AddActor(pMissile);
        m_MissileList.push_back(pMissile);
    }
    return true;
}


// Fire missile.
void COGWeapon::Fire (IOGActor* _pTarget, bool _bFollow)
{
    OGVec3 launches[3];
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
    
    case OG_WEAPONPOS_NONE:
        return;
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
            if (_pTarget)
            {
                if (_bFollow)
                {
                    pMissile->SetTarget(_pTarget);
                }
                else
                {
                    pMissile->SetTarget(_pTarget->GetPhysicalObject()->GetPosition());
                }
            }
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


// Fire.
void COGWeapon::Fire (const OGVec3& _vTarget)
{
    OGVec3 launches[3];
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
            
    case OG_WEAPONPOS_NONE:
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
            pMissile->SetTarget(_vTarget);
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
