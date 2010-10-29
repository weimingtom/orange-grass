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

#include "OGEffect.h"
#include <vector>


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

protected:

    struct COGBonusPickBillboard
    {
	    float	scale;
        float   angle;
	    Vec3	offset;
	    BBVert	pVertices[4];
    };
	
protected:

    IOGMapping              m_WaveMapping;
    COGBonusPickBillboard	m_Wave;
};


#endif