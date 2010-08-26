/*
 *  ogresourcemgr.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 07.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogmaterialmanager.h"
#include "ogsolidmaterial.h"
#include "ogalphatestmaterial.h"
#include "ogalphablendmaterial.h"


COGMaterialManager::COGMaterialManager ()
{
}


COGMaterialManager::~COGMaterialManager ()
{
	std::map<OGMaterialType, IOGMaterial*>::iterator iter = m_MaterialsList.begin();
	for( ; iter != m_MaterialsList.end(); ++iter )
	{
		OG_SAFE_DELETE (iter->second);
	}
}


// initialize materials.
bool COGMaterialManager::Init ()
{
	m_MaterialsList[OG_MAT_SOLID] = new COGSolidMaterial();
	m_MaterialsList[OG_MAT_ALPHATEST] = new COGAlphaTestMaterial();
	m_MaterialsList[OG_MAT_TEXTUREALPHABLEND] = new COGAlphaBlendMaterial();
	return true;
}


// get material.
IOGMaterial* COGMaterialManager::GetMaterial (const std::string& _Alias)
{
	OGMaterialType type = ParseMaterialType(_Alias);
	if (type != OG_MAT_NONE)
	{
		return m_MaterialsList[type];
	}
	return NULL;
}


// get material.
IOGMaterial* COGMaterialManager::GetMaterial (OGMaterialType _Type)
{
	if (_Type != OG_MAT_NONE)
	{
		return m_MaterialsList[_Type];
	}
	return NULL;
}


// parse material type
OGMaterialType COGMaterialManager::ParseMaterialType (const std::string& _Type)
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
