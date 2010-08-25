/*
 *  ogterrain.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogterrain.h"
#include "IOGMath.h"
#include "ogmaterial.h"
#include "tinyxml.h"


COGTerrain::COGTerrain () :	m_pMesh(NULL),
                            m_pMaterial(NULL)
{
    m_pRenderer = GetRenderer();
}


COGTerrain::~COGTerrain()
{
	m_pMesh = NULL;
    OG_SAFE_DELETE(m_pMaterial);
}


// Load terrain.
bool COGTerrain::Load ()
{
	switch (m_LoadState)
	{
	case OG_RESSTATE_UNKNOWN:
		return false;

	case OG_RESSTATE_LOADED:
        return true;    
	}

	Cfg cfg;
	if (!LoadConfig(cfg))
	{
		return false;
	}

    m_pMesh = GetResourceMgr()->GetMesh(cfg.mesh_alias);
    m_pMaterial = new COGMaterial(OG_MAT_SOLID);

	std::vector<Cfg::TextureCfg>::const_iterator iter;
	for (iter = cfg.texture_cfg_list.begin(); iter != cfg.texture_cfg_list.end(); ++iter)
	{
		IOGTexture* pTexture = GetResourceMgr()->GetTexture((*iter).alias);
		m_TextureList.push_back(pTexture);
	}

	m_LoadState = OG_RESSTATE_LOADED;
	return true;
}


// Load terrain configuration
bool COGTerrain::LoadConfig (COGTerrain::Cfg& _cfg)
{
    TiXmlDocument* pXmlSettings = new TiXmlDocument(m_ResourceFile.c_str());
    if (!pXmlSettings->LoadFile(m_ResourceFile.c_str()))
	{
        OG_LOG_ERROR("Failed to load config file %s for terrain", m_ResourceFile.c_str());
		OG_SAFE_DELETE(pXmlSettings);
        return false;
	}
    TiXmlHandle* hDoc = new TiXmlHandle (pXmlSettings);

    TiXmlHandle meshHandle = hDoc->FirstChild ("Mesh");
    if (meshHandle.Node())
    {
        TiXmlElement* pElement = meshHandle.Element();
		_cfg.mesh_alias = std::string(pElement->Attribute ("alias"));
    }
    TiXmlHandle mtlHandle = hDoc->FirstChild ("Material");
    int index = 0;
    TiXmlHandle TxHandle = mtlHandle.Child ( "Texture", index );
    while (TxHandle.Node ())
    {
        TiXmlElement* pElement = TxHandle.Element();
		
		Cfg::TextureCfg txcfg;
		txcfg.alias = std::string(pElement->Attribute ("alias"));
		_cfg.texture_cfg_list.push_back(txcfg);

		TxHandle = mtlHandle.Child ( "Texture", ++index );
    }

	OG_SAFE_DELETE(hDoc);
	OG_SAFE_DELETE(pXmlSettings);
	return true;
}


// Unload terrain.
void COGTerrain::Unload ()
{
	if (m_LoadState != OG_RESSTATE_LOADED)
	{
		return;
	}

	OG_SAFE_DELETE(m_pMaterial);
	m_TextureList.clear();

	m_LoadState = OG_RESSTATE_DEFINED;
}


// Render terrain.
void COGTerrain::Render (const MATRIX& _mView)
{
    m_pRenderer->SetMaterial(m_pMaterial);
    unsigned int numParts = m_pMesh->GetNumRenderables();
    for (unsigned int i = 0; i < numParts; ++i)
    {
        m_pRenderer->SetTexture(m_TextureList[i]);
        m_pMesh->Render (_mView, i);
    }
}


// Render.
void COGTerrain::Render (const MATRIX& _mView, unsigned int _Part)
{
    m_pRenderer->SetMaterial(m_pMaterial);
    m_pRenderer->SetTexture(m_TextureList[_Part]);
	m_pMesh->Render (_mView, _Part);
}


// Get num renderable parts.
unsigned int COGTerrain::GetNumRenderables () const
{
    return m_pMesh->GetNumRenderables();
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
