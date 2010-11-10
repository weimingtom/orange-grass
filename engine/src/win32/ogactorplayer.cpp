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

    SetTeam(TEAM_PLAYER);

    m_OrientWorker.Create(this);
    m_OrientWorker.Activate(false);
    m_CoolDownMax = 500;
    m_CoolDown = m_CoolDownMax;
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
bool COGActorPlayer::OnVectorChanged (const Vec3& _vVec)
{
	Vec3 v = _vVec;
	if (v.length() > 1.0f)
	{
		v.normalize();
	}
    m_pPhysicalObject->Strafe(v.x);
    return true;
}


// Touch event handler.
bool COGActorPlayer::OnTouch (const Vec2& _vPos, IOGTouchParam _param)
{
    if (_param != OG_TOUCH_DOWN)
        return false;

    Vec3 vP = GetRenderer()->UnprojectCoords((int)_vPos.x, (int)_vPos.y);
    Vec3 vCam = GetRenderer()->GetCamera()->GetPosition();

    Vec3 vDir = (vP - vCam).normalized();
    Vec3 vPoint = FindIntersectionWithPlane(
        m_pPhysicalObject->GetPosition().y, 
        vCam, 
        vDir);
    m_vTarget = vPoint;

    m_OrientWorker.Reset();
    m_OrientWorker.SetTarget(vPoint);
    m_OrientWorker.Activate(true);

    m_CoolDown = 0;
    m_StraightenWorker.Activate(false);
    return true;
}


// Update alive actor.
void COGActorPlayer::UpdateAlive (unsigned long _ElapsedTime)
{
    COGActorBot::UpdateAlive(_ElapsedTime);
	m_pPhysicalObject->Move(Vec3(0, 0, -1.0f));

    UpdateSpecParams(_ElapsedTime);

    if (m_pWeapon)
        m_pWeapon->Update(_ElapsedTime);
    
	if (m_OrientWorker.IsActive())
	{
		m_OrientWorker.Update(_ElapsedTime);
		if (m_OrientWorker.IsFinished())
		{
            if (m_pWeapon && m_pWeapon->IsReady())
            {
                m_pWeapon->Fire(m_vTarget);
				//m_pWeapon->Fire(NULL, false);
            }
            m_CoolDown = 0;
            m_StraightenWorker.Activate(false);
		}
	}
    else
    {
        if (m_CoolDown < m_CoolDownMax)
        {
            m_CoolDown += _ElapsedTime;
            if (m_CoolDown >= m_CoolDownMax)
            {
                m_CoolDown = m_CoolDownMax;
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


// collision event handler
bool COGActorPlayer::OnCollision (const IOGCollision& _Collision)
{
    if (m_Status != OG_ACTORSTATUS_ALIVE)
        return false;

	return COGActorBot::OnCollision(_Collision);
}


// Respond on collision with missile.
bool COGActorPlayer::RespondOnBonusCollision (IOGActor* _pBonus)
{
    IOGBonusParams* pBonusParams = _pBonus->GetBonusParams();
    if (pBonusParams)
    {
        if (pBonusParams->cooldown > 0)
        {
            m_SpecParamsList.push_back(*pBonusParams);
        }

        switch (pBonusParams->type)
        {
        case OG_BONUS_LIFEPACK:
            m_Hitpoints += pBonusParams->value;
            OG_CLAMP(m_Hitpoints, 0, m_pParams->gameplay.max_hitpoints);
            break;

        case OG_BONUS_SHIELD:
            break;
        }
        return true;
    }

    return false;
}


// Get special params
void COGActorPlayer::GetSpecialParams (std::vector<IOGBonusParams>& _ParamsList)
{
    _ParamsList = m_SpecParamsList;
}


// Update special params.
void COGActorPlayer::UpdateSpecParams (unsigned long _ElapsedTime)
{
    std::vector<IOGBonusParams>::iterator iter = m_SpecParamsList.begin();
    while (iter != m_SpecParamsList.end())
    {
        if ((*iter).value > _ElapsedTime)
        {
            (*iter).value -= _ElapsedTime;
            ++iter;
        }
        else
        {
            iter = m_SpecParamsList.erase(iter);
        }
    }
}
