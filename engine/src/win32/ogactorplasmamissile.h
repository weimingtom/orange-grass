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
	COGActorPlasmaMissile(OGActorType _Type);
	virtual ~COGActorPlasmaMissile();

	// Create actor.
	virtual bool Create (
		const std::string& _ModelAlias,
		const Vec3& _vPos,
		const Vec3& _vRot,
        const Vec3& _vScale);

	// Adding to actor manager event handler.
	virtual void OnAddedToManager ();

	// Update actor.
	virtual void Update (unsigned long _ElapsedTime);

	// Get model alias
	virtual const std::string& GetAlias () const;

protected:

    IOGEffect*  m_pHeadEffect;
    std::string m_EffectAlias;
};


#endif
