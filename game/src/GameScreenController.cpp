/*
 *  GameScreenController.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "GameScreenController.h"
#include "OrangeGrass.h"


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
	GetInput()->RegisterReceiver(this);
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
    
	IOGLevelParams* pLevelParams = GetGameSequence()->GetLevel(0);
	m_pCurLevel = GetLevelManager()->LoadLevel(pLevelParams->alias);
    m_pPlayer = GetActorManager()->GetPlayersActor();

	m_pHUD = m_pResourceMgr->GetSprite("hud");
	m_pWeaponIcon = m_pResourceMgr->GetSprite(m_pPlayer->GetWeapon()->GetParams()->icon_texture);

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

	m_pRenderer->EnableFog(true);

	m_pRenderer->StartRenderMode(OG_RENDERMODE_GEOMETRY);
	m_pSg->RenderLandscape(m_pCamera);
	m_pSg->RenderScene(m_pCamera);
	m_pRenderer->FinishRenderMode();

    m_pRenderer->StartRenderMode(OG_RENDERMODE_EFFECTS);
    m_pSg->RenderEffects(m_pCamera);
    m_pRenderer->FinishRenderMode();

    m_pRenderer->Reset();

	m_pRenderer->StartRenderMode(OG_RENDERMODE_GEOMETRY);
    m_pSg->RenderTransparentNodes(m_pCamera);
	m_pRenderer->FinishRenderMode();

    m_pRenderer->EnableFog(false);

    m_pRenderer->StartRenderMode(OG_RENDERMODE_SPRITES);
	m_pHUD->Render(Vec2(365, 231), Vec2(115.0f, 89.0f));
	m_pWeaponIcon->Render(Vec2(398, 243), Vec2(64.0f, 64.0f));
	m_pRenderer->FinishRenderMode();
/*
	unsigned long fps = 0;
	if (m_ElapsedTime > 0)
	{
		fps = 1000/m_ElapsedTime;
	}
	m_pRenderer->StartRenderMode(OG_RENDERMODE_TEXT);
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
*/
    GetStatistics()->Reset();
/*    
#endif
	m_pRenderer->FinishRenderMode();
*/
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
	if (m_pCurLevel)
		GetLevelManager()->UnloadLevel(m_pCurLevel);
    //GetInput()->UnregisterReceiver(this);
}


// Control vector change event handler.
bool CGameScreenController::OnVectorChanged (const Vec3& _vVec)
{
    return false;
}


// Touch event handler.
bool CGameScreenController::OnTouch (const Vec2& _vPos, IOGTouchParam _param)
{
	Vec2 vPos = Vec2(365, 231);
	Vec2 vSize = Vec2(115.0f, 89.0f);
    if (_vPos.x >= vPos.x && 
        _vPos.y >= vPos.y &&
        _vPos.x <= vPos.x + vSize.x && 
        _vPos.y <= vPos.y + vSize.y)
	{
		IOGWeapon* pWeapon = m_pPlayer->GetWeapon();
		if (pWeapon && pWeapon->IsReady())
		{
			pWeapon->Fire(Vec3(0,0,0));
		}
		return true;
	}
    return false;
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
