/*
 *  OGPlasmaEffect.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGEFFECTPLASMA_H_
#define OGEFFECTPLASMA_H_

#include "ogeffect.h"
#include "ogemitterparticlechain.h"


class COGEffectPlasma : public COGEffect
{
public:
	virtual ~COGEffectPlasma();

	// Initialize effect.
	virtual void Init(OGEffectType _Type);

	// Update.
	virtual void Update (unsigned long _ElapsedTime);

	// Render.
	virtual void Render (const MATRIX& _mWorld);

	// Is dynamic.
	virtual bool IsDynamic () const {return true;}

	// Start.
	virtual void Start ();

	// Stop.
	virtual void Stop ();

	// Set direction.
	virtual void SetDirection (const Vec3& _vDir);

protected:
	
	COGEmitterParticleChain		m_ChainEmitter;

	static Vec4					m_color;
    static std::string			m_Texture;
    static unsigned int			m_MappingId;
};


#endif