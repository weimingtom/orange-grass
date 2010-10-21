/*
 *  StartMenuScreenController.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef STARTMENUSCREENCONTROLLER_H_
#define STARTMENUSCREENCONTROLLER_H_

#include "IScreenController.h"
#include "IOGSprite.h"
#include "IOGResourceMgr.h"
#include "IOGLevel.h"
#include "IOGGlobalVarsTable.h"
#include "IOGInputReceiver.h"


class CStartMenuScreenController : public IScreenController, public IOGInputReceiver
{
public:
	CStartMenuScreenController();
	virtual ~CStartMenuScreenController();
	
	// Initialize controller
	virtual bool Init ();

	// Get controller state
	virtual ControllerState GetState () const { return m_State; }

	// Get controller type
    virtual ScreenType GetType () const { return m_Type; }

	// Update controller
	virtual void Update (unsigned long _ElapsedTime);
	
	// Render controller scene
	virtual void RenderScene ();
	
	// Activate
	virtual void Activate ();
	
	// deactivate
	virtual void Deactivate ();

    // Control vector change event handler.
	virtual void OnVectorChanged (const Vec3& _vVec);

	// Touch event handler.
	virtual void OnTouch (const Vec2& _vPos);
	
private:
	
	IOGGlobalVarsTable* m_pGlobalVars;
	IOGResourceMgr*	m_pResourceMgr;
	ControllerState	m_State;
    ScreenType      m_Type;
	IOGSprite*		m_pHUD;
	bool			m_bLoaded;
	bool			m_bDisplayed;

	float			m_fFOV;
	float			m_fZNear;
	float			m_fZFar;
	int				m_ScrWidth;
	int				m_ScrHeight;
};

#endif