/*
 *  OGPlasmaEffect.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGPLASMAEFFECT_H_
#define OGPLASMAEFFECT_H_

#include "OGEffect.h"


class COGPlasmaEffect : public COGEffect
{
public:
	virtual ~COGPlasmaEffect();

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
	
	COGBillboard::BBVert	m_Vertices[16];
	COGBillboard			m_Particles[4];
};


#endif