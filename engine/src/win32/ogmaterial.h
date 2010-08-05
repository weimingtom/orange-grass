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
#include <string>


class COGMaterial : public IOGMaterial
{
    COGMaterial ();

public:
    COGMaterial (const OGMaterialType& _Type);
	virtual ~COGMaterial ();
		
	// get material type.
	virtual OGMaterialType GetType () const;
		
	// apply the material.
	virtual void Apply ();

public:

    // parse material type
	static OGMaterialType ParseMaterialType (const std::string& _Type);

private:

    OGMaterialType  m_Type;
};

#endif
