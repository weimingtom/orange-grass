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
#include "IOGMath.h"


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
	if (m_Status == OG_ACTORSTATUS_DEAD)
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


// Update actor.
void COGActorAirBot::Update (unsigned long _ElapsedTime)
{
	if (m_Status != OG_ACTORSTATUS_DEAD)
		COGActorBot::Update(_ElapsedTime);

	switch (m_Status)
	{
	case OG_ACTORSTATUS_ALIVE:
		{
			if (m_FlightWorker.IsActive())
			{
				m_FlightWorker.Update(_ElapsedTime);
				if (m_FlightWorker.IsFinished())
				{
					Activate(false);
				}
			}
		}
		break;

	case OG_ACTORSTATUS_FALLING:
		{
			if (m_FallingWorker.IsActive())
			{
				m_FallingWorker.Update(_ElapsedTime);
				if (m_FallingWorker.IsFinished())
				{
					m_Status = OG_ACTORSTATUS_DEAD;
					Activate(false);
				}
			}
		}
		break;

	case OG_ACTORSTATUS_DEAD:
		{
		}
		break;
	}
}


// collision event handler
bool COGActorAirBot::OnCollision (const IOGCollision& _Collision)
{
	if (COGActorBot::OnCollision(_Collision))
	{
		m_Status = OG_ACTORSTATUS_FALLING;
		m_FallingWorker.Activate(true);
		return true;
	}
	return false;
}
