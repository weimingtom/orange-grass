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
#include "IOGRenderer.h"


class COGEffect : public IOGEffect
{
public:
	COGEffect();
	virtual ~COGEffect();

	// Initialize effect.
    virtual void Init(OGEffectType _Type, const std::string& _File);

	// Set billboard basis vectors.
	virtual void SetBillboardVectors (const OGVec3& _vLook, const OGVec3& _vUp, const OGVec3& _vRight);

	// Set direction.
	virtual void SetDirection (const OGVec3& _vDir);

	// Set start and finish positions.
    virtual void SetStartFinishPositions (const OGVec3& _vStartPos, const OGVec3& _vFinishPos);

	// Update.
	virtual void Update (unsigned long _ElapsedTime);

	// Update position.
	virtual void UpdatePosition (const OGVec3& _vPosition);

	// Render.
	virtual void Render (const OGMatrix& _mWorld);

	// Get combined AABB
    virtual const IOGAabb& GetAABB () const {return m_AABB;}

	// Start.
	virtual void Start ();

	// Stop.
	virtual void Stop ();

	// Is dynamic.
	virtual bool IsDynamic () const;

	// Get effect run status.
	virtual OGEffectStatus GetStatus() const { return m_Status; }

	// Get effect type.
	virtual OGEffectType GetType() const { return m_Type; }

	// Get type of the renderable.
	virtual RenderableType GetRenderableType () const { return OG_RENDERABLE_EFFECT; }

    // Get emitters list.
    virtual TEmittersList& GetEmitters () { return m_Emitters; }

protected:
	
    IOGAabb         m_AABB;
    OGVec3			m_vCameraLook;
    OGVec3			m_vCameraUp;
    OGVec3			m_vCameraRight;
    OGEffectStatus	m_Status;
    OGEffectType	m_Type;

    TEmittersList   m_Emitters;
    IOGEmitter*     m_pMasterEmitter;
};

#endif
