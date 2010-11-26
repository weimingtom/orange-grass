/*
 *  OGEmitterGlow.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGEMITTERGLOW_H_
#define OGEMITTERGLOW_H_

#include "ogemitter.h"
#include <vector>


class COGEmitterGlow : public COGEmitter
{
public:
	COGEmitterGlow();
	virtual ~COGEmitterGlow();

	// Initialize emitter.
	virtual void Init();

	// Update.
	virtual void Update (unsigned long _ElapsedTime);

	// Render.
	virtual void Render (const MATRIX& _mWorld, const Vec3& _vLook, const Vec3& _vUp, const Vec3& _vRight);

	// Start.
	virtual void Start ();

	// Stop.
	virtual void Stop ();

protected:

	struct ParticleFormat
	{
		bool    bDirty;
		float	scale;
		float   angle;
		Vec3	offset;
		BBVert	pVertices[4];
	};

protected:

    ParticleFormat	m_Glow;

public:

    std::string     m_Texture;
    unsigned int    m_MappingId;
};


#endif