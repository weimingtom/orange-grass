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

	// Get effect type.
    virtual OGEmitterType GetType() const { return s_Type; }

	// Get effect type.
    virtual const std::string& GetAlias() const { return s_Alias; }

protected:

	struct ParticleFormat
	{
		float	scale;
		BBVert	pVertices[4];
	};

protected:

    ParticleFormat	m_Wave;

    std::string     m_Texture;
    unsigned int    m_MappingId;
	float			m_fInitialScale;
	float			m_fAlphaDec;
	float			m_fScaleInc;
	Vec4			m_color;

public:

    static std::string     s_Alias;
    static OGEmitterType   s_Type;
};


#endif