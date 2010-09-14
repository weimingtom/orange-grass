/*
 *  OGEffect.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGEFFECT_H_
#define OGEFFECT_H_

#include "IOGEffect.h"
#include "IOGTexture.h"
#include "IOGMaterial.h"


struct COGBillboard
{
	struct BBVert
	{
		Vec3 p;
		Vec2 t;
		Vec4 c;
	};

	float	scale;
	Vec3	offset;
	BBVert*	pVertices;
};


class COGEffect : public IOGEffect
{
public:
	COGEffect();
	virtual ~COGEffect();

	// Initialize effect.
	virtual void Init(OGEffectType _Type) = 0;

	// Set position.
	virtual void SetPosition (const Vec3& _vPos);

	// Set direction.
	virtual void SetDirection (const Vec3& _vDir);

	// Get position.
	virtual const Vec3& GetPosition () const { return m_Position; }

	// Get direction.
	virtual const Vec3& GetDirection () const { return m_Direction; }

	// Update.
	virtual void Update (unsigned long _ElapsedTime) = 0;

	// Render.
	virtual void Render (
		const MATRIX& _mView, 
		const Vec3& _vRight, 
		const Vec3& _vUp) = 0;

	// Start.
	virtual void Start ();

	// Stop.
	virtual void Stop ();

	// Get effect run status.
	virtual OGEffectStatus GetStatus() const { return m_Status; }

	// Get effect type.
	virtual OGEffectType GetType() const { return m_Type; }

protected:
	
	Vec3			m_Position;
	Vec3			m_Direction;
	MATRIX			m_World;
	OGEffectStatus	m_Status;
	OGEffectType	m_Type;
	IOGTexture*		m_pTexture;
	IOGMaterial*	m_pMaterial;
};


#endif
