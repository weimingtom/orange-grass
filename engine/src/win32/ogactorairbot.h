/*
 *  OGActorAirbot.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGACTORAIRBOT_H_
#define OGACTORAIRBOT_H_

#include "OGActor.h"


class COGActorAirBot : public COGActor
{
public:
	COGActorAirBot();
	virtual ~COGActorAirBot();

	// Create actor.
	virtual bool Create (
		IOGActorParams* _pParams,
		const Vec3& _vPos,
		const Vec3& _vRot,
        const Vec3& _vScale);
};


#endif
