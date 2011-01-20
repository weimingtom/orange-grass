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
	m_pReader = GetSettingsReader();

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
	if (!m_pResourceMgr->Load(OG_RESPOOL_UI))
		return false;

	GetInput()->RegisterReceiver(this);

	IOGSettingsSource* pSource = m_pReader->OpenSource(GetResourceMgr()->GetUIPath("StartMenuUI.xml"));
	if (!pSource)
		return false;

	IOGGroupNode* pRoot = m_pReader->OpenGroupNode(pSource, NULL, "StartMenu");
	IOGGroupNode* pLogoNode = m_pReader->OpenGroupNode(pSource, pRoot, "Logo");
	if (pLogoNode != NULL)
	{
		m_LogoSprStr = m_pReader->ReadStringParam(pLogoNode, "sprite");
		m_LogoSprPos = m_pReader->ReadVec2Param(pLogoNode, "x", "y");
		m_LogoSprSize = m_pReader->ReadVec2Param(pLogoNode, "width", "height");
		m_pReader->CloseGroupNode(pLogoNode);
	}

	IOGGroupNode* pBackNode = m_pReader->OpenGroupNode(pSource, pRoot, "Back");
	if (pBackNode != NULL)
	{
		m_BackSprStr = m_pReader->ReadStringParam(pBackNode, "sprite");
		m_BackSprPos = m_pReader->ReadVec2Param(pBackNode, "x", "y");
		m_BackSprSize = m_pReader->ReadVec2Param(pBackNode, "width", "height");
		m_pReader->CloseGroupNode(pBackNode);
	}

	IOGGroupNode* pLabelNode = m_pReader->OpenGroupNode(pSource, pRoot, "DemoLabel");
	if (pLabelNode != NULL)
	{
		m_DemoLabelPos = m_pReader->ReadVec2Param(pLabelNode, "x", "y");
		m_pReader->CloseGroupNode(pLabelNode);
	}

	IOGGroupNode* pNewBtnNode = m_pReader->OpenGroupNode(pSource, pRoot, "NewBtn");
	if (pNewBtnNode != NULL)
	{
		m_NewBtnNSprStr = m_pReader->ReadStringParam(pNewBtnNode, "sprite_n");
		m_NewBtnPrSprStr = m_pReader->ReadStringParam(pNewBtnNode, "sprite_pr");
		m_NewBtnPos = m_pReader->ReadVec2Param(pNewBtnNode, "x", "y");
		m_NewBtnSize = m_pReader->ReadVec2Param(pNewBtnNode, "width", "height");
		m_pReader->CloseGroupNode(pNewBtnNode);
	}

	IOGGroupNode* pExitBtnNode = m_pReader->OpenGroupNode(pSource, pRoot, "ExitBtn");
	if (pExitBtnNode != NULL)
	{
		m_ExitBtnNSprStr = m_pReader->ReadStringParam(pExitBtnNode, "sprite_n");
		m_ExitBtnPrSprStr = m_pReader->ReadStringParam(pExitBtnNode, "sprite_pr");
		m_ExitBtnPos = m_pReader->ReadVec2Param(pExitBtnNode, "x", "y");
		m_ExitBtnSize = m_pReader->ReadVec2Param(pExitBtnNode, "width", "height");
		m_pReader->CloseGroupNode(pExitBtnNode);
	}

	m_pReader->CloseGroupNode(pRoot);
	m_pReader->CloseSource(pSource);
	
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
	m_pBack->Render(m_BackSprPos, m_BackSprSize);
	m_pLogo->Render(m_LogoSprPos, m_LogoSprSize);
    m_pNewBtn->Render();
    m_pExitBtn->Render();
	m_pRenderer->FinishRenderMode();
	m_pRenderer->StartRenderMode(OG_RENDERMODE_TEXT);
    m_pRenderer->DisplayString(m_DemoLabelPos, 0.3f, 0x7FFFFFFF, "Demo version: %d.%d", 0, 16);
	m_pRenderer->FinishRenderMode();
	m_pRenderer->Reset();
}


// Activate
void CStartMenuScreenController::Activate ()
{
    m_pLogo = m_pResourceMgr->GetSprite(OG_RESPOOL_UI, m_LogoSprStr);
    m_pBack = m_pResourceMgr->GetSprite(OG_RESPOOL_UI, m_BackSprStr);
    m_pNewBtn->Load(m_NewBtnNSprStr, m_NewBtnPrSprStr, m_NewBtnSize);
    m_pNewBtn->SetPosition(m_NewBtnPos);
    m_pExitBtn->Load(m_ExitBtnNSprStr, m_ExitBtnPrSprStr, m_ExitBtnSize);
    m_pExitBtn->SetPosition(m_ExitBtnPos);
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
