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

    struct COGCollisionBillboard
    {
        float   frame;
	    float	scale;
        float   angle;
	    Vec3	offset;
	    BBVert	pVertices[4];
    };
	
protected:

    std::vector<IOGMapping>             m_Frames;
    std::vector<COGCollisionBillboard>  m_BBList;
};


#endif