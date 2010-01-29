/*
 *  IOGLight.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGLIGHT_H_
#define IOGLIGHT_H_

#include "Mathematics.h"


class IOGLight
{
public:
	virtual ~IOGLight () {}
		
	// set light source position.
	virtual void SetPosition (const VECTOR3& _vPosition) = 0;
		
	// get light source position.
	virtual const VECTOR3& GetPosition () const = 0;
		
	// set light direction.
	virtual void SetDirection (const VECTOR3& _vDirection) = 0;
		
	// get light direction.
	virtual const VECTOR3& GetDirection () const = 0;
};

#endif
