/*
 *  GameScreenController.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenGL2.h"
#include "GameScreenController.h"
#include "OrangeGrass.h"
#include "common.h"


CGameScreenController::CGameScreenController() :	m_pGlobalVars(NULL),
													m_pResourceMgr(NULL),
													m_pSg(NULL),
													m_pRenderer(NULL),
													m_pCamera(NULL),
                                                    m_pPlayer(NULL),
													m_State(CSTATE_NO),
                                                    m_Type(SCRTYPE_GAME),
													m_pCurLevel(NULL),
													m_ElapsedTime(0)
{
}


CGameScreenController::~CGameScreenController()
{
	m_pResourceMgr = NULL;
	m_pSg = NULL;
	m_pRenderer = NULL;
	m_pCamera = NULL;
    m_pPlayer = NULL;

	m_State = CSTATE_NO;
	m_pCurLevel = NULL;
}


// Initialize controller
bool CGameScreenController::Init ()
{
	m_pGlobalVars = GetGlobalVars();

	m_CurLevel = m_pGlobalVars->GetSVar("level_0");
	m_fFOV = m_pGlobalVars->GetFVar("FOV");
	m_fZNear = m_pGlobalVars->GetFVar("z_near");
	m_fZFar = m_pGlobalVars->GetFVar("z_far");
	m_ScrWidth = m_pGlobalVars->GetIVar("view_width");
	m_ScrHeight = m_pGlobalVars->GetIVar("view_height");
	m_fCameraTargetDistance = m_pGlobalVars->GetFVar("cam_distance");
	m_fCameraMargins = m_pGlobalVars->GetFVar("cam_margins");
	m_vCameraDir = m_pGlobalVars->GetVec3Var("cam_dir");
	m_vCameraOffset = m_pGlobalVars->GetVec3Var("cam_offset");

	m_ElapsedTime = 0;

    m_pResourceMgr = GetResourceMgr();
	m_pSg = GetSceneGraph();
	m_pRenderer = GetRenderer();
	m_pCamera = m_pRenderer->GetCamera();
	m_pRenderer->SetViewport(m_ScrWidth, m_ScrHeight, m_fZNear, m_fZFar, m_fFOV);
    
    m_pCurLevel = GetLevelManager()->LoadLevel(m_CurLevel);
    m_pPlayer = GetActorManager()->GetPlayersActor();

	UpdateCamera();
	GetPhysics()->UpdateAll(1);

    return true;
}


// Update controller
void CGameScreenController::Update (unsigned long _ElapsedTime)
{
	m_ElapsedTime = _ElapsedTime;
	if (m_State != CSTATE_ACTIVE)
		return;
    
	UpdateCamera();

    GetPhysics()->Update(_ElapsedTime);
    GetActorManager()->Update(_ElapsedTime);
	m_pSg->Update(_ElapsedTime);

	if (CheckFinishCondition())
	{
		Deactivate();
	}
}


// Render controller scene
void CGameScreenController::RenderScene ()
{
	if (m_State != CSTATE_ACTIVE)
    {
		return;
    }

	m_pRenderer->ClearFrame(Vec4(0.3f, 0.3f, 0.4f, 1.0f));

	m_pRenderer->GetFog()->Enable(true);
	m_pRenderer->StartRenderMode(OG_RENDERMODE_GEOMETRY);
	m_pSg->RenderLandscape(m_pCamera);
	m_pSg->RenderScene(m_pCamera);
	m_pRenderer->FinishRenderMode();

	m_pRenderer->StartRenderMode(OG_RENDERMODE_EFFECTS);
    m_pSg->RenderEffects(m_pCamera);
	m_pRenderer->FinishRenderMode();
	m_pRenderer->GetFog()->Enable(false);

	unsigned long fps = 0;
	if (m_ElapsedTime > 0)
	{
		fps = 1000/m_ElapsedTime;
	}
	m_pRenderer->StartRenderMode(OG_RENDERMODE_SPRITES);
	m_pRenderer->DisplayString(Vec2(70.0f,4.0f), 0.4f, 0xFFFFFFFF, "FPS %d", fps);
#ifdef STATISTICS
	unsigned long Verts; 
	unsigned long Faces;
	unsigned long TextureSwitches;
	unsigned long VBOSwitches;
	unsigned long DrawCalls;
	GetStatistics()->GetStatistics(Verts, Faces, TextureSwitches, 
		VBOSwitches, DrawCalls);
	m_pRenderer->DisplayString(Vec2(70.0f, 8.0f), 0.4f, 0x7FFFFFFF, "Vertices: %d", Verts);
	m_pRenderer->DisplayString(Vec2(70.0f,12.0f), 0.4f, 0x7FFFFFFF, "Faces: %d", Faces);
	m_pRenderer->DisplayString(Vec2(70.0f,16.0f), 0.4f, 0x7FFFFFFF, "Textures: %d", TextureSwitches);
	m_pRenderer->DisplayString(Vec2(70.0f,20.0f), 0.4f, 0x7FFFFFFF, "VBO: %d", VBOSwitches);
	m_pRenderer->DisplayString(Vec2(70.0f,24.0f), 0.4f, 0x7FFFFFFF, "DP: %d", DrawCalls);
	GetStatistics()->Reset();
#endif
	m_pRenderer->FinishRenderMode();

	m_pRenderer->Reset();
}


// Activate
void CGameScreenController::Activate ()
{
	m_State = CSTATE_ACTIVE;
    GetInput()->RegisterReceiver(this);
}


// deactivate
void CGameScreenController::Deactivate ()
{
	m_State = CSTATE_INACTIVE;
    GetInput()->UnregisterReceiver(this);
}


// Control vector change event handler.
void CGameScreenController::OnVectorChanged (const Vec3& _vVec)
{
}


// Touch event handler.
void CGameScreenController::OnTouch (const Vec2& _vPos)
{
}


// Check if finish condition is satisfied.
bool CGameScreenController::CheckFinishCondition ()
{
	const Vec3& vFinishPoint = m_pCurLevel->GetFinishPosition();
	const Vec3& vCurPoint = m_pCamera->GetPosition();
	if (Dist2DSq(vCurPoint, vFinishPoint) <= 10000.0f)
	{
		return true;
	}
	return false;
}


// Update camera.
void CGameScreenController::UpdateCamera ()
{
    if (m_pCamera && m_pCurLevel)
    {
        Vec3 vTarget = m_pPlayer->GetPhysicalObject()->GetPosition() + m_vCameraOffset;
        Vec3 vUp = m_vCameraDir.cross(Vec3(1, 0, 0));
        Vec3 vPos = vTarget + (m_vCameraDir * m_fCameraTargetDistance);

        Vec3 vLeftBorder, vRightBorder;
        GetPhysics()->GetBordersAtPoint(vPos, vLeftBorder, vRightBorder);
        float fLeft = vLeftBorder.x + m_fCameraMargins;
        float fRight = vRightBorder.x - m_fCameraMargins;
        OG_CLAMP(vPos.x, fLeft, fRight);
        OG_CLAMP(vTarget.x, fLeft, fRight);

        m_pCamera->Setup (vPos, vTarget, vUp);
		m_pCamera->Update();
	}
}
