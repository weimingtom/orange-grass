/*
 *  GameScreenController.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef GAMESCREENCONTROLLER_H_
#define GAMESCREENCONTROLLER_H_

#include "IScreenController.h"
#include "IPlatform.h"
#include "ogterrain.h"
#include "IOGCamera.h"


class CGameScreenController : public IScreenController
{
public:
	CGameScreenController();
	virtual ~CGameScreenController();
		
	// Initialize controller
	virtual bool Init (IPlatform* _pPlatform);
		
	// Get controller state
	virtual ControllerState GetState () const { return m_State; }
		
	// Update controller
	virtual void Update (unsigned int _ElapsedTime);
		
	// Render controller scene
	virtual void RenderScene ();
		
	// Activate
	virtual void Activate ();
		
	// deactivate
	virtual void Deactivate ();
		
private:
		
	IPlatform*		m_pPlatform;
	IOGResourceMgr*	m_pResourceMgr;
	CDisplayText*	m_pUIHandler;
	ControllerState	m_State;
	IOGModel*		m_pModel;
	IOGTerrain*		m_pTerrain;
	IOGCamera*		m_pCamera;
	MATRIX			m_mProjection; 
	MATRIX			m_mView;
};

#endif
