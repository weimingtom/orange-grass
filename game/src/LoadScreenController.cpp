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


CLoadScreenController::CLoadScreenController() :	m_State(CSTATE_NO),
                                                    m_Type(SCRTYPE_LOAD),
													m_pHUD(NULL),
                                                    m_pCurLevel(NULL),
													m_bLoaded(false),
                                                    m_bDisplayed(false)
{
	m_pGlobalVars = GetGlobalVars();
	m_pResourceMgr = GetResourceMgr();
    m_pRenderer = GetRenderer();
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
	
	return true;
}


// Update controller
void CLoadScreenController::Update (unsigned long _ElapsedTime)
{
	if (!m_bLoaded && m_State == CSTATE_ACTIVE && m_bDisplayed)
	{
		GetActorParamsMgr()->Init();
        GetLevelManager()->Init();

		IOGLevelParams* pLevelParams = GetGameSequence()->GetLevel(0);

		m_pCurLevel = GetLevelManager()->LoadLevel(pLevelParams->alias);
		if (m_pCurLevel == NULL)
		{
			OG_LOG_ERROR("Failed to load level %s", pLevelParams->alias.c_str());
            Deactivate();
			m_State = CSTATE_FAILED;
			return;
		}

		Vec3 vCraftPos = m_pCurLevel->GetStartPosition();
		vCraftPos.y = 80.0f;
		IOGActor* pPlayerActor = GetActorManager()->CreateActor(
			std::string(pLevelParams->player_actor),
			vCraftPos, 
			Vec3(0,0,0), 
			Vec3(1,1,1));
		pPlayerActor->SetWeapon(GetActorParamsMgr()->GetWeaponParams(pLevelParams->weapon));
		GetActorManager()->AddActor(pPlayerActor);

		m_bLoaded = true;
		Deactivate();
	}
}


// Render controller scene
void CLoadScreenController::RenderScene ()
{
	m_pRenderer->ClearFrame(Vec4(0.0f, 0.0f, 0.0f, 1.0f));

	m_pRenderer->StartRenderMode(OG_RENDERMODE_SPRITES);
	m_pHUD->Render(Vec2(0, 0), Vec2((float)m_ScrWidth, (float)m_ScrHeight));
	m_pRenderer->FinishRenderMode();
	m_pRenderer->Reset();

	m_bDisplayed = true;
}


// Activate
void CLoadScreenController::Activate ()
{
	m_pHUD = m_pResourceMgr->GetSprite("load_scr");
    m_bLoaded = false;
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
