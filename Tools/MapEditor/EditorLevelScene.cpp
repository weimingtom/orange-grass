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
#include <IOGGraphicsHelpers.h>


CEditorLevelScene::CEditorLevelScene()
{
	m_pCurLevel = NULL;
	m_pCurActor = NULL;
	m_pPickedActor = NULL;
	m_vCurScaling = Vec3(1,1,1);
	m_CurActorType = OG_ACTOR_NONE;
	m_fAirBotHeight = 80.0f;
	m_fCameraDistance = 400.0f;
	m_bShowAABB = false;
    m_bInited = false;
}


CEditorLevelScene::~CEditorLevelScene()
{
    OG_SAFE_DELETE(m_pCurActor);
}


// Initialize scene
bool CEditorLevelScene::Init ()
{
    if (m_bInited)
        return true;

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

	std::vector<IOGResourceInfo> resInfo;
	if (m_pResourceMgr->Load(resInfo))
	{
		std::vector<IOGResourceInfo>::const_iterator iter = resInfo.begin();
		for (; iter != resInfo.end(); ++iter)
		{
			CommonToolEvent<ResLoadEventData> cmd(EVENTID_RESLOAD);
			cmd.SetEventCustomData(ResLoadEventData(wxT((*iter).m_Resource), 
				wxT((*iter).m_ResourceGroup), 
				wxT((*iter).m_ResourceIcon),
				wxT((*iter).m_ResourceActorType)));
			GetEventHandlersTable()->FireEvent(EVENTID_RESLOAD, &cmd);
		}
	}
	else
	{
        return false;
	}

	SetNewCurrentNodeForPlacement(NULL, OG_ACTOR_NONE);
    m_bInited = true;

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
	GetPhysics()->UpdateAll(0);
    GetActorManager()->Update(10);
	m_pCamera->Update();
	m_mView = m_pCamera->GetViewMatrix();

    if (m_pCurActor)
    {
        m_pCurActor->GetPhysicalObject()->Update(10);
        m_pCurActor->Update(10);
    }
}


// Render controller scene
void CEditorLevelScene::RenderScene ()
{
	m_pRenderer->ClearFrame(Vec4(0.3f, 0.3f, 0.4f, 1.0f));

	m_pRenderer->StartRenderMode(OG_RENDERMODE_GEOMETRY);

	if (m_pCurLevel)
        m_pCurLevel->GetTerrain()->Render(m_mView);

    m_pSg->RenderAll(m_pCamera);

    if (m_EditorMode == EDITMODE_OBJECTS)
    {
        if (m_pCurActor)
        {
            MATRIX mModelView = m_pCurActor->GetSgNode()->GetWorldTransform();
            MatrixMultiply(mModelView, mModelView, m_mView);
            m_pCurActor->GetSgNode()->GetRenderable()->Render(mModelView);
        }
    }

	m_pRenderer->FinishRenderMode();
    m_pRenderer->Reset();

    RenderHelpers();

    glFlush();
}


// Render scene helpers.
void CEditorLevelScene::RenderHelpers()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m_mView.f);
    glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	if (m_bShowAABB)
	{
        if (m_pCurActor)
        {
            DrawOBB(m_pCurActor->GetPhysicalObject()->GetOBB());
        }
	}

    if (m_pPickedActor)
    {
        DrawOBB(m_pPickedActor->GetPhysicalObject()->GetOBB());
    }

    if (m_pCurLevel)
    {
		DrawLevelRanges(m_pCurLevel->GetStartPosition(),
			m_pCurLevel->GetFinishPosition(),
            m_pCurLevel->GetActiveWidth(),
			m_fAirBotHeight);
    }

    glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
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


// Save level
bool CEditorLevelScene::SaveLevel ()
{
    return GetLevelManager()->SaveLevel(m_pCurLevel);
}


// Set editor mode
void CEditorLevelScene::SetEditMode (TerrainEditMode _Mode)
{
    m_EditorMode = _Mode;
    switch (m_EditorMode)
    {
        case EDITMODE_OBJECTS:
            {
                m_pPickedActor = NULL;
                m_vCurRotation = Vec3(0, 0, 0);
                m_vCurScaling = Vec3(1, 1, 1);
                if (m_CurModelAlias.empty())
                    SetNewCurrentNodeForPlacement(NULL, OG_ACTOR_NONE);
                else
                    SetNewCurrentNodeForPlacement(m_CurModelAlias.c_str(), m_CurActorType);
            }
            break;

        case EDITMODE_ADJUST:
            {
                m_vCurRotation = Vec3(0, 0, 0);
                m_vCurScaling = Vec3(1, 1, 1);
                m_pPickedActor = NULL;
                SetNewCurrentNodeForPlacement(NULL, OG_ACTOR_NONE);
            }
            break;

        case EDITMODE_SETTINGS:
            {
                m_vCurRotation = Vec3(0, 0, 0);
                m_vCurScaling = Vec3(1, 1, 1);
                m_pPickedActor = NULL;
                SetNewCurrentNodeForPlacement(NULL, OG_ACTOR_NONE);
            }
            break;
    }
}


// Setup new current node for placement.
void CEditorLevelScene::SetNewCurrentNodeForPlacement(const char* _pModelAlias, int _ActorType)
{
	OG_SAFE_DELETE(m_pCurActor);
	m_CurActorType = OG_ACTOR_NONE;

	if (_pModelAlias != NULL && _ActorType != (int)OG_ACTOR_NONE)
	{
        m_vCurScaling.x = m_vCurScaling.y = m_vCurScaling.z = 1;
        m_vCurRotation.x = m_vCurRotation.y = m_vCurRotation.z = 0;
		m_CurActorType = (OGActorType)_ActorType;
		m_CurModelAlias = std::string(_pModelAlias);

		m_pCurActor = GetActorManager()->CreateActor(
            m_CurActorType, 
            m_CurModelAlias,
            Vec3(0,0,0), 
            Vec3(0,0,0), 
            Vec3(1,1,1));
	}
}


// Place the current node
void CEditorLevelScene::PlaceCurrentNode (int _mouseX, int _mouseY)
{
    if (m_pCurLevel == NULL)
        return;

    Vec3 vPos, vVec, vIntersection;
    GetMousePickingRay(vPos, vVec, _mouseX, _mouseY);
    bool bIntersection = m_pCurLevel->GetTerrain()->GetRayIntersection(vPos, vVec, &vIntersection);
    if (bIntersection && m_pCurActor)
    {
        if (m_CurActorType == OG_ACTOR_AIRBOT || m_CurActorType == OG_ACTOR_PLAYER)
        {
            vIntersection.y = m_fAirBotHeight;
        }
        GetActorManager()->AddActor (m_pCurActor);
        m_pCurActor = GetActorManager()->CreateActor(
            m_CurActorType, 
            m_CurModelAlias.c_str(), 
            vIntersection, 
            m_vCurRotation, 
            m_vCurScaling);
    }
}


// Update current actor's position
void CEditorLevelScene::UpdateCurrentNodePosition (const Vec3& _vPos)
{
    if (m_pCurActor == NULL)
        return;

    Vec3 vPos = _vPos;
    if (m_CurActorType == OG_ACTOR_AIRBOT || m_CurActorType == OG_ACTOR_PLAYER)
    {
        vPos.y = m_fAirBotHeight;
    }
    m_pCurActor->GetPhysicalObject()->SetPosition(vPos);
}


// Update level start position
void CEditorLevelScene::UpdateLevelStartPosition (const Vec3& _vPos)
{
    if (m_pCurLevel == NULL)
        return;

    m_pCurLevel->SetStartPosition(_vPos);

    IOGActor* pPlayerActor = GetActorManager()->GetPlayersActor();
    if (pPlayerActor)
    {
        Vec3 vCraftPos = _vPos;
        vCraftPos.y = m_fAirBotHeight;
        pPlayerActor->GetPhysicalObject()->SetPosition(vCraftPos);
    }
}


// Update level start position
void CEditorLevelScene::UpdateLevelFinishPosition (const Vec3& _vPos)
{
    if (m_pCurLevel == NULL)
        return;

    m_pCurLevel->SetFinishPosition(_vPos);
}


// Get picking ray
void CEditorLevelScene::GetMousePickingRay (Vec3& _vPos, Vec3& _vRay, int _mouseX, int _mouseY)
{
    Vec3 vPick = GetPickRay (_mouseX, _mouseY);
    _vPos = m_pCamera->GetPosition();
    _vRay = vPick - _vPos;
    _vRay.normalize();
}


// Pick actor
void CEditorLevelScene::PickActor (int _mouseX, int _mouseY)
{
    Vec3 vPos, vVec;
    GetMousePickingRay(vPos, vVec, _mouseX, _mouseY);
    m_pPickedActor = GetActorManager()->GetNearestIntersectedActor(vPos, vVec);
}


// Camera zoom
void CEditorLevelScene::CameraZoom (float _fFactor)
{
	m_pCamera->Move (_fFactor);
}
