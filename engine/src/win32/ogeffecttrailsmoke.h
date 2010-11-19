/*
 *  OGEffectTrailSmoke.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGEFFECTTRAILSMOKE_H_
#define OGEFFECTTRAILSMOKE_H_

#include "OGEffect.h"
#include <vector>


class COGEffectTrailSmoke : public COGEffect
{
public:
	virtual ~COGEffectTrailSmoke();

	// Initialize effect.
	virtual void Init(OGEffectType _Type);

	// Update.
	virtual void Update (unsigned long _ElapsedTime);

	// Update position.
	virtual void UpdatePosition (const Vec3& _vPosition);

	// Render.
	virtual void Render (const MATRIX& _mWorld);

	// Start.
	virtual void Start ();

	// Stop.
	virtual void Stop ();

	// Is dynamic.
	virtual bool IsDynamic () const {return true;}

    // Load params.
    static bool LoadParams ();

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
	Vec3						m_vPrevPosition;
	Vec3						m_vCurPosition;
	bool						m_bPositionUpdated;
	IOGMapping*					m_pMapping;

	static float			m_fAlphaFade;
	static float			m_fInitialScale;
	static float			m_fScaleInc;
	static unsigned int		m_numVertsAtOnce;
    static float			m_fRotateInc;
	static Vec4				m_color;
    static std::string      m_Texture;
    static unsigned int     m_MappingId;
};


#endif