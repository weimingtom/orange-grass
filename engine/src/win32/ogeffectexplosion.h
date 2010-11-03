/*
 *  OGEffectExplosion.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGEFFECTEXPLOSION_H_
#define OGEFFECTEXPLOSION_H_

#include "OGEffect.h"
#include <vector>


class COGEffectExplosion : public COGEffect
{
public:
	virtual ~COGEffectExplosion();

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

protected:

    struct ParticleFormat
    {
        float   frame;
	    float	scale;
        float   angle;
	    Vec3	offset;
	    BBVert	pVertices[4];
    };
	
protected:

    std::vector<IOGMapping*>    m_Frames;
    std::vector<ParticleFormat>	m_BBList;
    IOGMapping*                 m_pWaveMapping;
    ParticleFormat              m_Wave;

	Vec4						m_color;

    static std::string          m_Texture;
	static unsigned int			m_MaxParticles;
    static unsigned int         m_MappingStartId;
    static unsigned int         m_MappingFinishId;
	static float				m_fFrameInc;
	static float				m_fInitialScale;
	static float				m_fScaleInc;
	static unsigned int			m_numVertsAtOnce;
    static float				m_fRotateInc;
	static int					m_offset_min;
	static int					m_offset_max;

	static float				m_fWaveInitialScale;
	static float				m_fWaveAlphaDec;
	static float				m_fWaveScaleInc;
    static unsigned int         m_WaveMappingId;
};


#endif