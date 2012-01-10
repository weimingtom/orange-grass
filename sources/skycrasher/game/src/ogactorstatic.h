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

#include "ogactor.h"


class COGActorStatic : public COGActor
{
public:
	COGActorStatic();
	virtual ~COGActorStatic();

	// Create actor.
	virtual bool Create (
		IOGActorParams* _pParams,
		const OGVec3& _vPos,
		const OGVec3& _vRot,
        const OGVec3& _vScale);

	// Adding to actor manager event handler.
	virtual void OnAddedToManager ();
};


#endif
