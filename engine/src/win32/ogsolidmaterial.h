/*
 *  OGSolidMaterial.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGSOLIDMATERIAL_H_
#define OGSOLIDMATERIAL_H_

#include "IOGMaterial.h"


class COGSolidMaterial : public IOGMaterial
{
public:
    COGSolidMaterial ();
	virtual ~COGSolidMaterial ();
		
	// get material type.
	virtual OGMaterialType GetType () const;
		
	// apply the material.
	virtual void Apply () const;

private:

    OGMaterialType  m_Type;
};

#endif
