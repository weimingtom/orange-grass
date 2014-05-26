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
#include "ogactorairbot.h"


COGActorAirBot::COGActorAirBot()
{
}


COGActorAirBot::~COGActorAirBot()
{
}


// Create actor.
bool COGActorAirBot::Create (IOGActorParams* _pParams,
                             const OGVec3& _vPos,
                             const OGVec3& _vRot,
                             const OGVec3& _vScale)
{
    if (!COGActorBot::Create(_pParams, _vPos, _vRot, _vScale))
        return false;

	m_FlightWorker.Create(this);
	m_FallingWorker.Create(this);
    Activate(false);

    return true;
}


// Adding to actor manager event handler.
void COGActorAirBot::OnAddedToManager ()
{
    COGActorBot::OnAddedToManager();
}


// Set active state
void COGActorAirBot::Activate (bool _bActive)
{
	if (_bActive == m_bActive || m_Status == OG_ACTORSTATUS_DEAD)
		return;

	COGActorBot::Activate(_bActive);

	if (m_bActive)
	{
		m_FlightWorker.Reset();
		m_FlightWorker.Activate(true);
	}
	else
	{
		m_FlightWorker.Activate(false);
	}
}


// Update alive actor.
void COGActorAirBot::UpdateAlive (unsigned long _ElapsedTime)
{
	COGActorBot::UpdateAlive(_ElapsedTime);

	if (m_FlightWorker.IsActive())
	{
        if (m_pWeapon)
        {
            m_pWeapon->Update(_ElapsedTime);
            if (m_pWeapon->IsReady())
            {
                IOGActor* pPlayer = GetActorManager()->GetPlayersActor();
                if (pPlayer)
                {
                    if (m_pPhysicalObject->GetPosition().z < (pPlayer->GetPhysicalObject()->GetPosition().z - 50.0f))
                    {
                        m_pWeapon->Fire(pPlayer, true);
                    }
                }
            }
        }

		m_FlightWorker.Update(_ElapsedTime);
		if (m_FlightWorker.IsFinished())
		{
			Activate(false);
		}
	}
}


// Update falling actor.
void COGActorAirBot::UpdateFalling (unsigned long _ElapsedTime)
{
	COGActorBot::UpdateFalling(_ElapsedTime);

	if (m_FallingWorker.IsActive())
	{
		m_FallingWorker.Update(_ElapsedTime);
		if (m_FallingWorker.IsFinished())
		{
            SetDeadStatus();
        }
	}
}


// collision event handler
bool COGActorAirBot::OnCollision (const IOGCollision& _Collision)
{
    if (m_Status != OG_ACTORSTATUS_ALIVE)
        return false;

	if (COGActorBot::OnCollision(_Collision))
	{
   		return true;
	}
	return false;
}


// Set actor status.
void COGActorAirBot::SetFallingStatus ()
{
    COGActorBot::SetFallingStatus();
    m_FallingWorker.Activate(true);

    ThrowBonus();
}


// Set actor status.
void COGActorAirBot::SetDeadStatus ()
{
	Activate(false);

    COGActorBot::SetDeadStatus();
}


// Throw bonus.
void COGActorAirBot::ThrowBonus ()
{
    int i = GetRandomRange(0, 3);
    IOGBonusParams* pBonusParams = NULL;
    switch(i)
    {
    case 0:
        break;

    case 1:
        pBonusParams = GetActorParamsMgr()->GetBonusParams("life_pack");
        break;

    case 2:
        pBonusParams = GetActorParamsMgr()->GetBonusParams("shield");
        break;
    }

    if (pBonusParams)
    {
        IOGActor* m_pBonus = GetActorManager()->CreateActor(
            pBonusParams->actor, m_pPhysicalObject->GetPosition(), 
            OGVec3(0,0,0), OGVec3(1,1,1));
        GetActorManager()->AddActor(m_pBonus);
        m_pBonus->SetBonusParams(pBonusParams);
        m_pBonus->Activate(true);
    }
}
