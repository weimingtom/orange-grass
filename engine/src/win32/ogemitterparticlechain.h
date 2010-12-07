/*
 *  OGEmitterParticleChain.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGEMITTERPARTICLECHAIN_H_
#define OGEMITTERPARTICLECHAIN_H_

#include "ogemitter.h"
#include <vector>


class COGEmitterParticleChain : public COGEmitter
{
public:
	COGEmitterParticleChain();
	virtual ~COGEmitterParticleChain();

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

	// Set direction.
    virtual void SetDirection (const Vec3& _vDir);

protected:

    struct ParticleFormat
    {
		float	scale;
		Vec3	offset;
	    BBVert	pVertices[4];
    };

protected:

	std::vector<ParticleFormat>  m_BBList;
	Vec3			m_Direction;

public:

    std::string     m_Texture;
    unsigned int    m_MappingId;
	unsigned int	m_NumParticles;
	Vec4			m_color;
};


#endif