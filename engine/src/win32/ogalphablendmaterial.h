/*
 *  OGAlphaBlendMaterial.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGALPHABLENDMATERIAL_H_
#define OGALPHABLENDMATERIAL_H_

#include "IOGMaterial.h"


class COGAlphaBlendMaterial : public IOGMaterial
{
public:
    COGAlphaBlendMaterial ();
	virtual ~COGAlphaBlendMaterial ();
		
	// get material type.
	virtual OGMaterialType GetType () const;
		
	// apply the material.
	virtual void Apply () const;

private:

    OGMaterialType  m_Type;
};

#endif
