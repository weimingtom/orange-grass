/*
 *  OGEffectGauss.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGEFFECTGAUSS_H_
#define OGEFFECTGAUSS_H_

#include "ogeffect.h"
#include "ogemitterscrollingray.h"


class COGEffectGauss : public COGEffect
{
public:
	virtual ~COGEffectGauss();

	// Initialize effect.
	virtual void Init(OGEffectType _Type);

	// Update.
	virtual void Update (unsigned long _ElapsedTime);

	// Render.
	virtual void Render (const MATRIX& _mWorld);

	// Start.
	virtual void Start ();

	// Stop.
	virtual void Stop ();

	// Set start and finish positions.
	virtual void SetStartFinishPositions (const Vec3& _vStartPos, const Vec3& _vFinishPos);

	// Set direction.
    virtual void SetDirection (const Vec3& _vDir) {}

protected:

	COGEmitterScrollingRay		m_RayEmitter;

    static std::string          m_Texture;
    static unsigned int         m_MappingStartId;
    static unsigned int         m_MappingFinishId;
    static float				m_fSegment;
    static float				m_fScale;
    static float				m_fSpeed;
	static Vec4					m_color;
};


#endif