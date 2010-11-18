/*
 *  ogmaterial.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenGL2.h"
#include "ogmaterial.h"


COGMaterial::COGMaterial ()
{
	m_fSpecular = 0.0f;
	m_fAmbient = 1.0f;
	m_fDiffuse = 1.0f;
}


COGMaterial::~COGMaterial ()
{
}


// get material ambient.
float COGMaterial::GetAmbient () const
{
	return m_fAmbient;
}


// get material diffuse.
float COGMaterial::GetDiffuse () const
{
	return m_fDiffuse;
}


// get material specular.
float COGMaterial::GetSpecular () const
{
	return m_fSpecular;
}


// apply the material.
void COGMaterial::Apply () const
{
}
