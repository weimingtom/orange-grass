/*
 *  OGActorPlayer.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGACTORPLAYER_H_
#define OGACTORPLAYER_H_

#include "ogactorbot.h"
#include "IOGInputReceiver.h"
#include "ogweapon.h"
#include "ogorientworker.h"
#include "ogstabilizeworker.h"


class COGActorPlayer : public COGActorBot, public IOGInputReceiver
{
public:
	COGActorPlayer();
	virtual ~COGActorPlayer();

	// Create actor.
	virtual bool Create (
		IOGActorParams* _pParams,
		const Vec3& _vPos,
		const Vec3& _vRot,
        const Vec3& _vScale);

	// Adding to actor manager event handler.
	virtual void OnAddedToManager ();

	// Control vector change event handler.
	virtual bool OnVectorChanged (const Vec3& _vVec);

	// Touch event handler.
	virtual bool OnTouch (const Vec2& _vPos, IOGTouchParam _param);

    // collision event handler
	virtual bool OnCollision (const IOGCollision& _Collision);

protected:

	// Update alive actor.
	virtual void UpdateAlive (unsigned long _ElapsedTime);

protected:

    COGOrientWorker     m_OrientWorker;
    COGStabilizeWorker  m_StraightenWorker;
    unsigned long       m_CoolDown;
    unsigned long       m_CoolDownMax;
};


#endif
