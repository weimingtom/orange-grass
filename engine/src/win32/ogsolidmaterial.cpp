/*
 *  ogsolidmaterial.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenGL2.h"
#include "ogsolidmaterial.h"


COGSolidMaterial::COGSolidMaterial () : m_Type(OG_MAT_SOLID)
{
}


COGSolidMaterial::~COGSolidMaterial ()
{
    m_Type = OG_MAT_NONE;
}


// get material type.
OGMaterialType COGSolidMaterial::GetType () const
{
    return m_Type;
}


// apply the material.
void COGSolidMaterial::Apply () const
{
	glDisable (GL_BLEND); 
	glDisable (GL_ALPHA_TEST); 
}
