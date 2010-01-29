/*
 *  oglight.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGLIGHT_H_
#define OGLIGHT_H_

#include "IOGLight.h"
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#include "common.h"
#include "GraphicsDevice.h"
#include "Geometry.h"
#include "Mathematics.h"


class COGLight : public IOGLight
{
public:
	COGLight ();
	virtual ~COGLight ();

	// set light source position.
	virtual void SetPosition (const VECTOR3& _vPosition);
	
	// get light source position.
	virtual const VECTOR3& GetPosition () const { return m_vPosition; }
	
	// set light direction.
	virtual void SetDirection (const VECTOR3& _vDirection);
	
	// get light direction.
	virtual const VECTOR3& GetDirection () const { return m_vDirection; }
	
private:
	VECTOR3		m_vPosition;
	VECTOR3		m_vDirection;
};

#endif
