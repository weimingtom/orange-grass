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

#include "IOGEmitter.h"


enum OGEffectType
{
	OG_EFFECT_NO = 0,
	OG_EFFECT_PLASMA,
	OG_EFFECT_MISSILESMOKE,
    OG_EFFECT_EXPLOSION,
    OG_EFFECT_BONUSPICK,
    OG_EFFECT_COLLISION,
	OG_EFFECT_TRAILSMOKE,
	OG_EFFECT_GAUSS
};


struct BBVert
{
	Vec3 p;
	Vec2 t;
	Vec4 c;
};


class IOGEffect
{
public:
	virtual ~IOGEffect() {}

	// Initialize effect.
	virtual void Init(OGEffectType _Type, const std::string& _File) = 0;

	// Set billboard basis vectors.
	virtual void SetBillboardVectors (const Vec3& _vLook, const Vec3& _vUp, const Vec3& _vRight) = 0;

	// Set direction.
	virtual void SetDirection (const Vec3& _vDir) = 0;

	// Set start and finish positions.
	virtual void SetStartFinishPositions (const Vec3& _vStartPos, const Vec3& _vFinishPos) = 0;

	// Update.
	virtual void Update (unsigned long _ElapsedTime) = 0;

	// Update position.
	virtual void UpdatePosition (const Vec3& _vPosition) = 0;

	// Render.
	virtual void Render (const MATRIX& _mWorld) = 0;

	// Start.
	virtual void Start () = 0;

	// Stop.
	virtual void Stop () = 0;

	// Is dynamic.
	virtual bool IsDynamic () const = 0;

	// Get effect run status.
	virtual OGEffectStatus GetStatus() const = 0;

	// Get effect type.
	virtual OGEffectType GetType() const = 0;

	// Get combined AABB
	virtual const IOGAabb& GetAABB () const = 0;
};

#endif
