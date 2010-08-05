/*
 *  ogmaterial.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenGL2.h"
#include "ogmaterial.h"


COGMaterial::COGMaterial () : m_Type(OG_MAT_NONE)
{
}


COGMaterial::COGMaterial (const OGMaterialType& _Type) : m_Type(_Type)
{
}


COGMaterial::~COGMaterial ()
{
    m_Type = OG_MAT_NONE;
}


// get material type.
OGMaterialType COGMaterial::GetType () const
{
    return m_Type;
}


// apply the material.
void COGMaterial::Apply ()
{
    switch (m_Type)
    {
    case OG_MAT_SOLID:
        glDisable (GL_BLEND); 
        glDisable (GL_ALPHA_TEST); 
        break;

    case OG_MAT_ALPHATEST:
        glAlphaFunc(GL_GREATER, 0.4f);
        glEnable(GL_ALPHA_TEST);
        break;

    case OG_MAT_TEXTUREALPHABLEND:
        glEnable (GL_BLEND); 
        glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        break;

    case OG_MAT_NONE:
    default:
        break;
    }
}


// parse material type
OGMaterialType COGMaterial::ParseMaterialType (const std::string& _Type)
{
	if (_Type.compare(std::string("solid")) == 0)
    {
        return OG_MAT_SOLID;
    }
    else if (_Type.compare(std::string("alpha_test")) == 0)
    {
        return OG_MAT_ALPHATEST;
    }
    else if (_Type.compare(std::string("tex_alpha")) == 0)
    {
        return OG_MAT_TEXTUREALPHABLEND;
    }

    return OG_MAT_NONE;
}
