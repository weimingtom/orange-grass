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

#include "ogeffect.h"
#include "ogemitteranimatedbb.h"
#include "ogemitterringwave.h"
#include "ogemitterlightflash.h"
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
	virtual void Render (const MATRIX& _mWorld);

	// Start.
	virtual void Start ();

	// Stop.
	virtual void Stop ();

protected:

	COGEmitterAnimatedBB		m_AnimatedBBEmitter;
	COGEmitterRingWave			m_RingWaveEmitter;
	COGEmitterLightFlash		m_LightFlashEmitter;

    static std::string          m_Texture;
    static unsigned int         m_MappingStartId;
    static unsigned int         m_MappingFinishId;
	static float				m_fFrameInc;
	static float				m_fInitialScale;
	static float				m_fScaleInc;
    static float				m_fRotateInc;

	static float				m_fWaveInitialScale;
	static float				m_fWaveAlphaDec;
	static float				m_fWaveScaleInc;
    static unsigned int         m_WaveMappingId;

	static float				m_fLightFadeFactor;
	static float				m_fLightInitialIntensity;
};


#endif