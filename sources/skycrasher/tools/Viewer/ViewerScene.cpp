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
#include "ViewerScene.h"
#include "Game.h"
#include <IOGGraphicsHelpers.h>
#include "IOGMath.h"


CViewerScene::CViewerScene()
{
    m_pResourceMgr = NULL;
    m_pSg = NULL;
    m_pRenderer = NULL;
    m_pCamera = NULL;
    m_pActorMgr = NULL;
    m_pCurActor = NULL;
    m_fCameraDistance = 200.0f;
    m_bShowAABB = false;
    m_bShowGrid = true;
    m_bInited = false;
    m_ResX = m_ResY = 0;
}


CViewerScene::~CViewerScene()
{
    if (m_pResourceMgr)
    {
        m_pResourceMgr->Unload(OG_RESPOOL_GAME);
    }

    if (m_pActorMgr)
    {
        if (m_pCurActor)
        {
            m_pActorMgr->DestroyActor(m_pCurActor);
            m_pCurActor = NULL;
        }
    }
}


// Initialize scene
bool CViewerScene::Init ()
{
    if (m_bInited)
        return true;

    glewInit();

    m_pRenderer = GetRenderer();
    m_pRenderer->SetViewport(m_ResX, m_ResY, 4.0f, 4500.0f, 0.67f);

    m_pResourceMgr = GetResourceMgr();
    m_pSg = GetSceneGraph();
    m_pCamera = m_pRenderer->GetCamera();
    m_pActorMgr = GetActorManager();

    OGVec3 vTarget (0, 0, 0);
    OGVec3 vDir (0, -1.0f, 0.4f);
    vDir = vDir.normalize();
    OGVec3 vUp = vDir.cross (OGVec3(1, 0, 0));
    m_pCamera->Setup (vTarget - (vDir*m_fCameraDistance), vTarget, vUp);

    OGVec3 vLightDir = OGVec3(0,1,0);
    OGVec4 vLightColor = OGVec4(1,1,1,1);
    IOGLight* pMainLight = m_pRenderer->GetLightMgr()->CreateLight();
    pMainLight->type = OG_LIGHT_DIRECTIONAL;
    pMainLight->vPosition = vLightDir;
    pMainLight->fIntensity = 100.0f;
    pMainLight->vAmbientColor = OGVec4(vLightColor.x, vLightColor.y, vLightColor.z, 1.0f);
    pMainLight->vDiffuseColor = OGVec4(vLightColor.x, vLightColor.y, vLightColor.z, 1.0f);
    pMainLight->vSpecularColor = OGVec4(vLightColor.x, vLightColor.y, vLightColor.z, 1.0f);

    glDisable(GL_CULL_FACE);
    glEnable(GL_NORMALIZE);

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
                (*iter)->type == OG_ACTOR_GAUSSRAY )
            {
                continue;
            }

            CommonToolEvent<ResLoadEventData> cmd(EVENTID_RESLOAD);
            cmd.SetEventCustomData(ResLoadEventData(wxT((*iter)->alias.c_str()), 
                wxT(ActorTypeToGroupName((*iter)->type).c_str()),
                wxT((*iter)->icon.c_str())));
            GetEventHandlersTable()->FireEvent(EVENTID_RESLOAD, &cmd);
        }
    }
    else
    {
        return false;
    }

    SetupModel(NULL);
    m_bInited = true;

    return true;
}


// Setup viewport
void CViewerScene::SetViewport (int _Width, int _Height)
{
    m_ResX = _Width;
    m_ResY = _Height;

    glViewport(0, 0, m_ResX, m_ResY);
    if (m_bInited)
    {
        m_pRenderer->EnableFog(false);
        m_pRenderer->SetViewport(m_ResX, m_ResY, 4.0f, 4500.0f, 0.67f);
    }
}


// Update controller
void CViewerScene::Update (unsigned long _ElapsedTime)
{
    GetPhysics()->UpdateAll(0);
    m_pActorMgr->UpdateEditor(33);
    m_pSg->Update(33);
    m_pCamera->Update();
    m_mView = m_pCamera->GetViewMatrix();
}


// Render controller scene
void CViewerScene::RenderScene ()
{
    m_pRenderer->SetClearColor(OGVec4(0.3f, 0.3f, 0.4f, 1.0f));

    m_pSg->RenderScene(m_pCamera);

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
    m_pRenderer->DrawScene();
    RenderHelpers();

    glFlush();
}


// Render scene helpers.
void CViewerScene::RenderHelpers()
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

    if (m_bShowGrid)
    {
        DrawCoordGrid(50, 2, 10);
    }

    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
}


// Setup model.
void CViewerScene::SetupModel(ResourceItem* _pModelItem)
{
    if (_pModelItem == NULL)
        return;

    if (m_pCurActor)
    {
        m_pActorMgr->DestroyActor(m_pCurActor);
    }

    const char* pModelAlias = _pModelItem->name;
    if (pModelAlias != NULL)
    {
        m_pCurActor = m_pActorMgr->CreateActor(pModelAlias, OGVec3(0,0,0), OGVec3(0,0,0), OGVec3(1,1,1));
        m_pActorMgr->AddActor(m_pCurActor);
        m_pCurActor->Activate(true);

        IOGModel* pModel = m_pResourceMgr->GetModel(OG_RESPOOL_GAME, m_pCurActor->GetParams()->model_alias);
        if (pModel)
        {
            const std::vector<IOGMesh*>& subMeshes = pModel->GetMeshes();
            size_t numSubMeshes = subMeshes.size();
            for (size_t n = 0; n < numSubMeshes; ++n)
            {
                CommonToolEvent<MeshLoadEventData> cmd(EVENTID_MESHLOAD);
                cmd.SetEventCustomData(MeshLoadEventData(subMeshes[n]->GetName(), (unsigned int)n, _pModelItem->GetId()));
                GetEventHandlersTable()->FireEvent(EVENTID_MESHLOAD, &cmd);
            }

            if (numSubMeshes > 0)
            {
                IOGMaterial* pMaterial = subMeshes[0]->GetMaterial();
                if (pMaterial)
                {
                    CommonToolEvent<MtlLoadEventData> cmd(EVENTID_MTLLOAD);
                    cmd.SetEventCustomData(MtlLoadEventData(
                        pMaterial->GetAmbient().x,
                        pMaterial->GetDiffuse().x,
                        pMaterial->GetSpecular().x,
                        pMaterial->GetBlend()));
                    GetEventHandlersTable()->FireEvent(EVENTID_MTLLOAD, &cmd);
                }
            }
        }
    }
}


// Adjust model material.
void CViewerScene::AdjustMaterial(MtlType _type, float _val)
{
    if (m_pCurActor)
    {
        IOGModel* pModel = m_pResourceMgr->GetModel(OG_RESPOOL_GAME, m_pCurActor->GetParams()->model_alias);
        const std::vector<IOGMesh*>& subMeshes = pModel->GetMeshes();
        IOGMaterial* pMaterial = subMeshes[0]->GetMaterial();

        switch(_type)
        {
        case MTLTYPE_DIF:
            pMaterial->SetDiffuse(OGVec4(_val, _val, _val, 1.0f));
            break;
        case MTLTYPE_AMB:
            pMaterial->SetAmbient(OGVec4(_val, _val, _val, 1.0f));
            break;
        case MTLTYPE_SPC:
            pMaterial->SetSpecular(OGVec4(_val, _val, _val, 1.0f));
            break;
        }
    }
}


// Camera zoom
void CViewerScene::CameraZoom (float _fFactor)
{
    m_fCameraDistance -= _fFactor;
    CameraRotateHor (0);
}


// Camera rotate
void CViewerScene::CameraRotate (float _fAngleH, float _fAngleV)
{
}


// Camera rotate horizontally
void CViewerScene::CameraRotateHor (float _fAngle)
{
    OGVec3 vTarget (0, 0, 0);

    OGMatrix mR;
    MatrixRotationY(mR, _fAngle);
    OGVec3 vDir, vRight;
    MatrixVec3Multiply(vDir, m_pCamera->GetDirection(), mR);
    MatrixVec3Multiply(vRight, m_pCamera->GetRight(), mR);
    vDir.normalize();
    OGVec3 vUp = vDir.cross (vRight);
    m_pCamera->Setup (vTarget - (vDir*m_fCameraDistance), vTarget, vUp);
}


// Camera rotate vertically
void CViewerScene::CameraRotateVer (float _fAngle)
{
    OGVec3 vTarget (0, 0, 0);

    OGMatrix mR;
    MatrixRotationAxis(mR, _fAngle, m_pCamera->GetRight().x, m_pCamera->GetRight().y, m_pCamera->GetRight().z);
    OGVec3 vDir, vRight;
    MatrixVec3Multiply(vDir, m_pCamera->GetDirection(), mR);
    MatrixVec3Multiply(vRight, m_pCamera->GetRight(), mR);
    vDir.normalize();
    OGVec3 vUp = vDir.cross (vRight);
    m_pCamera->Setup (vTarget - (vDir*m_fCameraDistance), vTarget, vUp);
}


// Convert actor type to group name.
std::string CViewerScene::ActorTypeToGroupName(OGActorType type)
{
    switch (type)
    {
    case OG_ACTOR_STATIC:
        return std::string("Static");

    case OG_ACTOR_NONE:
    case OG_ACTOR_PLASMAMISSILE:
    case OG_ACTOR_MISSILE:
    case OG_ACTOR_GAUSSRAY:
        return std::string("Others");

    case OG_ACTOR_LANDBOT:
    case OG_ACTOR_AIRBOT:
    case OG_ACTOR_PLAYER:
        return std::string("Units");

    case OG_ACTOR_BONUS:
        return std::string("Bonuses");
    }

    return std::string("Others");
}


// Save changes.
void CViewerScene::SaveChanges()
{
    if (m_pCurActor)
    {
        IOGModel* pModel = m_pResourceMgr->GetModel(OG_RESPOOL_GAME, m_pCurActor->GetParams()->model_alias);
        pModel->SaveParams();
    }
}
