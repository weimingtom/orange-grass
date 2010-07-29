/*
 *  ogmodel.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "orangegrass.h"
#include "ogmodel.h"
#include "ogmaterial.h"
#include "tinyxml.h"


COGModel::COGModel() :	m_pMesh(NULL),
						m_pTexture(NULL),
                        m_pMaterial(NULL)
{
}


COGModel::~COGModel()
{
	m_pMesh = NULL;
	m_pTexture = NULL;	
    delete m_pMaterial;
    m_pMaterial = NULL;
}


// Load model.
bool COGModel::Load ()
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
	const char* model_material_type = NULL;
	const char* model_icon = NULL;

	TiXmlHandle modHandle = hDoc->FirstChild ("Model");
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
        model_material_type = pElement->Attribute ("type");
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
    OGMaterialType mattype = COGMaterial::ParseMaterialType(model_material_type);
    if (mattype != OG_MAT_NONE)
    {
        m_pMaterial = new COGMaterial(mattype);
        return false;
    }

	m_LoadState = OG_RESSTATE_LOADED;

    return true;
}


// Update mesh animation.
void COGModel::UpdateAnimation (int _ElapsedTime)
{
	m_pMesh->UpdateAnimation (_ElapsedTime);
}


// Render mesh.
void COGModel::Render (const MATRIX& _mView)
{
    m_pMaterial->Apply();
    m_pTexture->Apply();
	m_pMesh->Render (_mView);
}


// Get number of parts
int COGModel::GetNumParts () const
{
	return m_pMesh->GetNumParts();
}


// Get AABB for the specified part
const IOGAabb& COGModel::GetAABB ( int _part ) const
{
	return m_pMesh->GetAABB(_part);
}


// Get combined AABB
const IOGAabb& COGModel::GetAABB () const
{
	return m_pMesh->GetAABB();
}
