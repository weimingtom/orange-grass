/*
 *  IOGEffect.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGEFFECT_H_
#define IOGEFFECT_H_

#include "IOGMath.h"
#include "IOGRenderable.h"


enum OGEffectStatus
{
	OG_EFFECTSTATUS_INACTIVE,
	OG_EFFECTSTATUS_STARTED,
	OG_EFFECTSTATUS_STOPPED
};

enum OGEffectType
{
	OG_EFFECT_NO = 0,
	OG_EFFECT_PLASMA
};


class IOGEffect : public IOGRenderable
{
public:
	virtual ~IOGEffect() {}

	// Initialize effect.
	virtual void Init(OGEffectType _Type) = 0;

	// Set position.
	virtual void SetPosition (const Vec3& _vPos) = 0;

	// Set direction.
	virtual void SetDirection (const Vec3& _vDir) = 0;

	// Get position.
	virtual const Vec3& GetPosition () const = 0;

	// Get direction.
	virtual const Vec3& GetDirection () const = 0;

	// Update.
	virtual void Update (unsigned long _ElapsedTime) = 0;

	// Start.
	virtual void Start () = 0;

	// Stop.
	virtual void Stop () = 0;

	// Get effect run status.
	virtual OGEffectStatus GetStatus() const = 0;

	// Get effect type.
	virtual OGEffectType GetType() const = 0;
};

#endif
