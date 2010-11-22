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
	virtual const Vec4& GetAmbient () const;

	// get material diffuse.
	virtual const Vec4& GetDiffuse () const;

	// get material specular.
	virtual const Vec4& GetSpecular () const;

	// set material ambient.
	virtual void SetAmbient (const Vec4& _Value);

	// set material diffuse.
	virtual void SetDiffuse (const Vec4& _Value);

	// set material specular.
	virtual void SetSpecular (const Vec4& _Value);

private:

    Vec4	m_Ambient;
    Vec4	m_Diffuse;
    Vec4	m_Specular;
};

#endif
