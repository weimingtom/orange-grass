/*
 *  OGAlphaTestMaterial.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGALPHATESTMATERIAL_H_
#define OGALPHATESTMATERIAL_H_

#include "IOGMaterial.h"


class COGAlphaTestMaterial : public IOGMaterial
{
public:
    COGAlphaTestMaterial ();
	virtual ~COGAlphaTestMaterial ();
		
	// get material type.
	virtual OGMaterialType GetType () const;
		
	// apply the material.
	virtual void Apply () const;

private:

    OGMaterialType  m_Type;
};

#endif
