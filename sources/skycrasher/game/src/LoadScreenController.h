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
#ifndef LOADSCREENCONTROLLER_H_
#define LOADSCREENCONTROLLER_H_

#include "IOGScreenController.h"
#include "IOGSprite.h"
#include "IOGResourceMgr.h"
#include "IOGLevel.h"
#include "IOGGlobalVarsTable.h"
#include "IOGRenderer.h"
#include "IOGSettingsReader.h"


class CLoadScreenController : public IOGScreenController
{
public:
	CLoadScreenController();
	virtual ~CLoadScreenController();
	
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
	
private:
	
	IOGGlobalVarsTable* m_pGlobalVars;
	IOGResourceMgr*	    m_pResourceMgr;
	IOGRenderer*	    m_pRenderer;
	IOGSettingsReader*	m_pReader;

	ControllerState	m_State;
    ScreenType      m_Type;
	IOGSprite*		m_pLoadSpr;
	IOGLevel*		m_pCurLevel;
	bool			m_bLoaded;
	bool			m_bDisplayed;

	int				m_ScrWidth;
	int				m_ScrHeight;

	// UI layout settings
	std::string		m_LoadSprStr;
	OGVec2			m_LoadSprPos;
	OGVec2			m_LoadSprSize;

	OGVec2			m_LoadLabelPos;
};

#endif
