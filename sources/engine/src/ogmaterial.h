/*
 * OrangeGrass
 * Copyright (C) 2009 Vyacheslav Bogdanov.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/lgpl-3.0-standalone.html>.
 */
#ifndef OGMATERIAL_H_
#define OGMATERIAL_H_

#include "IOGMaterial.h"


class COGMaterial : public IOGMaterial
{
public:
    COGMaterial ();
	virtual ~COGMaterial ();

    // load material from config
    virtual void LoadConfig (const OGMaterialCfg* _pCfg);

    // save material config
    virtual OGMaterialCfg SaveConfig ();

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
