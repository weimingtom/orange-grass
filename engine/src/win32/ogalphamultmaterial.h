/*
 *  OGAlphaMultMaterial.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGALPHAMULTMATERIAL_H_
#define OGALPHAMULTMATERIAL_H_

#include "IOGMaterial.h"


class COGAlphaMultMaterial : public IOGMaterial
{
public:
    COGAlphaMultMaterial ();
	virtual ~COGAlphaMultMaterial ();
		
	// get material type.
	virtual OGMaterialType GetType () const;
		
	// apply the material.
	virtual void Apply () const;

private:

    OGMaterialType  m_Type;
};

#endif
