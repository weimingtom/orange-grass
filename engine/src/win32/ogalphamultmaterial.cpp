/*
 *  ogalphamultmaterial.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenGL2.h"
#include "ogalphamultmaterial.h"


COGAlphaMultMaterial::COGAlphaMultMaterial () : m_Type(OG_MAT_TEXTUREALPHAMULT)
{
}


COGAlphaMultMaterial::~COGAlphaMultMaterial ()
{
    m_Type = OG_MAT_NONE;
}


// get material type.
OGMaterialType COGAlphaMultMaterial::GetType () const
{
    return m_Type;
}


// apply the material.
void COGAlphaMultMaterial::Apply () const
{
	glEnable (GL_BLEND); 
	glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_ALPHA_TEST);
}
