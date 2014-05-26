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
#ifndef IOGMATERIAL_H_
#define IOGMATERIAL_H_

#include "IOGRenderTypes.h"
#include "IOGVector.h"
#include <string>


struct OGMaterialCfg
{
    std::string texture_alias;
    OGBlendType blend_type;
    OGVec4 material_ambient;
    OGVec4 material_diffuse;
    OGVec4 material_specular;
};


class IOGMaterial
{
public:
	virtual ~IOGMaterial () {}

    // load material from config
    virtual void LoadConfig (const OGMaterialCfg* _pCfg) = 0;

    // save material config
    virtual OGMaterialCfg SaveConfig () = 0;

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
