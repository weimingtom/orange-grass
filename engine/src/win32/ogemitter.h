/*
 *  OGEmitter.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGEMITTER_H_
#define OGEMITTER_H_

#include "IOGEffect.h"
#include "IOGTexture.h"
#include "IOGRenderer.h"
#include <vector>


class COGEmitter
{
public:
	COGEmitter();
	virtual ~COGEmitter();

	// Initialize emitter.
	virtual void Init() = 0;

	// Update.
	virtual void Update (unsigned long _ElapsedTime) = 0;

	// Update position.
	virtual void UpdatePosition (const Vec3& _vPosition);

	// Render.
	virtual void Render (const MATRIX& _mWorld, const Vec3& _vLook, const Vec3& _vUp, const Vec3& _vRight) = 0;

	// Start.
	virtual void Start () = 0;

	// Stop.
	virtual void Stop () = 0;

	// Get effect run status.
	virtual OGEffectStatus GetStatus() const;

protected:

	Vec3						m_vPrevPosition;
	Vec3						m_vCurPosition;
	bool						m_bPositionUpdated;
	IOGMapping*					m_pMapping;
	OGEffectStatus				m_Status;
	IOGTexture*					m_pTexture;
	OGBlendType					m_Blend;
	IOGRenderer*				m_pRenderer;
};


#endif