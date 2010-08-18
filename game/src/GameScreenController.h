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
#include "IOGResourceMgr.h"
#include "IOGSceneGraph.h"
#include "IOGLevelManager.h"
#include "IOGInputReceiver.h"


class CGameScreenController : public IScreenController, public IOGInputReceiver
{
public:
	CGameScreenController();
	virtual ~CGameScreenController();
		
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

private:
		
	IOGResourceMgr*	m_pResourceMgr;
	IOGSceneGraph*	m_pSg;
	IOGCamera*		m_pCamera;

	ControllerState	m_State;
    ScreenType      m_Type;
    IOGLevel*	    m_pCurLevel;
	MATRIX			m_mProjection; 
	MATRIX			m_mView;
};

#endif
