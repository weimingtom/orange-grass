/*
 *  LoadScreenController.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef LOADSCREENCONTROLLER_H_
#define LOADSCREENCONTROLLER_H_

#include "IScreenController.h"
#include "IPlatform.h"
#include "IOGSprite.h"


class CLoadScreenController : public IScreenController
{
public:
	CLoadScreenController();
	virtual ~CLoadScreenController();
	
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
	
	ControllerState	m_State;
	IOGSprite*		m_pHUD;
	IOGSprite*		m_pLoadProgress;
	IOGResourceMgr*	m_pResourceMgr;
	CDisplayText*	m_pUIHandler;
	IPlatform*		m_pPlatform;
	bool			m_bLoaded;
};

#endif