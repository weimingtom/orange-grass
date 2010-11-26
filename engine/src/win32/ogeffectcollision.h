/*
 *  OGEffectCollision.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGEFFECTCOLLISION_H_
#define OGEFFECTCOLLISION_H_

#include "ogeffect.h"
#include "ogemitteranimatedbb.h"
#include "ogemitterlightflash.h"
#include <vector>


class COGEffectCollision : public COGEffect
{
public:
	virtual ~COGEffectCollision();

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

    // Load params.
    static bool LoadParams ();

protected:

	COGEmitterAnimatedBB		m_AnimatedBBEmitter;
	COGEmitterLightFlash		m_LightFlashEmitter;

    static unsigned int         m_MappingStartId;
    static unsigned int         m_MappingFinishId;
	static float                m_fFrameInc;
	static float                m_fInitialScale;
	static float                m_fScaleInc;
    static float                m_fRotateInc;
    static std::string          m_Texture;

	static float				m_fLightFadeFactor;
	static float				m_fLightInitialIntensity;
};


#endif