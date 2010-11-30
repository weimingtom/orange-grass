/*
 *  OGEmitterPulseGlow.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGEMITTERPULSEGLOW_H_
#define OGEMITTERPULSEGLOW_H_

#include "ogemitter.h"
#include <vector>


class COGEmitterPulseGlow : public COGEmitter
{
public:
	COGEmitterPulseGlow();
	virtual ~COGEmitterPulseGlow();

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
	    BBVert	pVertices[4];
    };

protected:

    ParticleFormat	m_Glow;
    int             m_GlowPulse;

public:

    std::string     m_Texture;
    unsigned int    m_MappingId;
    float           m_fGlowAlphaInc;
	float			m_fAlphaInc;
	Vec4			m_color;
};


#endif