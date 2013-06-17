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

#include "IOGRenderTypes.h"
#include "IOGVector.h"


class IOGMaterial
{
public:
	virtual ~IOGMaterial () {}

	// get material ambient.
	virtual const OGVec4& GetAmbient () const = 0;

	// get material diffuse.
	virtual const OGVec4& GetDiffuse () const = 0;

	// get material specular.
	virtual const OGVec4& GetSpecular () const = 0;

	// get material blend.
	virtual OGBlendType GetBlend () const = 0;

	// set material ambient.
	virtual void SetAmbient (const OGVec4& _Value) = 0;

	// set material diffuse.
	virtual void SetDiffuse (const OGVec4& _Value) = 0;

	// set material specular.
	virtual void SetSpecular (const OGVec4& _Value) = 0;

	// set material blend.
	virtual void SetBlend (OGBlendType _Value) = 0;
};

#endif
