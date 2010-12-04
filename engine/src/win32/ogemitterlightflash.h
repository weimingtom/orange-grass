/*
 *  OGEmitterLightFlash.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGEMITTERLIGHTFLASH_H_
#define OGEMITTERLIGHTFLASH_H_

#include "ogemitter.h"
#include <vector>


class COGEmitterLightFlash : public COGEmitter
{
public:
	COGEmitterLightFlash();
	virtual ~COGEmitterLightFlash();

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

protected:

    IOGLight*		m_pLight;

public:

    float			m_fFadeFactor;
	float			m_fInitialIntensity;
	Vec4			m_color;
};


#endif