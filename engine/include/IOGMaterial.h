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

enum OGMaterialType
{
    OG_MAT_NONE = -1,
    OG_MAT_SOLID,
    OG_MAT_ALPHATEST,
    OG_MAT_TEXTUREALPHABLEND
};


class IOGMaterial
{
public:
	virtual ~IOGMaterial () {}
		
	// get material type.
	virtual OGMaterialType GetType () const = 0;
		
	// apply the material.
	virtual void Apply () = 0;
};

#endif
