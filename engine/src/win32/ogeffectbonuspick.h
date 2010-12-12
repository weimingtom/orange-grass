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
#include "ogemitterpulseglow.h"
#include "ogemitterrotatingsparks.h"


class COGEffectBonusPick : public COGEffect
{
public:
	virtual ~COGEffectBonusPick();

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

    typedef std::vector<COGEmitter*>    TEmittersList;
    TEmittersList                       m_Emitters;
    COGEmitter*                         m_pMasterEmitter;
	//COGEmitterPulseGlow			m_GlowEmitter;
	//COGEmitterRotatingSparks	m_SparksEmitter;
};


#endif