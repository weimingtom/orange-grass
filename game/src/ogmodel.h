/*
 *  ogmodel.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGMODEL_H_
#define OGMODEL_H_

#include "IOGModel.h"


class COGModel : public IOGModel
{
public:
	COGModel();
	virtual ~COGModel();
		
	// Load model.
	virtual bool Load (IOGMesh* _pMesh, IOGTexture* _pTexture);
		
	// Update mesh animation.
	virtual void UpdateAnimation (int _ElapsedTime);
		
	// Render mesh.
	virtual void Render (const MATRIX& _mView);
		
public:

	IOGMesh*	m_pMesh;	
	IOGTexture*	m_pTexture;
};


#endif
