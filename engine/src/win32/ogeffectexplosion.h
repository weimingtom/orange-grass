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

    struct COGExplosionBillboard
    {
        bool    bDirty;
        float   frame;
	    float	scale;
        float   angle;
	    Vec3	offset;
	    BBVert	pVertices[4];
    };
	
protected:

    std::vector<IOGMapping>             m_Frames;
    std::vector<COGExplosionBillboard>  m_BBList;
};


#endif