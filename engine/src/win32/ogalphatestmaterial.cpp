/*
 *  ogalphatestmaterial.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenGL2.h"
#include "ogalphatestmaterial.h"


COGAlphaTestMaterial::COGAlphaTestMaterial () : m_Type(OG_MAT_ALPHATEST)
{
}


COGAlphaTestMaterial::~COGAlphaTestMaterial ()
{
    m_Type = OG_MAT_NONE;
}


// get material type.
OGMaterialType COGAlphaTestMaterial::GetType () const
{
    return m_Type;
}


// apply the material.
void COGAlphaTestMaterial::Apply () const
{
	glAlphaFunc(GL_GREATER, 0.4f);
	glEnable(GL_ALPHA_TEST);
}
