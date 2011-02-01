/*
 *  OGEmitterTrail.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGEMITTERTRAIL_H_
#define OGEMITTERTRAIL_H_

#include "ogemitter.h"
#include <vector>


class COGEmitterTrail : public COGEmitter
{
public:
	COGEmitterTrail();
	virtual ~COGEmitterTrail();

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

	// Is dynamic.
	virtual bool IsDynamic () const {return true;}

	// Get effect type.
    virtual OGEmitterType GetType() const { return s_Type; }

	// Get effect type.
    virtual const std::string& GetAlias() const { return s_Alias; }

protected:

	struct ParticleFormat
	{
		bool    bDirty;
		float	scale;
		float   angle;
		Vec3	offset;
		BBVert	pVertices[4];
	};

protected:

    std::vector<ParticleFormat>	m_BBList;

	float			m_fAlphaFade;
	float			m_fInitialScale;
	float			m_fScaleInc;
	float			m_fEmitDistance;
    float			m_fRotateInc;
	Vec4			m_color;
    std::string     m_Texture;
    unsigned int    m_MappingId;

	float			m_fDistanceAccum;

public:

    static std::string     s_Alias;
    static OGEmitterType   s_Type;
};


#endif