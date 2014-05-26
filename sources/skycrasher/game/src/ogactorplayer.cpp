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
#include "ogactorplayer.h"
#include "IOGMath.h"


COGActorPlayer::COGActorPlayer() : m_bFinishLineFlight(false)
{
}


COGActorPlayer::~COGActorPlayer()
{
	GetInput()->UnregisterReceiver(this);
}


// Create actor.
bool COGActorPlayer::Create (IOGActorParams* _pParams,
                             const OGVec3& _vPos,
                             const OGVec3& _vRot,
                             const OGVec3& _vScale)
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
    m_FinishWorker.Create(this);
    m_FinishWorker.Activate(false);
    m_bFinishLineFlight = false;

    return true;
}


// Adding to actor manager event handler.
void COGActorPlayer::OnAddedToManager ()
{
	COGActorBot::OnAddedToManager();
	GetInput()->RegisterReceiver(this);
    IOGLevel* pCurLevel = GetLevelManager()->GetCurrentLevel();
    if (pCurLevel)
    {
        m_vFinishPoint = pCurLevel->GetFinishPosition();
    }
    m_FinishWorker.SetTarget(m_vFinishPoint);
}


// Control vector change event handler.
bool COGActorPlayer::OnVectorChanged (const OGVec3& _vVec)
{
    if (m_bFinishLineFlight)
        return false;

#ifdef WIN32
	OGVec3 v = _vVec;
	if (v.length() > 1.0f)
	{
		v.normalize();
	}
    m_pPhysicalObject->Strafe(v.x);
#else
    m_pPhysicalObject->Strafe(_vVec.x);
#endif
    return true;
}


// Touch event handler.
bool COGActorPlayer::OnTouch (const OGVec2& _vPos, IOGTouchParam _param)
{
    if (_param != OG_TOUCH_DOWN)
        return false;

    if (m_bFinishLineFlight)
        return false;

    OGVec3 vP = GetRenderer()->UnprojectCoords((int)_vPos.x, (int)_vPos.y);
    OGVec3 vCam = GetRenderer()->GetCamera()->GetPosition();

    OGVec3 vDir = (vP - vCam).normalized();
    OGVec3 vPoint = FindIntersectionWithPlane(
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


// Update actor.
void COGActorPlayer::Update (unsigned long _ElapsedTime)
{
    if (!m_bFinishLineFlight)
    {
        COGActorBot::Update(_ElapsedTime);

        if (CheckFinishCondition())
        {
            if (m_pGameEventsHandler)
                m_pGameEventsHandler->OnReachedFinishPoint();
            m_bFinishLineFlight = true;
            m_FinishWorker.Activate(true);
        }
    }
    else
    {
        m_pNode->Update(_ElapsedTime);
        if (m_FinishWorker.IsActive())
            m_FinishWorker.Update(_ElapsedTime);

        if (m_FinishWorker.IsFinished())
        {
            m_FinishWorker.Activate(false);
            if (m_pGameEventsHandler)
                m_pGameEventsHandler->OnLevelFinish();
        }
    }
}


// Update alive actor.
void COGActorPlayer::UpdateAlive (unsigned long _ElapsedTime)
{
    COGActorBot::UpdateAlive(_ElapsedTime);
	m_pPhysicalObject->Move(OGVec3(0, 0, -1.0f));

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
                
        case OG_BONUS_NONE:
            return false;
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


// Check if finish condition is satisfied.
bool COGActorPlayer::CheckFinishCondition ()
{
	const OGVec3& vCurPoint = m_pPhysicalObject->GetPosition();
	if (Dist2DSq(vCurPoint, m_vFinishPoint) <= 30000.0f)
	{
		return true;
	}
	return false;
}
