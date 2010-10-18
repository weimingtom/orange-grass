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
    COGActorBot::Update(_ElapsedTime);

    if (m_FlightWorker.IsActive())
	{
		m_FlightWorker.Update(_ElapsedTime);
		if (m_FlightWorker.IsFinished())
		{
			Activate(false);
		}
	}
}
