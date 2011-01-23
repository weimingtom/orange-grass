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
#include "IOGSpritePool.h"
#include "IOGResourceMgr.h"
#include "IOGLevel.h"
#include "IOGGlobalVarsTable.h"
#include "IOGInputReceiver.h"
#include "IOGRenderer.h"
#include "IOGSettingsReader.h"


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
	virtual bool OnVectorChanged (const Vec3& _vVec);

	// Touch event handler.
	virtual bool OnTouch (const Vec2& _vPos, IOGTouchParam _param);
	
private:
	
	IOGGlobalVarsTable* m_pGlobalVars;
	IOGResourceMgr*	    m_pResourceMgr;
	IOGRenderer*	    m_pRenderer;
	IOGSettingsReader*	m_pReader;

	ControllerState	m_State;
    ScreenType      m_Type;
	bool			m_bLoaded;

    IOGSprite*		m_pLogo;
    IOGSprite*		m_pBack;
    IOGGuiButton*   m_pNewBtn;
    IOGGuiButton*   m_pExitBtn;

	// UI layout settings
	std::string		m_LogoSprStr;
	Vec2			m_LogoSprPos;
	Vec2			m_LogoSprSize;

	std::string		m_BackSprStr;
	Vec2			m_BackSprPos;
	Vec2			m_BackSprSize;

	Vec2			m_DemoLabelPos;

	std::string		m_NewBtnNSprStr;
	std::string		m_NewBtnPrSprStr;
	Vec2			m_NewBtnPos;
	Vec2			m_NewBtnSize;
#ifdef WIN32
	std::string		m_ExitBtnNSprStr;
	std::string		m_ExitBtnPrSprStr;
	Vec2			m_ExitBtnPos;
	Vec2			m_ExitBtnSize;
#endif
};

#endif
