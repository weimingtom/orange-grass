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
	m_Specular = OGVec4(0.0f, 0.0f, 0.0f, 0.0f);
	m_Ambient = OGVec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Diffuse = OGVec4(1.0f, 1.0f, 1.0f, 1.0f);
}


COGMaterial::~COGMaterial ()
{
}


// get material ambient.
const OGVec4& COGMaterial::GetAmbient () const
{
	return m_Ambient;
}


// get material diffuse.
const OGVec4& COGMaterial::GetDiffuse () const
{
	return m_Diffuse;
}


// get material specular.
const OGVec4& COGMaterial::GetSpecular () const
{
	return m_Specular;
}


// set material ambient.
void COGMaterial::SetAmbient (const OGVec4& _Value)
{
	m_Ambient = _Value;
}


// set material diffuse.
void COGMaterial::SetDiffuse (const OGVec4& _Value)
{
	m_Diffuse = _Value;
}


// set material specular.
void COGMaterial::SetSpecular (const OGVec4& _Value)
{
	m_Specular = _Value;
}
