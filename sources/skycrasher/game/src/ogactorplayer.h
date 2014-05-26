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
#ifndef OGACTORPLAYER_H_
#define OGACTORPLAYER_H_

#include "ogactorbot.h"
#include "IOGInputReceiver.h"
#include "ogweapon.h"
#include "ogorientworker.h"
#include "ogstabilizeworker.h"
#include "ogfinishlevelworker.h"


class COGActorPlayer : public COGActorBot, public IOGInputReceiver
{
public:
	COGActorPlayer();
	virtual ~COGActorPlayer();

	// Create actor.
	virtual bool Create (
		IOGActorParams* _pParams,
		const OGVec3& _vPos,
		const OGVec3& _vRot,
        const OGVec3& _vScale);

	// Adding to actor manager event handler.
	virtual void OnAddedToManager ();

	// Control vector change event handler.
	virtual bool OnVectorChanged (const OGVec3& _vVec);

	// Touch event handler.
	virtual bool OnTouch (const OGVec2& _vPos, IOGTouchParam _param);

    // collision event handler
	virtual bool OnCollision (const IOGCollision& _Collision);

	// Get special params
    virtual void GetSpecialParams (std::vector<IOGBonusParams>& _ParamsList);

	// Update actor.
	virtual void Update (unsigned long _ElapsedTime);

protected:

	// Update alive actor.
	virtual void UpdateAlive (unsigned long _ElapsedTime);

	// Update special params.
	virtual void UpdateSpecParams (unsigned long _ElapsedTime);

	// Respond on collision with missile.
	virtual bool RespondOnBonusCollision (IOGActor* _pBonus);

    // Check if finish condition is satisfied.
    bool CheckFinishCondition ();

protected:

    COGOrientWorker     m_OrientWorker;
    COGStabilizeWorker  m_StraightenWorker;
    COGFinishLevelWorker  m_FinishWorker;
    unsigned long       m_CoolDown;
    unsigned long       m_CoolDownMax;
    OGVec3                m_vTarget;
    std::vector<IOGBonusParams> m_SpecParamsList;

    OGVec3 m_vFinishPoint;
    bool m_bFinishLineFlight;
};


#endif
