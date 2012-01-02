/*
 *  OGEmitterGlow.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGEMITTERGLOW_H_
#define OGEMITTERGLOW_H_

#include "ogemitter.h"
#include <vector>


class COGEmitterGlow : public COGEmitter
{
public:
	COGEmitterGlow();
	virtual ~COGEmitterGlow();

	// Initialize emitter.
	virtual void Init (IOGGroupNode* _pNode);

	// Update.
	virtual void Update (unsigned long _ElapsedTime);

	// Render.
	virtual void Render (const OGMatrix& _mWorld, const OGVec3& _vLook, const OGVec3& _vUp, const OGVec3& _vRight);

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
		float   angle;
		BBVert	pVertices[4];
	};

protected:

    ParticleFormat	m_Glow;

    std::string     m_Texture;
    unsigned int    m_MappingId;
	OGVec4			m_color;
	float			m_fInitialScale;
	float			m_fInitialAngleMin;
	float			m_fInitialAngleMax;

public:

    static std::string     s_Alias;
    static OGEmitterType   s_Type;
};


#endif