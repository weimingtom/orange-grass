/*
 *  EffectViewerScene.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenGL2.h"
#include "EffectViewerScene.h"
#include "OrangeGrass.h"
#include <IOGGraphicsHelpers.h>
#include "IOGMath.h"


CEffectViewerScene::CEffectViewerScene()
{
	m_pCurEffect = NULL;
	m_pCurNode = NULL;
	m_pCurPhysics = NULL;

	m_fCameraDistance = 200.0f;
	m_bShowAABB = false;
	m_bShowGrid = true;
    m_bInited = false;
	m_ResX = m_ResY = 0;

	m_fFineAngleStep = TO_RADIAN(2.0f);
    m_fCoarseAngleStep = TO_RADIAN(45.0f);
}


CEffectViewerScene::~CEffectViewerScene()
{
	SetupEffect(NULL);
}


// Initialize scene
bool CEffectViewerScene::Init ()
{
    if (m_bInited)
        return true;

	glewInit();

	m_pRenderer = GetRendererGL11();
	m_pRenderer->SetViewport(m_ResX, m_ResY, 4.0f, 4500.0f, 0.67f);

	m_pResourceMgr = GetResourceMgr();
	m_pSg = GetSceneGraph();
	m_pCamera = m_pRenderer->GetCamera();
	m_pActorMgr = GetActorManager();

    Vec3 vTarget (0, 0, 0);
	Vec3 vDir (0, 1.0f, 0.4f);
	vDir = vDir.normalize();
	Vec3 vUp = vDir.cross (Vec3(1, 0, 0));
	m_pCamera->Setup (vTarget + (vDir*m_fCameraDistance), vTarget, vUp);

	m_fHorViewAngle = m_fVerViewAngle = 0.0f;
	m_vCamUp = vUp;
	m_vCamPos = m_pCamera->GetPosition();

	Vec3 vLightDir = Vec3(0,1,0);
	Vec4 vLightColor = Vec4(1,1,1,1);
	IOGLight* pMainLight = m_pRenderer->GetLightMgr()->CreateLight();
	pMainLight->type = OG_LIGHT_DIRECTIONAL;
	pMainLight->vPosition = vLightDir;
	pMainLight->fIntensity = 100.0f;
	pMainLight->vAmbientColor = Vec4(vLightColor.x, vLightColor.y, vLightColor.z, 1.0f);
	pMainLight->vDiffuseColor = Vec4(vLightColor.x, vLightColor.y, vLightColor.z, 1.0f);
	pMainLight->vSpecularColor = Vec4(vLightColor.x, vLightColor.y, vLightColor.z, 1.0f);

	glDisable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);

	if (m_pResourceMgr->Init() == false)
	{
		return false;
	}

	if (m_pResourceMgr->Load() == false)
	{
        return false;
	}

	if (GetActorParamsMgr()->Init() == false)
	{
        return false;
	}

	const std::map<std::string, OGEffectType>& effects = GetEffectsManager()->GetEffectsList();
	std::map<std::string, OGEffectType>::const_iterator iter = effects.begin();
	for (; iter != effects.end(); ++iter)
	{
		CommonToolEvent<ResLoadEventData> cmd(EVENTID_RESLOAD);
		cmd.SetEventCustomData(ResLoadEventData(wxT(iter->first.c_str()), 
			wxT("Effects"),
			wxT("")));
		GetEventHandlersTable()->FireEvent(EVENTID_RESLOAD, &cmd);
	}

	SetupEffect(NULL);
    m_bInited = true;

	return true;
}


// Setup viewport
void CEffectViewerScene::SetViewport (int _Width, int _Height)
{
	m_ResX = _Width;
	m_ResY = _Height;

	glViewport(0, 0, m_ResX, m_ResY);
	if (m_bInited)
	{
		m_pRenderer->SetViewport(m_ResX, m_ResY, 4.0f, 4500.0f, 0.67f);
	}
}


// Update controller
void CEffectViewerScene::Update (unsigned long _ElapsedTime)
{
	GetPhysics()->UpdateAll(33);
    m_pSg->Update(33);
	m_pCamera->Update();
	m_mView = m_pCamera->GetViewMatrix();

	if (m_pCurEffect)
	{
		if (m_pCurEffect->GetStatus() == OG_EFFECTSTATUS_INACTIVE)
		{
			m_pCurEffect->Start();
		}
	}
}


// Render controller scene
void CEffectViewerScene::RenderScene ()
{
	m_pRenderer->ClearFrame(Vec4(0.3f, 0.3f, 0.4f, 1.0f));

	RenderHelpers();

	m_pRenderer->EnableLight(false);
    m_pRenderer->StartRenderMode(OG_RENDERMODE_EFFECTS);
    m_pSg->RenderAllEffects(m_pCamera);
	m_pRenderer->FinishRenderMode();

	m_pRenderer->StartRenderMode(OG_RENDERMODE_TEXT);
	unsigned long Verts; 
	unsigned long Faces;
	unsigned long TextureSwitches;
	unsigned long VBOSwitches;
	unsigned long DrawCalls;
	GetStatistics()->GetStatistics(Verts, Faces, TextureSwitches, 
		VBOSwitches, DrawCalls);
	m_pRenderer->DisplayString(Vec2(85.0f, 2.0f), 0.4f, 0x7FFFFFFF, "Vertices: %d", Verts);
	m_pRenderer->DisplayString(Vec2(85.0f, 6.0f), 0.4f, 0x7FFFFFFF, "Faces: %d", Faces);
	m_pRenderer->DisplayString(Vec2(85.0f,10.0f), 0.4f, 0x7FFFFFFF, "Textures: %d", TextureSwitches);
	m_pRenderer->DisplayString(Vec2(85.0f,14.0f), 0.4f, 0x7FFFFFFF, "VBO: %d", VBOSwitches);
	m_pRenderer->DisplayString(Vec2(85.0f,18.0f), 0.4f, 0x7FFFFFFF, "DP: %d", DrawCalls);
	GetStatistics()->Reset();
	m_pRenderer->FinishRenderMode();

	m_pRenderer->Reset();

	glFlush();
}


// Render scene helpers.
void CEffectViewerScene::RenderHelpers()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m_mView.f);
    glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	if (m_bShowAABB)
	{
        if (m_pCurNode)
        {
			DrawOBB(m_pCurNode->GetOBB());
        }
	}

	if (m_bShowGrid)
	{
		DrawCoordGrid(50, 2, 10);
	}

    glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
}


// Setup effect.
void CEffectViewerScene::SetupEffect(const char* _pEffectAlias)
{
    if (m_pCurEffect)
    {
		m_pSg->RemoveNode(m_pCurNode);
		GetPhysics()->RemoveObject(m_pCurPhysics);
		m_pCurPhysics = NULL;
		OG_SAFE_DELETE(m_pCurNode);
		OG_SAFE_DELETE(m_pCurEffect);
    }

	if (_pEffectAlias != NULL)
	{
		m_pCurEffect = GetEffectsManager()->CreateEffect(_pEffectAlias);

	    m_pCurPhysics = GetPhysics()->CreateObject(&m_PhysicalParams, m_pCurEffect->GetAABB(), NULL);
		m_pCurPhysics->SetWorldTransform(Vec3(0,0,0), Vec3(0,0,0), Vec3(1,1,1));
		GetPhysics()->AddObject(m_pCurPhysics);

		m_pCurNode = m_pSg->CreateEffectNode(m_pCurEffect, m_pCurPhysics);
		m_pSg->AddEffectNode(m_pCurNode);
        m_pCurNode->Activate(true);
		m_pCurEffect->Start();
	}
}


// Camera zoom
void CEffectViewerScene::CameraZoom (float _fFactor)
{
	m_pCamera->Move (_fFactor);
}


// Camera move
void CEffectViewerScene::CameraMove (float _fX, float _fZ)
{
	m_pCamera->Strafe(5.5f, Vec3(_fX, 0, _fZ));
}


// Camera rotate
void CEffectViewerScene::CameraRotate (float _fAngleH, float _fAngleV)
{
}


// Camera rotate horizontally
void CEffectViewerScene::CameraRotateHor (float _fAngle)
{
	m_fHorViewAngle += _fAngle;
	Vec3 vTarget (0, 0, 0);

	MATRIX mR;
	MatrixRotationY(mR, m_fHorViewAngle);
	Vec3 vDir, vRight;
	MatrixVec3Multiply(vDir, Vec3(0.0f, 1.0f, 0.4f), mR);
	MatrixVec3Multiply(vRight, Vec3(1.0f, 0.0f, 0.0f), mR);
	vDir = vDir.normalize();
	Vec3 vUp = vDir.cross (vRight);
	m_pCamera->Setup (vTarget + (vDir*m_fCameraDistance), vTarget, vUp);
}


// Camera rotate vertically
void CEffectViewerScene::CameraRotateVer (float _fAngle)
{
	Vec3 vTarget (0, 0, 0);
	
	MATRIX mR;
	MatrixRotationX(mR, _fAngle);
	Vec3 vDir, vRight;
	MatrixVec3Multiply(vDir, m_pCamera->GetDirection(), mR);
	MatrixVec3Multiply(vRight, m_pCamera->GetRight(), mR);
	vDir.normalize();
	Vec3 vUp = vDir.cross (vRight);
	m_pCamera->Setup (vTarget + (vDir*m_fCameraDistance), vTarget, vUp);
}
