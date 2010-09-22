/*
 *  ogmodel.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "OrangeGrass.h"
#include "ogmodel.h"
#include "tinyxml.h"


COGModel::COGModel() :	m_pMesh(NULL),
						m_pTexture(NULL),
                        m_pMaterial(NULL)
{
    m_pRenderer = GetRenderer();
}


COGModel::~COGModel()
{
	m_pMesh = NULL;
	m_pTexture = NULL;	
}


// Load model.
bool COGModel::Load ()
{
	switch (m_LoadState)
	{
	case OG_RESSTATE_UNKNOWN:
		return false;

	case OG_RESSTATE_LOADED:
        return true;    
	}

	Cfg modelcfg;
	if (!LoadConfig(modelcfg))
	{
        OG_LOG_ERROR("Failed to load model from config");
		return false;
	}

	m_pMesh = GetResourceMgr()->GetMesh(modelcfg.mesh_alias);
	m_pTexture = GetResourceMgr()->GetTexture(modelcfg.texture_alias);
	m_pMaterial = GetMaterialManager()->GetMaterial(modelcfg.material_type);

	m_LoadState = OG_RESSTATE_LOADED;
    return true;
}


// Load model configuration
bool COGModel::LoadConfig (COGModel::Cfg& _cfg)
{
	TiXmlDocument* pXmlSettings = new TiXmlDocument(m_ResourceFile.c_str());
    if (!pXmlSettings->LoadFile(m_ResourceFile.c_str()))
	{
        OG_LOG_ERROR("Failed to load model config file %s", m_ResourceFile.c_str());
		OG_SAFE_DELETE(pXmlSettings);
        return false;
	}

	TiXmlHandle* hDoc = new TiXmlHandle(pXmlSettings);
	TiXmlHandle meshHandle = hDoc->FirstChild ("Mesh");
    if (meshHandle.Node())
    {
        TiXmlElement* pElement = meshHandle.Element();
		_cfg.mesh_alias = std::string(pElement->Attribute ("alias"));
    }
	TiXmlHandle mtlHandle = hDoc->FirstChild ("Material");
    if (mtlHandle.Node())
    {
        TiXmlElement* pElement = mtlHandle.Element();
        _cfg.texture_alias = std::string(pElement->Attribute ("texture"));
        _cfg.material_type = std::string(pElement->Attribute ("type"));
    }

	OG_SAFE_DELETE(hDoc);
	OG_SAFE_DELETE(pXmlSettings);
	return true;
}


// Unload resource.
void COGModel::Unload ()
{
	if (m_LoadState != OG_RESSTATE_LOADED)
	{
		return;
	}

	OG_SAFE_DELETE(m_pMaterial);

	m_LoadState = OG_RESSTATE_DEFINED;
}


// Update.
void COGModel::Update (unsigned long _ElapsedTime)
{
	m_pMesh->Update (_ElapsedTime);
}


// Render mesh.
void COGModel::Render (const MATRIX& _mView)
{
    m_pRenderer->SetMaterial(m_pMaterial);
    m_pRenderer->SetTexture(m_pTexture);
	m_pMesh->Render (_mView);
}

		
// Render.
void COGModel::Render (const MATRIX& _mView, unsigned int _Part)
{
    m_pRenderer->SetMaterial(m_pMaterial);
    m_pRenderer->SetTexture(m_pTexture);
	m_pMesh->Render (_mView, _Part);
}


// Get num renderable parts.
unsigned int COGModel::GetNumRenderables () const
{
    return m_pMesh->GetNumRenderables();
}


// Get combined AABB
const IOGAabb& COGModel::GetAABB () const
{
	return m_pMesh->GetAABB();
}


// Get model alias
const std::string& COGModel::GetAlias () const
{
    return m_ResourceAlias;
}
