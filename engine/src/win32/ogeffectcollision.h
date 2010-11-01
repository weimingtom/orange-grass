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

#include "OGEffect.h"
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
	virtual void Render (const MATRIX& _mWorld, unsigned int _Frame);

	// Start.
	virtual void Start ();

	// Stop.
	virtual void Stop ();

protected:

    struct ParticleFormat
    {
        bool    bDirty;
        float   frame;
	    float	scale;
        float   angle;
	    BBVert	pVertices[4];
    };
	
protected:

    std::vector<IOGMapping*>    m_Frames;
    ParticleFormat              m_BB;

    unsigned int                m_MappingStartId;
    unsigned int                m_MappingFinishId;
	float                       m_fFrameInc;
	float                       m_fInitialScale;
	float                       m_fScaleInc;
    float                       m_fRotateInc;
};


#endif