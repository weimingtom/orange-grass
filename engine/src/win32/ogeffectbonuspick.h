/*
 *  OGEffectBonusPick.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGEFFECTBONUSPICK_H_
#define OGEFFECTBONUSPICK_H_

#include "ogeffect.h"
#include <vector>

#define MAXPART     10


class COGEffectBonusPick : public COGEffect
{
public:
	virtual ~COGEffectBonusPick();

	// Initialize effect.
	virtual void Init(OGEffectType _Type);

	// Update.
	virtual void Update (unsigned long _ElapsedTime);

	// Render.
	virtual void Render (const MATRIX& _mWorld, unsigned int _Frame);

	// Start.
	virtual void Start ();

	// Stop.
	virtual void Stop ();

    // Load params.
    static bool LoadParams ();

protected:

    struct ParticleFormat
    {
        bool    bDirty;
	    float	scale;
        float   angle;
        float   tilt;
        int     axis;
	    Vec3	offset;
	    BBVert	pVertices[4];
    };
	
protected:

    IOGMapping*             m_pWaveMapping;
    IOGMapping*             m_pGlowMapping;

    ParticleFormat          m_BB[MAXPART];
    ParticleFormat          m_Glow;
    int                     m_GlowPulse;

    static float            m_fAlphaInc;
	static float            m_fScaleInc;
	static float            m_fInitialScale;
    static std::string      m_Texture;
    static unsigned int     m_MappingId;
};


#endif