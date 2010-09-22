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
#include "UI.h"

CDisplayText * AppDisplayText;
//IOGEffect*	g_pEffect = NULL;

CGameScreenController::CGameScreenController() :	m_pResourceMgr(NULL),
													m_pSg(NULL),
													m_pRenderer(NULL),
													m_pCamera(NULL),
                                                    m_pPlayer(NULL),
													m_State(CSTATE_NO),
                                                    m_Type(SCRTYPE_GAME),
													m_pCurLevel(NULL),
													m_fFOV(1.0f),
													m_fCameraTargetDistance(150.0f),
													m_fCameraFwdSpeed(0.02f),
													m_fCameraStrafeSpeed(0.02f),
													m_ElapsedTime(0)
{
}


CGameScreenController::~CGameScreenController()
{
	AppDisplayText->ReleaseTextures();
	free(AppDisplayText);

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
	m_pResourceMgr = GetResourceMgr();
	m_pSg = GetSceneGraph();
	m_pRenderer = GetRenderer();
	m_pCamera = m_pRenderer->GetCamera();
	m_pRenderer->SetViewport(SCR_WIDTH, SCR_HEIGHT, 4.0f, 200.0f, 0.67f);

	AppDisplayText = (CDisplayText*)malloc(sizeof(CDisplayText));    
	memset(AppDisplayText, 0, sizeof(CDisplayText));
#ifdef WIN32
 	AppDisplayText->SetTextures(SCR_WIDTH, SCR_HEIGHT, false);
#else
 	AppDisplayText->SetTextures(SCR_HEIGHT, SCR_WIDTH, true);
#endif
    
	m_fFOV = 0.67f;
	m_fCameraTargetDistance = 60.0f;
	m_fCameraFwdSpeed = 0.0f;//0.02f;
	m_fCameraStrafeSpeed = 0.01f;
	m_fFinishPointSqDistance = 10000.0f;
	m_ElapsedTime = 0;

	GetPhysics()->SetCameraFwdSpeed(m_fCameraFwdSpeed);
	GetPhysics()->SetCameraStrafeSpeed(m_fCameraStrafeSpeed);

    m_pCurLevel = GetLevelManager()->LoadLevel(std::string("level_0"));
    m_pPlayer = GetActorManager()->GetPlayersActor();

	//g_pEffect = GetEffectsManager()->CreateEffect(OG_EFFECT_PLASMA);

	UpdateCamera();
	GetPhysics()->UpdateAll(1);

    IOGActor* pMissile = GetActorManager()->CreateActor(OG_ACTOR_PLASMAMISSILE, 
        std::string("plasma01"), 
        m_pPlayer->GetPhysicalObject()->GetPosition()+Vec3(0,0,-20),
        Vec3(0,0,0),
        Vec3(1,1,1));
    GetActorManager()->AddActor(pMissile);

    return true;
}


// Update controller
void CGameScreenController::Update (unsigned long _ElapsedTime)
{
	m_ElapsedTime = _ElapsedTime;
	if (m_State != CSTATE_ACTIVE)
		return;
    
	UpdateCamera();
	//g_pEffect->SetPosition(m_pPlayer->GetPhysicalObject()->GetPosition()+Vec3(0,0,-20));

    GetPhysics()->Update(_ElapsedTime);
    GetActorManager()->Update(_ElapsedTime);
	//GetEffectsManager()->Update(_ElapsedTime);
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
	//GetEffectsManager()->Render(m_pCamera->GetViewMatrix());
	m_pRenderer->FinishRenderMode();
	m_pRenderer->GetFog()->Enable(false);

	m_pRenderer->Reset();

	glAlphaFunc(GL_GREATER, 0.1f);
	unsigned long fps = 0;
	if (m_ElapsedTime > 0)
	{
		fps = 1000/m_ElapsedTime;
	}
	AppDisplayText->DisplayText(70,4,0.4f, 0xFFFFFFFF, "FPS %d", fps);
#ifdef STATISTICS
	unsigned long Verts; 
	unsigned long Faces;
	unsigned long TextureSwitches;
	unsigned long VBOSwitches;
	unsigned long DrawCalls;
	GetStatistics()->GetStatistics(Verts, Faces, TextureSwitches, 
		VBOSwitches, DrawCalls);
	AppDisplayText->DisplayText(70, 8,0.4f, 0x7FFFFFFF, "Vertices: %d", Verts);
	AppDisplayText->DisplayText(70,12,0.4f, 0x7FFFFFFF, "Faces: %d", Faces);
	AppDisplayText->DisplayText(70,16,0.4f, 0x7FFFFFFF, "Textures: %d", TextureSwitches);
	AppDisplayText->DisplayText(70,20,0.4f, 0x7FFFFFFF, "VBO: %d", VBOSwitches);
	AppDisplayText->DisplayText(70,24,0.4f, 0x7FFFFFFF, "DP: %d", DrawCalls);
	GetStatistics()->Reset();
#endif
	AppDisplayText->Flush();
}


// Activate
void CGameScreenController::Activate ()
{
	m_State = CSTATE_ACTIVE;
    GetInput()->RegisterReceiver(this);
	
	//g_pEffect->Start();
	//g_pEffect->SetDirection(Vec3(0,0,1));
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


// Check if finish condition is satisfied.
bool CGameScreenController::CheckFinishCondition ()
{
	const Vec3& vFinishPoint = m_pCurLevel->GetFinishPosition();
	const Vec3& vCurPoint = m_pCamera->GetPosition();
	if (Dist2DSq(vCurPoint, vFinishPoint) <= m_fFinishPointSqDistance)
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
        const Vec3& vTarget = m_pPlayer->GetPhysicalObject()->GetPosition()+Vec3(0,0,-15);
        Vec3 vDir  = Vec3(0, 0.6f, 0.4f).normalized();
        Vec3 vUp = vDir.cross (Vec3(1, 0, 0));
        Vec3 vPos = vTarget + (vDir*m_fCameraTargetDistance);

        m_pCamera->Setup (vPos, vTarget, vUp);
		m_pCamera->Update();
	}
}
