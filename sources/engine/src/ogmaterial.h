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
	virtual const OGVec4& GetAmbient () const;

	// get material diffuse.
	virtual const OGVec4& GetDiffuse () const;

	// get material specular.
	virtual const OGVec4& GetSpecular () const;

	// get material blend.
	virtual OGBlendType GetBlend () const;

	// set material ambient.
	virtual void SetAmbient (const OGVec4& _Value);

	// set material diffuse.
	virtual void SetDiffuse (const OGVec4& _Value);

	// set material specular.
	virtual void SetSpecular (const OGVec4& _Value);

	// set material blend.
	virtual void SetBlend (OGBlendType _Value);

private:

    OGVec4	m_Ambient;
    OGVec4	m_Diffuse;
    OGVec4	m_Specular;

    OGBlendType m_Blend;
};

#endif
