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


class IOGMaterial
{
public:
	virtual ~IOGMaterial () {}

	// get material ambient.
	virtual float GetAmbient () const = 0;
		
	// get material diffuse.
	virtual float GetDiffuse () const = 0;
		
	// get material specular.
	virtual float GetSpecular () const = 0;
		
	// apply the material.
	virtual void Apply () const = 0;
};

#endif
