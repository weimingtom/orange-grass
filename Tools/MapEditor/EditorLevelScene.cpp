/*
 *  EditorLevelScene.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenGL2.h"
#include "EditorLevelScene.h"
#include "OrangeGrass.h"
#include "common.h"


CEditorLevelScene::CEditorLevelScene()
{
	m_pCurLevel = NULL;
	m_pCurActor = NULL;
	m_pPickedActor = NULL;
	m_bIntersectionFound = false;
	m_vCurScaling = Vec3(1,1,1);
	m_CurActorType = OG_ACTOR_NONE;
	m_fAirBotHeight = 80.0f;
}


CEditorLevelScene::~CEditorLevelScene()
{
    OG_SAFE_DELETE(m_pCurActor);
}


// Initialize scene
bool CEditorLevelScene::Init ()
{
	glewInit();

	m_pResourceMgr = GetResourceMgr();
	m_pSg = GetSceneGraph();
	m_pRenderer = GetRenderer();
	m_pCamera = m_pRenderer->GetCamera();

    Vec3 vTarget (200, 0, -100);
	Vec3 vDir (0, 1.0f, 0.4f);
	vDir = vDir.normalize();
	Vec3 vUp = vDir.cross (Vec3(1, 0, 0));
	GetRenderer()->GetCamera()->Setup (vTarget + (vDir* m_fCameraDistance), vTarget, vUp);

	glDisable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);

	if (GetResourceMgr()->Init() == false)
	{
		return false;
	}
	if (GetLevelManager()->Init() == false)
	{
		return false;
	}

	return true;
}


// Setup viewport
void CEditorLevelScene::SetViewport (int _Width, int _Height)
{
	m_ResX = _Width;
	m_ResY = _Height;

	glViewport(0, 0, m_ResX, m_ResY);
	m_pRenderer->SetViewport(m_ResX, m_ResY, 4.0f, 4500.0f, 0.67f);
}


// Update controller
void CEditorLevelScene::Update (unsigned long _ElapsedTime)
{
}


// Render controller scene
void CEditorLevelScene::RenderScene ()
{
}


// Load level
bool CEditorLevelScene::LoadLevel (const std::string& _LevelName)
{
	if (m_pCurLevel)
	{
		GetLevelManager()->UnloadLevel(m_pCurLevel);
	}
	
	m_pCurLevel = GetLevelManager()->LoadLevel(_LevelName);
	if (m_pCurLevel == NULL)
	{
		return false;
	}
	
	IOGActor* pPlayerActor = GetActorManager()->GetPlayersActor();
	Vec3 vCraftPos = m_pCurLevel->GetStartPosition();
	vCraftPos.y = m_fAirBotHeight;
	if (!pPlayerActor)
	{
		pPlayerActor = GetActorManager()->CreateActor(
            OG_ACTOR_PLAYER, 
			std::string("craft"),
			vCraftPos, 
            Vec3(0,0,0), 
            Vec3(1,1,1));
		GetActorManager()->AddActor(pPlayerActor);
	}
	else
	{
		pPlayerActor->GetPhysicalObject()->SetPosition(vCraftPos);
	}

	return true;
}


// Set editor mode
void CEditorLevelScene::SetEditMode (TerrainEditMode _Mode)
{
}
