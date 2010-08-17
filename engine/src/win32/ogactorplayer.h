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

#include "OGActor.h"


class COGActorPlayer : public COGActor
{
public:
	COGActorPlayer(OGActorType _Type);
	virtual ~COGActorPlayer();

	// Create actor.
	virtual bool Create (
		const std::string& _ModelAlias,
		const Vec3& _vPos,
		const Vec3& _vRot,
        const Vec3& _vScale);
};


#endif
