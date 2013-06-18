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
