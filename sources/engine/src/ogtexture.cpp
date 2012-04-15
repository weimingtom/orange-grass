/*
 *  ogtexture.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 07.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenGL2.h"
#include "pvr/PVRTC.h"
#include "ogtexture.h"


COGTexture::COGTexture () : m_TextureId (0)
{
	IOGMapping* pNewMapping = new IOGMapping;
	pNewMapping->upper_left = OGVec2(0.0f, 0.0f);
	pNewMapping->size = OGVec2(0.0f, 0.0f);
	pNewMapping->t0 = OGVec2(0.0f, 0.0f);
	pNewMapping->t1 = OGVec2(1.0f, 1.0f);
	m_MappingsList.push_back(pNewMapping);

	m_Width = 0;
	m_Height = 0;
}


COGTexture::~COGTexture ()
{
	if (m_TextureId != 0)
	{
        glDeleteTextures(1, &m_TextureId);

		std::vector<IOGMapping*>::iterator iter = m_MappingsList.begin();
		for (; iter != m_MappingsList.end(); ++iter)
		{
			OG_SAFE_DELETE((*iter));
		}
		m_MappingsList.clear();
    	m_TextureId = 0;
	}
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
            
    case OG_RESSTATE_DEFINED:
        break;
	}

    TextureImageData* pImgData = LoadTextureFromPVR(m_ResourceFile.c_str());
	if(!pImgData)
	{
        OG_LOG_ERROR("Failed to load texture file %s", m_ResourceFile.c_str());
		return false;
	}

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &m_TextureId);
    glBindTexture(GL_TEXTURE_2D, m_TextureId);

	m_Width = pImgData->dwWidth;
	m_Height = pImgData->dwHeight;
    for (unsigned int i = 0; i <= pImgData->dwMipLevels; ++i)
    {
        if (pImgData->isCompressed)
        {
            glCompressedTexImage2D(GL_TEXTURE_2D, i, pImgData->textureFormat, 
                pImgData->pLevels[i].dwSizeX, pImgData->pLevels[i].dwSizeY, 0,
                pImgData->pLevels[i].dwDataSize, pImgData->pLevels[i].pData);
        }
        else
        {
            glTexImage2D(GL_TEXTURE_2D, i, pImgData->textureType,
                pImgData->pLevels[i].dwSizeX, pImgData->pLevels[i].dwSizeY, 0, 
                pImgData->textureType, pImgData->textureFormat, pImgData->pLevels[i].pData);
        }
        free(pImgData->pLevels[i].pData);
    }

    if(!pImgData->dwMipLevels)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    free(pImgData->pLevels);
    free(pImgData);
    pImgData = NULL;
    m_MappingsList[0]->size = OGVec2((float)m_Width, (float)m_Height);

	std::vector<IOGMapping*>::iterator iter = m_MappingsList.begin();
	for (; iter != m_MappingsList.end(); ++iter)
	{
        IOGMapping* pMap = (*iter);
		pMap->t0 = OGVec2(
			pMap->upper_left.x / m_Width, 
			(m_Height - pMap->upper_left.y - pMap->size.y) / m_Height);
		pMap->t1 = OGVec2(
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
