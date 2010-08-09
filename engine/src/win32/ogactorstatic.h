/*
 *  OGActorStatic.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGACTORSTATIC_H_
#define OGACTORSTATIC_H_

#include "OGActor.h"


class COGActorStatic : public COGActor
{
public:
	COGActorStatic(OGActorType _Type);
	virtual ~COGActorStatic();

	// Create actor.
	virtual bool Create (
		const std::string& _ModelAlias,
		const Vec3& _vPos,
		const Vec3& _vRot,
        const Vec3& _vScale);
};


#endif
