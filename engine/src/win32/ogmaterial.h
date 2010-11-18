/*
 *  OGMaterial.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGMATERIAL_H_
#define OGMATERIAL_H_

#include "IOGMaterial.h"


class COGMaterial : public IOGMaterial
{
public:
    COGMaterial ();
	virtual ~COGMaterial ();
		
	// get material ambient.
	virtual float GetAmbient () const;
		
	// get material diffuse.
	virtual float GetDiffuse () const;
		
	// get material specular.
	virtual float GetSpecular () const;
		
	// apply the material.
	virtual void Apply () const;

private:

    float	m_fAmbient;
    float	m_fDiffuse;
    float	m_fSpecular;
};

#endif
