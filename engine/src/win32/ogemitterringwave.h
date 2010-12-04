/*
 *  OGEmitterRingWave.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGEMITTERRINGWAVE_H_
#define OGEMITTERRINGWAVE_H_

#include "ogemitter.h"
#include <vector>


class COGEmitterRingWave : public COGEmitter
{
public:
	COGEmitterRingWave();
	virtual ~COGEmitterRingWave();

	// Initialize emitter.
	virtual void Init(IOGGroupNode* _pNode);

	// Update.
	virtual void Update (unsigned long _ElapsedTime);

	// Render.
	virtual void Render (const MATRIX& _mWorld, const Vec3& _vLook, const Vec3& _vUp, const Vec3& _vRight);

	// Start.
	virtual void Start ();

	// Stop.
	virtual void Stop ();

protected:

	struct ParticleFormat
	{
		bool    bDirty;
		float	scale;
		Vec3	offset;
		BBVert	pVertices[4];
	};

protected:

    ParticleFormat	m_Wave;

public:

    std::string     m_Texture;
    unsigned int    m_MappingId;
	float			m_fWaveInitialScale;
	float			m_fWaveAlphaDec;
	float			m_fWaveScaleInc;
	Vec4			m_color;
};


#endif