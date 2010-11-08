/*
 *  StartMenuScreenController.cpp
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
															m_bLoaded(false)
{
    m_pLogo = NULL;
    m_pBack = NULL;
	
    m_pRenderer = GetRenderer();
	m_pGlobalVars = GetGlobalVars();
	m_pResourceMgr = GetResourceMgr();

    m_pNewBtn = GetSpritePool()->CreateButton();
    m_pExitBtn = GetSpritePool()->CreateButton();
}


CStartMenuScreenController::~CStartMenuScreenController()
{	
	m_pResourceMgr = NULL;
	m_State = CSTATE_NO;
	m_bLoaded = false;
    GetSpritePool()->DestroyButton(m_pNewBtn);
    GetSpritePool()->DestroyButton(m_pExitBtn);
}


// Initialize controller
bool CStartMenuScreenController::Init ()
{
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
	m_pRenderer->ClearFrame(Vec4(0.0f, 0.0f, 0.0f, 1.0f));

    if (m_State != CSTATE_ACTIVE)
        return;

	m_pRenderer->StartRenderMode(OG_RENDERMODE_SPRITES);
	m_pBack->Render(Vec2(73, 65), Vec2(334.0f, 189.0f));
	m_pLogo->Render(Vec2(112, 10), Vec2(256.0f, 128.0f));
    m_pNewBtn->Render();
    m_pExitBtn->Render();
	m_pRenderer->FinishRenderMode();
	m_pRenderer->StartRenderMode(OG_RENDERMODE_TEXT);
    m_pRenderer->DisplayString(Vec2(80.0f,93.0f), 0.3f, 0x7FFFFFFF, "Demo version: %d.%d", 0, 14);
	m_pRenderer->FinishRenderMode();
	m_pRenderer->Reset();
}


// Activate
void CStartMenuScreenController::Activate ()
{
    m_pLogo = m_pResourceMgr->GetSprite("logo");
    m_pBack = m_pResourceMgr->GetSprite("back");
    m_pNewBtn->Load("new_n", "new_pr", Vec2(222.0f, 42.0f));
    m_pNewBtn->SetPosition(Vec2(129, 125));
    m_pExitBtn->Load("exit_n", "exit_pr", Vec2(222.0f, 42.0f));
    m_pExitBtn->SetPosition(Vec2(129, 175));
    m_State = CSTATE_ACTIVE;
}


// deactivate
void CStartMenuScreenController::Deactivate ()
{
    m_pResourceMgr->ReleaseSprite(m_pLogo);
    m_pResourceMgr->ReleaseSprite(m_pBack);
    m_pNewBtn->Unload();
    m_pExitBtn->Unload();
	m_State = CSTATE_INACTIVE;
}


// Control vector change event handler.
bool CStartMenuScreenController::OnVectorChanged (const Vec3& _vVec)
{
    return false;
}


// Touch event handler.
bool CStartMenuScreenController::OnTouch (const Vec2& _vPos, IOGTouchParam _param)
{
	if (m_State == CSTATE_ACTIVE)
	{
        bool bNewBtn = m_pNewBtn->OnTouch(_vPos, _param);
        bool bExitBtn = m_pExitBtn->OnTouch(_vPos, _param);
        
        if (_param == OG_TOUCH_UP && bNewBtn)
        {
    		Deactivate();
            return true;
        }
        
        if (_param == OG_TOUCH_UP && bExitBtn)
        {
    		Deactivate();
            m_State = CSTATE_FAILED;
            return true;
        }
	}
    return false;
}
