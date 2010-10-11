/*
 *  ogactorplayer.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogactorplayer.h"
#include "IOGMath.h"


COGActorPlayer::COGActorPlayer()
{
}


COGActorPlayer::~COGActorPlayer()
{
	GetInput()->UnregisterReceiver(this);
}


// Create actor.
bool COGActorPlayer::Create (IOGActorParams* _pParams,
                             const Vec3& _vPos,
                             const Vec3& _vRot,
                             const Vec3& _vScale)
{
    if (!COGActorBot::Create(_pParams, _vPos, _vRot, _vScale))
        return false;

    m_Weapon.Create(this);
    m_OrientWorker.Create(this);
    m_OrientWorker.Activate(false);
    m_CoolDown = 2000;
    m_WeaponCoolDownMax = 200;
    m_WeaponCoolDown = m_WeaponCoolDownMax;
    m_StraightenWorker.Create(this);
    m_StraightenWorker.Activate(false);

    return true;
}


// Adding to actor manager event handler.
void COGActorPlayer::OnAddedToManager ()
{
	COGActorBot::OnAddedToManager();
	GetInput()->RegisterReceiver(this);
}


// Control vector change event handler.
void COGActorPlayer::OnVectorChanged (const Vec3& _vVec)
{
	Vec3 v = _vVec;
	if (v.length() > 1.0f)
	{
		v.normalize();
	}
    m_pPhysicalObject->Strafe(v.x);
}


// Touch event handler.
void COGActorPlayer::OnTouch (const Vec2& _vPos)
{
    Vec3 vP = GetRenderer()->UnprojectCoords((int)_vPos.x, (int)_vPos.y);
    Vec3 vCam = GetRenderer()->GetCamera()->GetPosition();

    Vec3 vDir = (vP - vCam).normalized();
    Vec3 vPoint = FindIntersectionWithPlane(
        m_pPhysicalObject->GetPosition().y, 
        vCam, 
        vDir);

    m_OrientWorker.Reset();
    m_OrientWorker.SetTarget(vPoint);
    m_OrientWorker.Activate(true);

    m_CoolDown = 0;
    m_StraightenWorker.Activate(false);
}


// Update actor.
void COGActorPlayer::Update (unsigned long _ElapsedTime)
{
    COGActorBot::Update(_ElapsedTime);
    
    if (m_WeaponCoolDown < m_WeaponCoolDownMax)
    {
        m_WeaponCoolDown += _ElapsedTime;
        if (m_WeaponCoolDown >= m_WeaponCoolDownMax)
        {
            m_WeaponCoolDown = m_WeaponCoolDownMax;
            m_StraightenWorker.Activate(true);
        }        
    }
    
	if (m_OrientWorker.IsActive())
	{
		m_OrientWorker.Update(_ElapsedTime);
		if (m_OrientWorker.IsFinished() && m_WeaponCoolDown == m_WeaponCoolDownMax)
		{
            m_Weapon.Fire(Vec3(0,0,0));
            m_WeaponCoolDown = 0;
            m_CoolDown = 0;
            m_StraightenWorker.Activate(false);
		}
	}
    else
    {
        if (m_CoolDown < 2000)
        {
            m_CoolDown += _ElapsedTime;
            if (m_CoolDown >= 2000)
            {
                m_CoolDown = 2000;
                m_StraightenWorker.Activate(true);
            }
        }
        else
        {
            if (m_StraightenWorker.IsActive())
            {
                m_StraightenWorker.Update(_ElapsedTime);
                if (m_StraightenWorker.IsFinished())
                {
                }
            }
        }
    }
}
