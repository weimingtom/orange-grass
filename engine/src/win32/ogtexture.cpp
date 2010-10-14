/*
 *  ogtexture.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 07.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenGL2.h"
#include "ogtexture.h"


COGTexture::COGTexture () : m_TextureId (0),
							m_pTexture (NULL)
{
	m_pTexture = (CTexture*)malloc(sizeof(CTexture));
	memset(m_pTexture, 0, sizeof(CTexture));

	IOGMapping* pNewMapping = new IOGMapping;
	pNewMapping->upper_left = Vec2(0.0f, 0.0f);
	pNewMapping->size = Vec2(0.0f, 0.0f);
	pNewMapping->t0 = Vec2(0.0f, 0.0f);
	pNewMapping->t1 = Vec2(1.0f, 1.0f);
	m_MappingsList.push_back(pNewMapping);

	m_Width = 0;
	m_Height = 0;
}


COGTexture::~COGTexture ()
{
	if (m_pTexture)
	{
		m_pTexture->ReleaseTexture(m_TextureId);
		free(m_pTexture);
		m_pTexture = NULL;

		std::vector<IOGMapping*>::iterator iter = m_MappingsList.begin();
		for (; iter != m_MappingsList.end(); ++iter)
		{
			OG_SAFE_DELETE((*iter));
		}
		m_MappingsList.clear();
	}
	m_TextureId = 0;
}


// load from file.
bool COGTexture::Load ()
{
	switch (m_LoadState)
	{
	case OG_RESSTATE_UNKNOWN:
		return false;

	case OG_RESSTATE_LOADED:
        return true;    
	}

	PVR_Texture_Header header;
	if(!m_pTexture->LoadTextureFromPVR(m_ResourceFile.c_str(), &m_TextureId, &header))
	{
        OG_LOG_ERROR("Failed to load texture file %s", m_ResourceFile.c_str());
		return false;
	}

	m_Width = header.dwWidth;
	m_Height = header.dwHeight;
	m_MappingsList[0]->size = Vec2((float)m_Width, (float)m_Height);

	std::vector<IOGMapping*>::iterator iter = m_MappingsList.begin();
	for (; iter != m_MappingsList.end(); ++iter)
	{
        IOGMapping* pMap = (*iter);
		pMap->t0 = Vec2(
			pMap->upper_left.x / m_Width, 
			(m_Height - pMap->upper_left.y - pMap->size.y) / m_Height);
		pMap->t1 = Vec2(
			(pMap->upper_left.x + pMap->size.x) / m_Width, 
			(m_Height - pMap->upper_left.y) / m_Height);
	}

	m_LoadState = OG_RESSTATE_LOADED;
	
	return true;
}


// Unload resource.
void COGTexture::Unload ()
{
	if (m_LoadState != OG_RESSTATE_LOADED)
	{
		return;
	}

	memset(m_pTexture, 0, sizeof(CTexture));
	m_TextureId = 0;

	m_Width = 0;
	m_Height = 0;

	m_LoadState = OG_RESSTATE_DEFINED;
}


// apply texture
void COGTexture::Apply () const
{
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
}


// get texture mapping
IOGMapping* COGTexture::GetMapping (unsigned int _Id)
{
	if (_Id < m_MappingsList.size() && m_LoadState == OG_RESSTATE_LOADED)
	{
		return m_MappingsList[_Id];
	}
	return NULL;
}


// add texture mapping
void COGTexture::AddMapping (IOGMapping* _pMapping)
{
	IOGMapping* pNewMapping = new IOGMapping;
	pNewMapping->upper_left = _pMapping->upper_left;
	pNewMapping->size = _pMapping->size;
	m_MappingsList.push_back(pNewMapping);
}
