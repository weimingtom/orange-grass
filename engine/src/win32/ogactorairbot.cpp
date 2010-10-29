/*
 *  ogactorairbot.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogactorairbot.h"


COGActorAirBot::COGActorAirBot()
{
}


COGActorAirBot::~COGActorAirBot()
{
}


// Create actor.
bool COGActorAirBot::Create (IOGActorParams* _pParams,
                             const Vec3& _vPos,
                             const Vec3& _vRot,
                             const Vec3& _vScale)
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
			Activate(false);
			m_Status = OG_ACTORSTATUS_DEAD;
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
        IOGActor* m_pBonus = GetActorManager()->CreateActor(
            "bonus_01", m_pPhysicalObject->GetPosition(), 
            Vec3(0,0,0), Vec3(1,1,1));
        GetActorManager()->AddActor(m_pBonus);
        m_pBonus->Activate(true);
		m_Status = OG_ACTORSTATUS_FALLING;
		m_FallingWorker.Activate(true);
		return true;
	}
	return false;
}
