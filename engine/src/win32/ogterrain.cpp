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
                            m_pMaterial(NULL)
{
    for (int i = 0; i < MAX_TERRAIN_PARTS; ++i)
        m_pTexture[i] = NULL;
}


COGTerrain::~COGTerrain()
{
    for (int i = 0; i < MAX_TERRAIN_PARTS; ++i)
        m_pTexture[i] = NULL;
	m_pMesh = NULL;
    OG_SAFE_DELETE(m_pMaterial);
}


// Load terrain.
bool COGTerrain::Load ()
{
	if (m_LoadState == OG_RESSTATE_UNKNOWN)
	{
		return false;
	}

    IOGDeserializer* pDS = GetDeserializer(m_pResourceFile);
    std::string val, model_alias, mesh_alias, model_icon;
    pDS->StartDoc();
        pDS->StartMap();
            pDS->ReadValue(val);
            pDS->StartMap();
                pDS->ReadPair(std::string("alias"), model_alias);
                pDS->ReadPair(std::string("mesh"), mesh_alias);
                pDS->ReadValue(std::string("material"));
                if (pDS->StartSeq())
                {
                    std::string texture;
                    int index = 0;
                    while (pDS->StartMap())
                    {
                        if (pDS->ReadPair(std::string("texture"), texture))
                        {
                            m_pTexture[index++] = GetResourceMgr()->GetTexture(texture.c_str());
                        }
                        pDS->FinishMap();
                    }
                }
                pDS->ReadPair(std::string("icon"), model_icon);
            pDS->FinishMap();
        pDS->FinishMap();
    pDS->FinishDoc();
    
    pDS->Close();
    OG_SAFE_DELETE(pDS);

    SetResourceIcon (model_icon.c_str());
    m_pMesh = GetResourceMgr()->GetMesh(mesh_alias.c_str());
    m_pMaterial = new COGMaterial(OG_MAT_SOLID);


    //TiXmlDocument* pXmlSettings = new TiXmlDocument ( m_pResourceFile );
    //if (!pXmlSettings->LoadFile (m_pResourceFile))
    //    return false;
    //TiXmlHandle* hDoc = new TiXmlHandle (pXmlSettings);

    //const char* model_alias = NULL;
    //const char* model_mesh_alias = NULL;
    //const char* model_icon = NULL;

    //TiXmlHandle modHandle = hDoc->FirstChild ("Terrain");
    //if (modHandle.Node())
    //{
    //    TiXmlElement* pElement = modHandle.Element();
    //    model_alias = pElement->Attribute ("alias");
    //}
    //TiXmlHandle meshHandle = hDoc->FirstChild ("Mesh");
    //if (meshHandle.Node())
    //{
    //    TiXmlElement* pElement = meshHandle.Element();
    //    model_mesh_alias = pElement->Attribute ("alias");
    //}
    //TiXmlHandle mtlHandle = hDoc->FirstChild ("Material");
    //int index = 0;
    //TiXmlHandle TxHandle = mtlHandle.Child ( "Texture", index );
    //while (TxHandle.Node ())
    //{
    //    TiXmlElement* pElement = TxHandle.Element();
    //    const char* alias = pElement->Attribute ("alias");
    //    m_pTexture[index] = GetResourceMgr()->GetTexture(alias);
    //    TxHandle = mtlHandle.Child ( "Texture", ++index );
    //}
    //TiXmlHandle edtHandle = hDoc->FirstChild ("Editor");
    //if (edtHandle.Node())
    //{
    //    TiXmlElement* pElement = edtHandle.Element();
    //    model_icon = pElement->Attribute ("icon");
    //}

    //SetResourceIcon (model_icon);
    //m_pMesh = GetResourceMgr()->GetMesh(model_mesh_alias);
    //m_pMaterial = new COGMaterial(OG_MAT_SOLID);

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
    unsigned int numParts = m_pMesh->GetNumRenderables();
    for (unsigned int i = 0; i < numParts; ++i)
    {
        m_pTexture[i]->Apply();
        m_pMesh->Render (_mView, i);
    }
}


// Render.
void COGTerrain::Render (const MATRIX& _mView, unsigned int _Part)
{
    m_pMaterial->Apply();
    m_pTexture[_Part]->Apply();
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
