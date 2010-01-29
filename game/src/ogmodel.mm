/*
 *  ogmodel.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "ogmodel.h"


COGModel::COGModel() :	m_pMesh(NULL),
						m_pTexture(NULL)
{
}


COGModel::~COGModel()
{
	m_pMesh = NULL;
	m_pTexture = NULL;	
}


// Load model.
bool COGModel::Load (IOGMesh* _pMesh, IOGTexture* _pTexture)
{
	m_pMesh = _pMesh;
	m_pTexture = _pTexture;
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
	glBindTexture(GL_TEXTURE_2D, m_pTexture->GetTextureId());
	m_pMesh->Render (_mView);
}
