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


class COGEffectMissileSmoke : public COGEffect
{
public:
	virtual ~COGEffectMissileSmoke();

	// Initialize effect.
	virtual void Init(OGEffectType _Type);

	// Update.
	virtual void Update (unsigned long _ElapsedTime);

	// Update position.
	virtual void UpdatePosition (const Vec3& _vPosition);

	// Render.
	virtual void Render (const MATRIX& _mWorld, unsigned int _Frame);

	// Start.
	virtual void Start ();

	// Stop.
	virtual void Stop ();

protected:

	struct COGSmokeBillboard
	{
		bool    bDirty;
		float	scale;
		float   angle;
		Vec3	offset;
		BBVert	pVertices[4];
	};

protected:

    std::vector<COGSmokeBillboard>  m_BBList;
	Vec3							m_vPrevPosition;
	Vec3							m_vCurPosition;
	bool							m_bPositionUpdated;
	IOGMapping*						m_pMapping;
};


#endif