/*
 *  ogterrain.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#define _CRT_SECURE_NO_WARNINGS
#include "orangegrass.h"
#include "ogterrain.h"
#include "IOGMath.h"
#include "ogmaterial.h"
#include "tinyxml.h"


COGTerrain::COGTerrain () :	m_pMesh(NULL),
							m_pTexture(NULL),
                            m_pMaterial(NULL)
{
}


COGTerrain::~COGTerrain()
{
	m_pMesh = NULL;
	m_pTexture = NULL;	
    OG_SAFE_DELETE(m_pMaterial);
}


// Load terrain.
bool COGTerrain::Load ()
{
	if (m_LoadState == OG_RESSTATE_UNKNOWN)
	{
		return false;
	}

	TiXmlDocument* pXmlSettings = new TiXmlDocument ( m_pResourceFile );
    if (!pXmlSettings->LoadFile (m_pResourceFile))
        return false;
    TiXmlHandle* hDoc = new TiXmlHandle (pXmlSettings);

    const char* model_alias = NULL;
    const char* model_mesh_alias = NULL;
	const char* model_texture_alias = NULL;
	const char* model_icon = NULL;

	TiXmlHandle modHandle = hDoc->FirstChild ("Terrain");
    if (modHandle.Node())
    {
        TiXmlElement* pElement = modHandle.Element();
        model_alias = pElement->Attribute ("alias");
    }
	TiXmlHandle meshHandle = hDoc->FirstChild ("Mesh");
    if (meshHandle.Node())
    {
        TiXmlElement* pElement = meshHandle.Element();
        model_mesh_alias = pElement->Attribute ("alias");
    }
	TiXmlHandle mtlHandle = hDoc->FirstChild ("Material");
    if (mtlHandle.Node())
    {
        TiXmlElement* pElement = mtlHandle.Element();
        model_texture_alias = pElement->Attribute ("texture");
    }
    TiXmlHandle edtHandle = hDoc->FirstChild ("Editor");
    if (edtHandle.Node())
    {
        TiXmlElement* pElement = edtHandle.Element();
        model_icon = pElement->Attribute ("icon");
    }

	SetResourceIcon (model_icon);
	m_pMesh = GetResourceMgr()->GetMesh(model_mesh_alias);
	m_pTexture = GetResourceMgr()->GetTexture(model_texture_alias);
    m_pMaterial = new COGMaterial(OG_MAT_SOLID);

	m_LoadState = OG_RESSTATE_LOADED;
	return true;
}


// Set terrain position.
void COGTerrain::SetWorldPosition (const Vec3& _vPos)
{
	m_vPosition = _vPos;
}


// Render terrain.
void COGTerrain::Render (const MATRIX& _mView)
{
    m_pMaterial->Apply();
    m_pTexture->Apply();
	m_pMesh->Render (_mView);
}


// Get ray intersection
bool COGTerrain::GetRayIntersection (const Vec3& _vRayPos, const Vec3& _vRayDir, Vec3* _pOutPos)
{
    if (m_pMesh)
    {
        return m_pMesh->GetRayIntersection(_vRayPos, _vRayDir, _pOutPos);
    }
    return false;
}


// Get combined AABB
const IOGAabb& COGTerrain::GetAABB () const
{
	return m_pMesh->GetAABB();
}
