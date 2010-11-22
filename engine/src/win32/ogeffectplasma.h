/*
 *  OGPlasmaEffect.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGEFFECTPLASMA_H_
#define OGEFFECTPLASMA_H_

#include "ogeffect.h"
#define MAX_PLASMA_PARTILES 12
#define PLASMA_VERTICES     MAX_PLASMA_PARTILES*4

class COGEffectPlasma : public COGEffect
{
public:
	virtual ~COGEffectPlasma();

	// Initialize effect.
	virtual void Init(OGEffectType _Type);

	// Update.
	virtual void Update (unsigned long _ElapsedTime);

	// Render.
	virtual void Render (const MATRIX& _mWorld);

	// Is dynamic.
	virtual bool IsDynamic () const {return true;}

	// Start.
	virtual void Start ();

	// Stop.
	virtual void Stop ();

protected:

	struct COGBillboard
	{
		float	scale;
		Vec3	offset;
		BBVert*	pVertices;
	};

protected:
	
	IOGMapping*		m_pMapping;
	BBVert			m_Vertices[PLASMA_VERTICES];
	COGBillboard	m_Particles[MAX_PLASMA_PARTILES];
};


#endif