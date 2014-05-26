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
#include "GameScreenController.h"
#include "Game.h"


CGameScreenController::CGameScreenController() 
    : m_pGlobalVars(NULL)
    , m_pResourceMgr(NULL)
    , m_pSg(NULL)
    , m_pRenderer(NULL)
    , m_pCamera(NULL)
    , m_pPlayer(NULL)
    , m_State(CSTATE_NO)
    , m_Type(SCRTYPE_GAME)
    , m_pCurLevel(NULL)
    , m_ElapsedTime(0)
    , m_bFinishLine(false)
{
    GetInput()->RegisterReceiver(this);
}


CGameScreenController::~CGameScreenController()
{
    m_pResourceMgr = NULL;
    m_pSg = NULL;
    m_pRenderer = NULL;
    m_pCamera = NULL;
    m_pPlayer = NULL;

    m_pLifeHUD = NULL;
    m_pSpecHUD = NULL;
    m_pWeaponHUD = NULL;

    m_State = CSTATE_NO;
    m_pCurLevel = NULL;
}


// Initialize controller
bool CGameScreenController::Init ()
{
    m_pGlobalVars = GetGlobalVars();

    m_ScrWidth = m_pGlobalVars->GetIVar("view_width");
    m_ScrHeight = m_pGlobalVars->GetIVar("view_height");
    m_fCameraTargetDistance = m_pGlobalVars->GetFVar("cam_distance");
    m_fCameraMargins = m_pGlobalVars->GetFVar("cam_margins");
    m_vCameraDir = m_pGlobalVars->GetVec3Var("cam_dir");
    m_vCameraOffset = m_pGlobalVars->GetVec3Var("cam_offset");

    m_ElapsedTime = 0;
    m_bFinishLine = false;

    m_pResourceMgr = GetResourceMgr();
    m_pSg = GetSceneGraph();
    m_pRenderer = GetRenderer();
    m_pReader = GetSettingsReader();
    m_pCamera = m_pRenderer->GetCamera();

    IOGLevelParams* pLevelParams = GetGameSequence()->GetLevel(0);
    m_pCurLevel = GetLevelManager()->LoadLevel(pLevelParams->alias);
    m_pPlayer = GetActorManager()->GetPlayersActor();
    m_pPlayer->SetGameEventHandler(this);

    IOGSettingsSource* pSource = m_pReader->OpenSource(m_pResourceMgr->GetUIPath("GameScreenUI.xml"));
    if (!pSource)
        return false;

    IOGGroupNode* pRoot = m_pReader->OpenGroupNode(pSource, NULL, "GameScreen");

    m_pReader->CloseGroupNode(pRoot);
    m_pReader->CloseSource(pSource);

    UpdateCamera();
    GetPhysics()->UpdateAll(1);
    m_pRenderer->EnableFog(true);

    return true;
}


// Update controller
void CGameScreenController::Update (unsigned long _ElapsedTime)
{
    m_ElapsedTime = _ElapsedTime;
    if (m_State != CSTATE_ACTIVE)
    {
        OG_LOG_INFO("Game screen update - inactive state");
        return;
    }

    UpdateCamera();

    GetPhysics()->Update(_ElapsedTime);
    GetActorManager()->Update(_ElapsedTime);
    m_pSg->Update(_ElapsedTime);
}


// Render controller scene
void CGameScreenController::RenderScene ()
{
    if (m_State != CSTATE_ACTIVE)
    {
        OG_LOG_INFO("Game screen render - inactive state");
        return;
    }

    //m_pSg->RenderLandscape(m_pCamera);
    m_pSg->RenderScene(m_pCamera);
    //m_pSg->RenderEffects(m_pCamera);
    m_pRenderer->DrawScene();
}


// Activate
void CGameScreenController::Activate ()
{
    m_State = CSTATE_ACTIVE;
    GetInput()->RegisterReceiver(this);
    m_bFinishLine = false;
    OG_LOG_INFO("Game screen activated.");
}


// deactivate
void CGameScreenController::Deactivate ()
{
    m_State = CSTATE_INACTIVE;
    if (m_pCurLevel)
        GetLevelManager()->UnloadLevel();
    m_pPlayer = NULL;
    OG_LOG_INFO("Game screen deactivated.");
}


// Control vector change event handler.
bool CGameScreenController::OnVectorChanged (const OGVec3& _vVec)
{
    if (m_State != CSTATE_ACTIVE)
    {
        return false;
    }

    return false;
}


// Touch event handler.
bool CGameScreenController::OnTouch (const OGVec2& _vPos, IOGTouchParam _param)
{
    if (m_State != CSTATE_ACTIVE)
    {
        return false;
    }
    return false;
}


// Level finish point handler
void CGameScreenController::OnReachedFinishPoint ()
{
    m_bFinishLine = true;
}


// Level finish handler
void CGameScreenController::OnLevelFinish ()
{
    Deactivate();
}


// Update camera.
void CGameScreenController::UpdateCamera ()
{
    if (m_pCamera && m_pCurLevel && !m_bFinishLine)
    {
        OGVec3 vTarget = m_pPlayer->GetPhysicalObject()->GetPosition() + m_vCameraOffset;
        OGVec3 vUp = m_vCameraDir.cross(OGVec3(1, 0, 0));
        OGVec3 vPos = vTarget + (m_vCameraDir * m_fCameraTargetDistance);

        OGVec3 vLeftBorder, vRightBorder;
        GetPhysics()->GetBordersAtPoint(vPos, vLeftBorder, vRightBorder);
        float fLeft = vLeftBorder.x + m_fCameraMargins;
        float fRight = vRightBorder.x - m_fCameraMargins;
        OG_CLAMP(vPos.x, fLeft, fRight);
        OG_CLAMP(vTarget.x, fLeft, fRight);

        m_pCamera->Setup (vPos, vTarget, vUp);
        m_pCamera->Update();
        m_pRenderer->GetLightMgr()->UpdateGlobalLight(m_pCamera);
    }
    else if (m_bFinishLine)
    {
        m_pCamera->Update();
        m_pRenderer->GetLightMgr()->UpdateGlobalLight(m_pCamera);
    }
}
