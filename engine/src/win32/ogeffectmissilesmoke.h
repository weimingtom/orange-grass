/*
 *  OGEffectMissileSmoke.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGEFFECTMISSILESMOKE_H_
#define OGEFFECTMISSILESMOKE_H_

#include "OGEffect.h"
#include <vector>
#define MAX_SMOKE_PARTILES 30
#define SMOKE_VERTICES     MAX_SMOKE_PARTILES*4

struct COSmokeGBillboard
{
	struct BBVert
	{
		Vec3 p;
		Vec2 t;
		Vec4 c;
	};

    bool    bDirty;
	float	scale;
	Vec3	offset;
	BBVert	pVertices[4];
};


class COGEffectMissileSmoke : public COGEffect
{
public:
	virtual ~COGEffectMissileSmoke();

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
	
	COSmokeGBillboard::BBVert	    m_Vertices[SMOKE_VERTICES];
    std::vector<COSmokeGBillboard>  m_BBList;
};


#endif