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
#include "IOGActorManager.h"
#include "IOGRenderer.h"
#include "IOGGlobalVarsTable.h"
#include "IOGSpritePool.h"
#include "IOGSettingsReader.h"


class CGameScreenController :   public IScreenController, 
                                public IOGInputReceiver,
                                public IOGGameEventsHandler
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
	virtual bool OnVectorChanged (const OGVec3& _vVec);

	// Touch event handler.
	virtual bool OnTouch (const OGVec2& _vPos, IOGTouchParam _param);

	// Level finish point handler
	virtual void OnReachedFinishPoint ();

	// Level finish handler
	virtual void OnLevelFinish ();

private:

    // Update camera.
	void UpdateCamera ();

private:
		
	IOGGlobalVarsTable* m_pGlobalVars;
	IOGSettingsReader*	m_pReader;
	IOGResourceMgr*		m_pResourceMgr;
	IOGSceneGraph*		m_pSg;
	IOGRenderer*		m_pRenderer;
	IOGCamera*			m_pCamera;
    IOGActor*			m_pPlayer;

    IOGGuiLifebar*      m_pLifeHUD;
    IOGGuiBonusbar*	    m_pSpecHUD;
    IOGGuiWeaponPanel*	m_pWeaponHUD;

	ControllerState	m_State;
    ScreenType      m_Type;
    IOGLevel*	    m_pCurLevel;
	OGMatrix			m_mProjection; 
	OGMatrix			m_mView;

	float			m_fFOV;
	float			m_fZNear;
	float			m_fZFar;
	int				m_ScrWidth;
	int				m_ScrHeight;
	float			m_fCameraTargetDistance;
	float			m_fCameraMargins;
	OGVec3			m_vCameraDir;
	OGVec3			m_vCameraOffset;

	unsigned long	m_ElapsedTime;
    bool            m_bFinishLine;
};

#endif
