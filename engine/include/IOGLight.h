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

	// set light color.
	virtual void SetColor (const Vec4& _vColor) = 0;

	// get light color.
	virtual const Vec4& GetColor () const = 0;

	// set light direction.
	virtual void SetDirection (const Vec3& _vDirection) = 0;

	// get light direction.
	virtual const Vec3& GetDirection () const = 0;
};

#endif
