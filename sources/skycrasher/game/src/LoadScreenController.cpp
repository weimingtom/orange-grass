/*
 *  LoadScreenController.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "LoadScreenController.h"
#include "Game.h"
#include <stdio.h>


CLoadScreenController::CLoadScreenController() :	m_State(CSTATE_NO),
                                                    m_Type(SCRTYPE_LOAD),
													m_pLoadSpr(NULL),
                                                    m_pCurLevel(NULL),
													m_bLoaded(false),
                                                    m_bDisplayed(false)
{
	m_pGlobalVars = GetGlobalVars();
	m_pResourceMgr = GetResourceMgr();
    m_pRenderer = GetRenderer();
	m_pReader = GetSettingsReader();
}


CLoadScreenController::~CLoadScreenController()
{	
	m_State = CSTATE_NO;
	m_bLoaded = false;
}


// Initialize controller
bool CLoadScreenController::Init ()
{
	m_ScrWidth = m_pGlobalVars->GetIVar("view_width");
	m_ScrHeight = m_pGlobalVars->GetIVar("view_height");
	
	IOGSettingsSource* pSource = m_pReader->OpenSource(GetResourceMgr()->GetUIPath("LoadScreenUI.xml"));
	if (!pSource)
		return false;

	IOGGroupNode* pRoot = m_pReader->OpenGroupNode(pSource, NULL, "LoadScreen");
	IOGGroupNode* pLoadSprNode = m_pReader->OpenGroupNode(pSource, pRoot, "LoadSpr");
	if (pLoadSprNode != NULL)
	{
		m_LoadSprStr = m_pReader->ReadStringParam(pLoadSprNode, "sprite");
		m_LoadSprPos = m_pReader->ReadVec2Param(pLoadSprNode, "x", "y");
		m_LoadSprSize = m_pReader->ReadVec2Param(pLoadSprNode, "width", "height");
		m_pReader->CloseGroupNode(pLoadSprNode);
	}

	IOGGroupNode* pLabelNode = m_pReader->OpenGroupNode(pSource, pRoot, "LoadLabel");
	if (pLabelNode != NULL)
	{
		m_LoadLabelPos = m_pReader->ReadVec2Param(pLabelNode, "x", "y");
		m_pReader->CloseGroupNode(pLabelNode);
	}

	m_pReader->CloseGroupNode(pRoot);
	m_pReader->CloseSource(pSource);

	return true;
}


// Update controller
void CLoadScreenController::Update (unsigned long _ElapsedTime)
{
	if (!m_bLoaded && m_State == CSTATE_ACTIVE && m_bDisplayed)
	{
		OG_LOG_INFO("Loading started");
		GetActorParamsMgr()->Init();
		OG_LOG_INFO("Actor params manager initialized");
        GetLevelManager()->Init();
		OG_LOG_INFO("Level manager initialized");
		GetResourceMgr()->Load(OG_RESPOOL_GAME);
		OG_LOG_INFO("Resource managers loaded");

		IOGLevelParams* pLevelParams = GetGameSequence()->GetLevel(0);

		m_pCurLevel = GetLevelManager()->LoadLevel(pLevelParams->alias);
		if (m_pCurLevel == NULL)
		{
			OG_LOG_ERROR("Failed to load level %s", pLevelParams->alias.c_str());
            Deactivate();
			m_State = CSTATE_FAILED;
			return;
		}
		OG_LOG_INFO("Current level loading finished");

		OGVec3 vCraftPos = m_pCurLevel->GetStartPosition();
		vCraftPos.y = 80.0f;
		IOGActor* pPlayerActor = GetActorManager()->CreateActor(
			std::string(pLevelParams->player_actor),
			vCraftPos, 
			OGVec3(0,0,0), 
			OGVec3(1,1,1));
		pPlayerActor->SetWeapon(GetActorParamsMgr()->GetWeaponParams(pLevelParams->weapon));
		GetActorManager()->AddActor(pPlayerActor);

		OG_LOG_INFO("Player actor added");

		m_bLoaded = true;
		Deactivate();
	}
}


// Render controller scene
void CLoadScreenController::RenderScene ()
{
    m_pRenderer->SetClearColor(OGVec4(0.0f, 0.0f, 0.0f, 1.0f));
    m_pRenderer->DisplayString(m_LoadLabelPos, 0.5f, 0xFFFFFFFF, "Loading...");
    m_pRenderer->DrawScene();

    m_bDisplayed = true;
}


// Activate
void CLoadScreenController::Activate ()
{
	if (!m_LoadSprStr.empty())
	{
		m_pLoadSpr = m_pResourceMgr->GetSprite(OG_RESPOOL_UI, m_LoadSprStr);
	}
    m_bLoaded = false;
    m_bDisplayed = false;
	m_State = CSTATE_ACTIVE;
}


// deactivate
void CLoadScreenController::Deactivate ()
{
	if (m_pLoadSpr)
	{
		m_pResourceMgr->ReleaseSprite(m_pLoadSpr);
	}
	OG_LOG_INFO("Loading screen deactivated");
    m_bDisplayed = false;
	m_State = CSTATE_INACTIVE;
}
