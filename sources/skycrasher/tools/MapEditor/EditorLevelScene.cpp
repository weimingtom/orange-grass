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
#include "OpenGL2.h"
#include "EditorLevelScene.h"
#include "Game.h"
#include <IOGGraphicsHelpers.h>


CEditorLevelScene::CEditorLevelScene()
{
    m_pCurLevel = NULL;
	m_pCurActor = NULL;
	m_pPickedActor = NULL;
	m_vCurScaling = OGVec3(1,1,1);
	m_CurActorType = OG_ACTOR_NONE;
	m_fAirBotHeight = 80.0f;
	m_fCameraDistance = 400.0f;
	m_bShowAABB = false;
    m_bInited = false;
	m_ResX = m_ResY = 0;
	m_EditorMode = EDITMODE_OBJECTS;
    m_CamMode = CAMMODE_EDITOR;

	m_fFineAngleStep = TO_RADIAN(2.0f);
    m_fCoarseAngleStep = TO_RADIAN(45.0f);
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

	GetAppSettings()->Init("settings.xml");
	GetAppSettings()->InitScreenMode();

	glewInit();

	m_pRenderer = GetRenderer();
	m_pRenderer->SetViewport(m_ResX, m_ResY, 4.0f, 4500.0f, 0.67f);
	m_pResourceMgr = GetResourceMgr();
	m_pSg = GetSceneGraph();
	m_pCamera = m_pRenderer->GetCamera();
	m_pActorMgr = GetActorManager();
	m_pLevelMgr = GetLevelManager();

    CameraMode(m_CamMode);

	glDisable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);

	if (m_pLevelMgr->Init() == false)
	{
		return false;
	}

	if (m_pResourceMgr->Load(OG_RESPOOL_GAME) == false)
	{
        return false;
	}

	if (GetActorParamsMgr()->Init())
	{
		std::list<IOGActorParams*> ActorsParamsList;
		GetActorParamsMgr()->GetParamsList(ActorsParamsList);
		std::list<IOGActorParams*>::const_iterator iter = ActorsParamsList.begin();
		for (; iter != ActorsParamsList.end(); ++iter)
		{
			if ((*iter)->type == OG_ACTOR_MISSILE ||
				(*iter)->type == OG_ACTOR_PLASMAMISSILE ||
				(*iter)->type == OG_ACTOR_GAUSSRAY ||
				(*iter)->type == OG_ACTOR_BONUS ||
				(*iter)->type == OG_ACTOR_PLAYER )
			{
				continue;
			}

			CommonToolEvent<ResLoadEventData> cmd(EVENTID_RESLOAD);
			cmd.SetEventCustomData(ResLoadEventData(wxT((*iter)->alias.c_str()), 
				wxT("Models"), 
				wxT((*iter)->icon.c_str())));
			GetEventHandlersTable()->FireEvent(EVENTID_RESLOAD, &cmd);
		}
	}
	else
	{
        return false;
	}

	SetNewCurrentNodeForPlacement(NULL);
    m_bInited = true;

	return true;
}


// Setup viewport
void CEditorLevelScene::SetViewport (int _Width, int _Height)
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
void CEditorLevelScene::Update (unsigned long _ElapsedTime)
{
    GetPhysics()->UpdateAll(0);
    m_pActorMgr->UpdateEditor(33);
    m_pSg->Update(33);
    m_pCamera->Update();
    m_mView = m_pCamera->GetViewMatrix();

    if (m_pCurActor)
    {
        m_pCurActor->GetPhysicalObject()->Update(0);
        m_pCurActor->UpdateEditor(0);
    }
}


// Render controller scene
void CEditorLevelScene::RenderScene ()
{
    m_pRenderer->SetClearColor(OGVec4(0.3f, 0.3f, 0.4f, 1.0f));

    if (m_pCurLevel)
    {
        if (m_CamMode == CAMMODE_GAME)
        {
            m_pRenderer->EnableFog(true);
        }

        m_pSg->RenderScene(m_pCamera);
        if (m_EditorMode == EDITMODE_OBJECTS)
        {
            if (m_pCurActor)
            {
                m_pCurActor->GetSgNode()->Render(m_pCamera, OG_RENDERPASS_SCENE);
            }
        }

        if (m_CamMode == CAMMODE_GAME)
        {
            m_pRenderer->EnableFog(false);
        }
    }
    /*
    unsigned long Verts; 
    unsigned long Faces;
    unsigned long TextureSwitches;
    unsigned long VBOSwitches;
    unsigned long DrawCalls;
    GetStatistics()->GetStatistics(Verts, Faces, TextureSwitches, VBOSwitches, DrawCalls);
    m_pRenderer->DisplayString(OGVec2(85.0f, 2.0f), 0.4f, 0x7FFFFFFF, "Vertices: %d", Verts);
    m_pRenderer->DisplayString(OGVec2(85.0f, 6.0f), 0.4f, 0x7FFFFFFF, "Faces: %d", Faces);
    m_pRenderer->DisplayString(OGVec2(85.0f,10.0f), 0.4f, 0x7FFFFFFF, "Textures: %d", TextureSwitches);
    m_pRenderer->DisplayString(OGVec2(85.0f,14.0f), 0.4f, 0x7FFFFFFF, "VBO: %d", VBOSwitches);
    m_pRenderer->DisplayString(OGVec2(85.0f,18.0f), 0.4f, 0x7FFFFFFF, "DP: %d", DrawCalls);
    GetStatistics()->Reset();

    RenderHelpers();
    */
    m_pRenderer->DrawScene();

    glFlush();
}


// Render scene helpers.
void CEditorLevelScene::RenderHelpers()
{
    glUseProgram(0);

    m_pRenderer->GetProjectionMatrix(m_mProjection);
    m_pRenderer->GetViewMatrix(m_mView);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(m_mProjection.f);
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
        std::vector<IOGMesh*> meshes;
        m_pCurLevel->GetTerrain()->GetMeshes();
        for (unsigned int i = 0; i < meshes.size(); ++i)
        {
            DrawAABB(meshes[i]->GetAABB());
        }

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
        m_pLevelMgr->UnloadLevel();
    }

    m_pCurLevel = m_pLevelMgr->LoadLevel(_LevelName);
    if (m_pCurLevel == NULL)
    {
        return false;
    }

    IOGActor* pPlayerActor = m_pActorMgr->GetPlayersActor();
    OGVec3 vCraftPos = m_pCurLevel->GetStartPosition();
    vCraftPos.y = m_fAirBotHeight;
    if (!pPlayerActor)
    {
        pPlayerActor = m_pActorMgr->CreateActor(
            std::string("helicopter_player"),
            vCraftPos, 
            OGVec3(0,0,0), 
            OGVec3(1,1,1));
        m_pActorMgr->AddActor(pPlayerActor);
    }
    else
    {
        pPlayerActor->GetPhysicalObject()->SetPosition(vCraftPos);
    }

    CameraMode(m_CamMode);

    return true;
}


// Save level
bool CEditorLevelScene::SaveLevel ()
{
    return m_pLevelMgr->SaveLevel();
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
                m_vCurRotation = OGVec3(0, 0, 0);
                m_vCurScaling = OGVec3(1, 1, 1);
                if (m_CurModelAlias.empty())
                    SetNewCurrentNodeForPlacement(NULL);
                else
                    SetNewCurrentNodeForPlacement(m_CurModelAlias.c_str());
            }
            break;

        case EDITMODE_ADJUST:
            {
                m_vCurRotation = OGVec3(0, 0, 0);
                m_vCurScaling = OGVec3(1, 1, 1);
                m_pPickedActor = NULL;
                SetNewCurrentNodeForPlacement(NULL);
            }
            break;

        case EDITMODE_SETTINGS:
            {
                m_vCurRotation = OGVec3(0, 0, 0);
                m_vCurScaling = OGVec3(1, 1, 1);
                m_pPickedActor = NULL;
                SetNewCurrentNodeForPlacement(NULL);
            }
            break;
    }
}


// Setup new current node for placement.
void CEditorLevelScene::SetNewCurrentNodeForPlacement(const char* _pModelAlias)
{
	OG_SAFE_DELETE(m_pCurActor);

	if (_pModelAlias != NULL)
	{
        m_vCurScaling.x = m_vCurScaling.y = m_vCurScaling.z = 1;
        m_vCurRotation.x = m_vCurRotation.y = m_vCurRotation.z = 0;
		m_CurModelAlias = std::string(_pModelAlias);

		m_pCurActor = m_pActorMgr->CreateActor(
            m_CurModelAlias,
            OGVec3(0,0,0), 
            OGVec3(0,0,0), 
            OGVec3(1,1,1));
		m_pCurActor->Activate(true);
		m_CurActorType = m_pCurActor->GetType();
	}
	else
	{
		m_CurActorType = OG_ACTOR_NONE;
	}
}


// Place the current node
void CEditorLevelScene::PlaceCurrentNode (const OGVec3& _vPos)
{
    if (m_pCurLevel == NULL || m_pCurActor == NULL)
        return;

    OGVec3 vIntersection = _vPos;
	if (m_CurActorType == OG_ACTOR_AIRBOT || m_CurActorType == OG_ACTOR_PLAYER)
	{
		vIntersection.y = m_fAirBotHeight;
	}
	m_pActorMgr->AddActor (m_pCurActor);
	m_pCurActor = m_pActorMgr->CreateActor(
		m_CurModelAlias.c_str(), 
		vIntersection, 
		m_vCurRotation, 
		m_vCurScaling);
	m_pCurActor->Activate(true);
}


// Update current actor's position
void CEditorLevelScene::UpdateCurrentNodePosition (const OGVec3& _vPos)
{
    if (m_pCurActor == NULL)
        return;

    OGVec3 vPos = _vPos;
    if (m_CurActorType == OG_ACTOR_AIRBOT || m_CurActorType == OG_ACTOR_PLAYER)
    {
        vPos.y = m_fAirBotHeight;
    }
    m_pCurActor->GetPhysicalObject()->SetPosition(vPos);
}


// Update level start position
void CEditorLevelScene::UpdateLevelStartPosition (const OGVec3& _vPos)
{
    if (m_pCurLevel == NULL)
        return;

    m_pCurLevel->SetStartPosition(_vPos);

    IOGActor* pPlayerActor = m_pActorMgr->GetPlayersActor();
    if (pPlayerActor)
    {
        OGVec3 vCraftPos = _vPos;
        vCraftPos.y = m_fAirBotHeight;
        pPlayerActor->GetPhysicalObject()->SetPosition(vCraftPos);
    }
}


// Update level start position
void CEditorLevelScene::UpdateLevelFinishPosition (const OGVec3& _vPos)
{
    if (m_pCurLevel == NULL)
        return;

    m_pCurLevel->SetFinishPosition(_vPos);
}


// Update level active width
void CEditorLevelScene::UpdateLevelActiveWidth (float _fWidthDiff)
{
	if (m_pCurLevel)
	{
		float fW = m_pCurLevel->GetActiveWidth();
		if (_fWidthDiff < 0.0f)
		{
			if (fW > 30.0f)
				fW -= 1.0f;
		}
		else if (_fWidthDiff > 0.0f)
		{
			if (fW < 400.0f)
				fW += 1.0f;
		}
		m_pCurLevel->SetActiveWidth(fW);
	}
}


// Get picking ray
void CEditorLevelScene::GetMousePickingRay (OGVec3& _vPos, OGVec3& _vRay, int _mouseX, int _mouseY)
{
    OGVec3 vPick = m_pRenderer->UnprojectCoords (_mouseX, _mouseY);
    _vPos = m_pCamera->GetPosition();
    _vRay = vPick - _vPos;
    _vRay.normalize();
}


// Get terrain intersection position.
bool CEditorLevelScene::GetTerrainIntersection (OGVec3& _vOutPos, int _mouseX, int _mouseY)
{
    if (m_pCurLevel == NULL)
        return false;

	OGVec3 vPos, vVec;
	GetMousePickingRay(vPos, vVec, _mouseX, _mouseY);
	return m_pCurLevel->GetTerrain()->GetRayIntersection(vPos, vVec, &_vOutPos);
}


// Pick actor
void CEditorLevelScene::PickActor (int _mouseX, int _mouseY)
{
    OGVec3 vPos, vVec;
    GetMousePickingRay(vPos, vVec, _mouseX, _mouseY);
    m_pPickedActor = m_pActorMgr->GetNearestIntersectedActor(vPos, vVec);
}


// Update picked actor's position
void CEditorLevelScene::UpdatePickedActorPosition (const OGVec3& _vDiff)
{
	if (m_pPickedActor)
	{
		OGVec3 vPos = m_pPickedActor->GetPhysicalObject()->GetPosition(); 
		vPos += _vDiff;
		m_pPickedActor->GetPhysicalObject()->SetPosition(vPos);
	}
}


// Update selected actor's rotation
void CEditorLevelScene::UpdateSelectedActorRotation (const OGVec3& _vRotationDiff, bool _bCoarse)
{
	float fStep = _bCoarse ? m_fCoarseAngleStep : m_fFineAngleStep;
	if (m_pCurActor)
	{
		m_vCurRotation += fStep * _vRotationDiff;
		m_pCurActor->GetPhysicalObject()->SetRotation(m_vCurRotation);
	}
	if (m_pPickedActor)
	{
		OGVec3 vRot = m_pPickedActor->GetPhysicalObject()->GetRotation();
		vRot += fStep * _vRotationDiff;
		m_pPickedActor->GetPhysicalObject()->SetRotation(vRot);
	}
}


// Update selected actor's scaling
void CEditorLevelScene::UpdateSelectedActorScaling (float _fScalingDiff, bool _bCoarse)
{
	float fStep = _bCoarse ? m_fCoarseAngleStep : m_fFineAngleStep;
	if (m_pCurActor)
	{
		m_vCurScaling += OGVec3(1,1,1) * (fStep * _fScalingDiff);
		m_pCurActor->GetPhysicalObject()->SetScaling(m_vCurScaling);
	}
	if (m_pPickedActor)
	{
		OGVec3 vScale = m_pPickedActor->GetPhysicalObject()->GetScaling();
		vScale += OGVec3(1,1,1) * (fStep * _fScalingDiff);
		m_pPickedActor->GetPhysicalObject()->SetScaling(vScale);
	}
}


// Reset selected actor's transform
void CEditorLevelScene::ResetSelectedActorTansform ()
{
	if (m_pCurActor)
	{
		m_vCurScaling.x = m_vCurScaling.y = m_vCurScaling.z = 1;
		m_vCurRotation.x = m_vCurRotation.y = m_vCurRotation.z = 0;
		OGVec3 vPos = m_pCurActor->GetPhysicalObject()->GetPosition();
		m_pCurActor->GetPhysicalObject()->SetWorldTransform(vPos, m_vCurRotation, m_vCurScaling);
	}
	if (m_pPickedActor)
	{
		OGVec3 vPos = m_pPickedActor->GetPhysicalObject()->GetPosition();
		m_pPickedActor->GetPhysicalObject()->SetWorldTransform(vPos, OGVec3(0, 0, 0), OGVec3(1, 1, 1));
	}
}


// Delete picked actor
void CEditorLevelScene::DeletePickedActor ()
{
	if (m_pPickedActor)
	{
		m_pActorMgr->DestroyActor(m_pPickedActor);
		m_pPickedActor = NULL;
	}
}


// Camera zoom
void CEditorLevelScene::CameraZoom (float _fFactor)
{
	m_pCamera->Move (_fFactor);
}


// Camera move
void CEditorLevelScene::CameraMove (float _fX, float _fZ)
{
	m_pCamera->Strafe(5.5f, OGVec3(_fX, 0, _fZ));
}


// Set camera mode
void CEditorLevelScene::CameraMode (CamModes mode)
{
    m_CamMode = mode;

    switch(mode)
    {
    case CAMMODE_EDITOR:
        {
            OGVec3 vTarget (200, 0, -100);
            if (m_pCurLevel)
            {
                vTarget = m_pActorMgr->GetPlayersActor()->GetPhysicalObject()->GetPosition();
            }
	        OGVec3 vDir (0, 1.0f, 0.4f);
	        vDir = vDir.normalize();
	        OGVec3 vUp = vDir.cross (OGVec3(1, 0, 0));
	        m_pCamera->Setup (vTarget + (vDir* m_fCameraDistance), vTarget, vUp);
            m_pCamera->Update();
        }
        break;

    case CAMMODE_GAME:
        {
        	OGVec3 vCameraDir = GetGlobalVars()->GetVec3Var("cam_dir");
	        OGVec3 vCameraOffset = GetGlobalVars()->GetVec3Var("cam_offset");
        	float fCameraTargetDistance = GetGlobalVars()->GetFVar("cam_distance");

            OGVec3 vTarget (200, m_fAirBotHeight, -100);
            if (m_pCurLevel)
            {
                vTarget = m_pActorMgr->GetPlayersActor()->GetPhysicalObject()->GetPosition() + vCameraOffset;
            }

            OGVec3 vPos = vTarget + (vCameraDir * fCameraTargetDistance);

	        OGVec3 vUp = vCameraDir.cross (OGVec3(1, 0, 0));
	        m_pCamera->Setup (vPos, vTarget, vUp);
            m_pCamera->Update();
        }
        break;
    }
}
