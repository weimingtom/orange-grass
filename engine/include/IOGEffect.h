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
	OG_EFFECT_PLASMA,
	OG_EFFECT_MISSILESMOKE,
    OG_EFFECT_EXPLOSION
};


class IOGEffect : public IOGRenderable
{
public:
	virtual ~IOGEffect() {}

	// Initialize effect.
	virtual void Init(OGEffectType _Type) = 0;

	// Set billboard basis vectors.
	virtual void SetBillboardVectors (const Vec3& _vLook, const Vec3& _vUp, const Vec3& _vRight) = 0;

	// Set direction.
	virtual void SetDirection (const Vec3& _vDir) = 0;

	// Get direction.
	virtual const Vec3& GetDirection () const = 0;

	// Update.
	virtual void Update (unsigned long _ElapsedTime) = 0;

	// Update position.
	virtual void UpdatePosition (const Vec3& _vPosition) = 0;

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
