/*
 *  OGActorPlasmaMissile.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGACTORPLASMAMISSILE_H_
#define OGACTORPLASMAMISSILE_H_

#include "OGActor.h"


class COGActorPlasmaMissile : public COGActor
{
public:
	COGActorPlasmaMissile();
	virtual ~COGActorPlasmaMissile();

	// Create actor.
	virtual bool Create (
		IOGActorParams* _pParams,
		const Vec3& _vPos,
		const Vec3& _vRot,
        const Vec3& _vScale);

	// Adding to actor manager event handler.
	virtual void OnAddedToManager ();

	// Update actor.
	virtual void Update (unsigned long _ElapsedTime);

protected:

    IOGEffect*  m_pHeadEffect;
};


#endif
