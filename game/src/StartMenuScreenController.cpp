/*
 *  StartMenuScreenController.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "StartMenuScreenController.h"
#include "OrangeGrass.h"


CStartMenuScreenController::CStartMenuScreenController() :	m_pResourceMgr(NULL),
															m_State(CSTATE_NO),
															m_Type(SCRTYPE_STARTMENU),
															m_pHUD(NULL),
															m_bLoaded(false),
															m_bDisplayed(false)
{
}


CStartMenuScreenController::~CStartMenuScreenController()
{	
	m_pResourceMgr = NULL;
	m_State = CSTATE_NO;
	m_bLoaded = false;
}


// Initialize controller
bool CStartMenuScreenController::Init ()
{
	if (!GetAppSettings()->Init("settings.xml"))
		return false;

	m_pGlobalVars = GetGlobalVars();
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

	GetInput()->RegisterReceiver(this);
	
	return true;
}


// Update controller
void CStartMenuScreenController::Update (unsigned long _ElapsedTime)
{
	if (m_State == CSTATE_ACTIVE)
	{
	}
}


// Render controller scene
void CStartMenuScreenController::RenderScene ()
{
	GetRenderer()->ClearFrame(Vec4(0.0f, 0.0f, 0.0f, 1.0f));

	GetRenderer()->StartRenderMode(OG_RENDERMODE_SPRITES);
	m_pHUD->Render(Vec2(112, 10), Vec2(256.0f, 128.0f));
	GetRenderer()->FinishRenderMode();
	GetRenderer()->Reset();

	m_bDisplayed = true;
}


// Activate
void CStartMenuScreenController::Activate ()
{
	m_pHUD = m_pResourceMgr->GetSprite("logo");
    m_bDisplayed = false;
	m_State = CSTATE_ACTIVE;
}


// deactivate
void CStartMenuScreenController::Deactivate ()
{
	m_pResourceMgr->ReleaseSprite(m_pHUD);
    m_bDisplayed = false;
	m_State = CSTATE_INACTIVE;
}


// Control vector change event handler.
void CStartMenuScreenController::OnVectorChanged (const Vec3& _vVec)
{
}


// Touch event handler.
void CStartMenuScreenController::OnTouch (const Vec2& _vPos)
{
	if (m_State == CSTATE_ACTIVE)
	{
		Deactivate();
	}
}
