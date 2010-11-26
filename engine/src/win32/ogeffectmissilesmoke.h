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

#include "ogeffect.h"
#include "ogemittertrail.h"
#include "ogemitterglow.h"
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

	COGEmitterTrail			m_TrailEmitter;
	COGEmitterGlow			m_GlowEmitter;

	static float			m_fAlphaFade;
	static float			m_fInitialScale;
	static float			m_fScaleInc;
	static unsigned int		m_numVertsAtOnce;
	static float			m_fRotateInc;
	static Vec4				m_color;
	static std::string      m_Texture;
	static unsigned int     m_MappingId;

    static unsigned int     m_GlowMappingId;
};


#endif