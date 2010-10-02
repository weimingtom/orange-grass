/*
 *  LoadScreenController.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "LoadScreenController.h"
#include "OrangeGrass.h"


CLoadScreenController::CLoadScreenController() :	m_pResourceMgr(NULL),
													m_State(CSTATE_NO),
                                                    m_Type(SCRTYPE_LOAD),
													m_pHUD(NULL),
                                                    m_pCurLevel(NULL),
													m_bLoaded(false),
                                                    m_bDisplayed(false)
{
}


CLoadScreenController::~CLoadScreenController()
{	
	m_pResourceMgr = NULL;
	m_State = CSTATE_NO;
	m_bLoaded = false;
}


// Initialize controller
bool CLoadScreenController::Init ()
{
	if (!GetAppSettings()->Init("settings.xml"))
		return false;

	m_pGlobalVars = GetGlobalVars();
	m_CurLevel = m_pGlobalVars->GetSVar("level_0");
	m_fFOV = m_pGlobalVars->GetFVar("FOV");
	m_fZNear = m_pGlobalVars->GetFVar("z_near");
	m_fZFar = m_pGlobalVars->GetFVar("z_far");
	m_ScrWidth = m_pGlobalVars->GetIVar("view_width");
	m_ScrHeight = m_pGlobalVars->GetIVar("view_height");

	GetRenderer()->SetViewport(m_ScrWidth, m_ScrHeight, m_fZNear, m_fZFar, m_fFOV);
	m_pResourceMgr = GetResourceMgr();
    m_pResourceMgr->Init();
	if (!m_pResourceMgr->Load())
		return false;
	
	return true;
}


// Update controller
void CLoadScreenController::Update (unsigned long _ElapsedTime)
{
	if (!m_bLoaded && m_State == CSTATE_ACTIVE && m_bDisplayed)
	{
		GetActorParamsMgr()->Init();
        GetLevelManager()->Init();

		m_pCurLevel = GetLevelManager()->LoadLevel(m_CurLevel);
		if (m_pCurLevel == NULL)
		{
			m_State = CSTATE_FAILED;
			OG_LOG_ERROR("Failed to load level %s", m_CurLevel.c_str());
			return;
		}
		m_bLoaded = true;
		Deactivate();
	}
}


// Render controller scene
void CLoadScreenController::RenderScene ()
{
	GetRenderer()->ClearFrame(Vec4(0.0f, 0.0f, 0.0f, 1.0f));

	GetRenderer()->StartRenderMode(OG_RENDERMODE_SPRITES);
	m_pHUD->Render(Vec2(0, 0), Vec2((float)m_ScrWidth, (float)m_ScrHeight));
	GetRenderer()->FinishRenderMode();
	GetRenderer()->Reset();

	m_bDisplayed = true;
}


// Activate
void CLoadScreenController::Activate ()
{
	m_pHUD = m_pResourceMgr->GetSprite("load_scr");
    m_bDisplayed = false;
	m_State = CSTATE_ACTIVE;
}


// deactivate
void CLoadScreenController::Deactivate ()
{
	m_pResourceMgr->ReleaseSprite(m_pHUD);
    m_bDisplayed = false;
	m_State = CSTATE_INACTIVE;
}
