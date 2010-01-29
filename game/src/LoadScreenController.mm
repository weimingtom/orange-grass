/*
 *  LoadScreenController.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "LoadScreenController.h"
#include "ogsprite.h"


CLoadScreenController::CLoadScreenController() :	m_pPlatform(NULL),
													m_pResourceMgr(NULL),
													m_pUIHandler(NULL),
													m_State(CSTATE_NO),
													m_pHUD(NULL),
													m_pLoadProgress(NULL),
													m_bLoaded(false)
{
}


CLoadScreenController::~CLoadScreenController()
{
	delete m_pHUD;
	delete m_pLoadProgress;
	
	m_pPlatform = NULL;
	m_pResourceMgr = NULL;
	m_pUIHandler = NULL;
	m_State = CSTATE_NO;
	m_pHUD = NULL;
	m_pLoadProgress = NULL;
	m_bLoaded = false;
}


// Initialize controller
bool CLoadScreenController::Init (IPlatform* _pPlatform)
{
	m_pPlatform = _pPlatform;
	m_pResourceMgr = m_pPlatform->GetResourceManager();
	m_pUIHandler = m_pPlatform->GetUIHandler();
	
	m_pHUD = new COGSprite();
	m_pLoadProgress = new COGSprite();
	
	m_pHUD->Init (m_pResourceMgr->GetTexture ("load_scr"));
	m_pLoadProgress->Init (m_pResourceMgr->GetTexture ("load_progress"));
	
	return true;
}


// Update controller
void CLoadScreenController::Update (unsigned int _ElapsedTime)
{
	if (!m_bLoaded && m_State == CSTATE_ACTIVE)
	{
		if (m_pResourceMgr->LoadNext())
		{
			m_bLoaded = false;
		}
		else
		{
			m_bLoaded = true;
			Deactivate();
		}
	}
}


// Render controller scene
void CLoadScreenController::RenderScene ()
{
	if (!m_bLoaded && m_State == CSTATE_ACTIVE)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		m_pHUD->SetPosition(0, 0, 480, 320);
		m_pHUD->Render ();
		float fProgress = m_pResourceMgr->GetLoadProgress ();
		m_pLoadProgress->SetPosition(55, 273, 383 * fProgress / 100.0f, 13);
		m_pLoadProgress->Render ();
		m_pUIHandler->DisplayText(50, 86, 0.4f, RGBA(255,25,25,255), "%3.f", fProgress);
		m_pUIHandler->DisplayDefaultTitle("", "", eDisplayTextLogoIMG);
		m_pUIHandler->Flush();
	}
}


// Activate
void CLoadScreenController::Activate ()
{
	glClearColor(f2vt(0.0f), f2vt(0.0f), f2vt(0.0f), f2vt(1.0f));
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	m_State = CSTATE_ACTIVE;
}


// deactivate
void CLoadScreenController::Deactivate ()
{
	m_State = CSTATE_INACTIVE;
}
