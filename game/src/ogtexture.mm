/*
 *  ogtexture.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 07.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogtexture.h"


COGTexture::COGTexture () : m_TextureId (0),
							m_pTexture (NULL)
{
	m_pTexture = (CTexture*)malloc(sizeof(CTexture));
	memset(m_pTexture, 0, sizeof(CTexture));
}


COGTexture::~COGTexture ()
{
	if (m_pTexture)
	{
		m_pTexture->ReleaseTexture(m_TextureId);
		free(m_pTexture);
		m_pTexture = NULL;
	}
	m_TextureId = 0;
}


// load from file.
bool COGTexture::LoadFromFile (const char* _pTextureFile)
{
	if(!m_pTexture->LoadTextureFromPVR(_pTextureFile, &m_TextureId))
	{
		return false;
	}
	
	return true;
}
