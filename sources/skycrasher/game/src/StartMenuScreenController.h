/*
 * OrangeGrass
 * Copyright (C) 2009 Vyacheslav Bogdanov.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/lgpl-3.0-standalone.html>.
 */
#ifndef STARTMENUSCREENCONTROLLER_H_
#define STARTMENUSCREENCONTROLLER_H_

#include "IOGScreenController.h"
#include "IOGSpritePool.h"
#include "IOGResourceMgr.h"
#include "IOGLevel.h"
#include "IOGGlobalVarsTable.h"
#include "IOGInputReceiver.h"
#include "IOGRenderer.h"
#include "IOGSettingsReader.h"


class CStartMenuScreenController :  public IOGScreenController, 
                                    public IOGInputReceiver
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
	virtual bool OnVectorChanged (const OGVec3& _vVec);

	// Touch event handler.
	virtual bool OnTouch (const OGVec2& _vPos, IOGTouchParam _param);
	
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
	OGVec2			m_LogoSprPos;
	OGVec2			m_LogoSprSize;

	std::string		m_BackSprStr;
	OGVec2			m_BackSprPos;
	OGVec2			m_BackSprSize;

	OGVec2			m_DemoLabelPos;

	std::string		m_NewBtnNSprStr;
	std::string		m_NewBtnPrSprStr;
	OGVec2			m_NewBtnPos;
	OGVec2			m_NewBtnSize;
#ifdef WIN32
	std::string		m_ExitBtnNSprStr;
	std::string		m_ExitBtnPrSprStr;
	OGVec2			m_ExitBtnPos;
	OGVec2			m_ExitBtnSize;
#endif
};

#endif
