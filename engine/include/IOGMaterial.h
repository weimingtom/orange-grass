/*
 *  IOGMaterial.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGMATERIAL_H_
#define IOGMATERIAL_H_

#include "Mathematics.h"


class IOGMaterial
{
public:
	virtual ~IOGMaterial () {}

	// get material ambient.
	virtual const Vec4& GetAmbient () const = 0;

	// get material diffuse.
	virtual const Vec4& GetDiffuse () const = 0;

	// get material specular.
	virtual const Vec4& GetSpecular () const = 0;

	// set material ambient.
	virtual void SetAmbient (float _Value) = 0;

	// set material diffuse.
	virtual void SetDiffuse (float _Value) = 0;

	// set material specular.
	virtual void SetSpecular (float _Value) = 0;
};

#endif
