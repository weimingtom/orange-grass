/*
 *  ViewerScene.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenGL2.h"
#include "ViewerScene.h"
#include "OrangeGrass.h"
#include <IOGGraphicsHelpers.h>


CViewerScene::CViewerScene()
{
	m_pCurActor = NULL;
	m_fCameraDistance = 200.0f;
	m_bShowAABB = false;
	m_bShowGrid = true;
    m_bInited = false;
	m_ResX = m_ResY = 0;

	m_fFineAngleStep = TO_RADIAN(2.0f);
    m_fCoarseAngleStep = TO_RADIAN(45.0f);
}


CViewerScene::~CViewerScene()
{
    OG_SAFE_DELETE(m_pCurActor);
}


// Initialize scene
bool CViewerScene::Init ()
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

	Vec3 vLightDir = Vec3(0,1,0);
	Vec4 vLightColor = Vec4(1,1,1,1);
	m_pRenderer->GetLight()->SetDirection(vLightDir);
	m_pRenderer->GetLight()->SetColor(vLightColor);

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

	if (GetActorParamsMgr()->Init())
	{
		std::list<IOGActorParams*> ActorsParamsList;
		GetActorParamsMgr()->GetParamsList(ActorsParamsList);
		std::list<IOGActorParams*>::const_iterator iter = ActorsParamsList.begin();
		for (; iter != ActorsParamsList.end(); ++iter)
		{
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
		m_pRenderer->SetViewport(m_ResX, m_ResY, 4.0f, 4500.0f, 0.67f);
	}
}


// Update controller
void CViewerScene::Update (unsigned long _ElapsedTime)
{
	GetPhysics()->UpdateAll(0);
    m_pActorMgr->Update(10);
	m_pCamera->Update();
	m_mView = m_pCamera->GetViewMatrix();

    if (m_pCurActor)
    {
        m_pCurActor->GetPhysicalObject()->Update(10);
        m_pCurActor->Update(10);
    }
}


// Render controller scene
void CViewerScene::RenderScene ()
{
	m_pRenderer->ClearFrame(Vec4(0.3f, 0.3f, 0.4f, 1.0f));

	m_pRenderer->StartRenderMode(OG_RENDERMODE_GEOMETRY);

	if (m_pCurActor)
	{
		MATRIX mModel = m_pCurActor->GetSgNode()->GetWorldTransform();
		m_pCurActor->GetSgNode()->GetRenderable()->Render(mModel);
	}
	m_pRenderer->FinishRenderMode();

	m_pRenderer->StartRenderMode(OG_RENDERMODE_TEXT);
#ifdef STATISTICS
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
#endif
	m_pRenderer->FinishRenderMode();

	m_pRenderer->Reset();

	RenderHelpers();

	glFlush();
}


// Render scene helpers.
void CViewerScene::RenderHelpers()
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

	if (m_bShowGrid)
	{
		DrawCoordGrid(50, 2, 10);
	}

    glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
}


// Setup model.
void CViewerScene::SetupModel(const char* _pModelAlias)
{
	OG_SAFE_DELETE(m_pCurActor);

	if (_pModelAlias != NULL)
	{
		m_pCurActor = m_pActorMgr->CreateActor(
            _pModelAlias,
            Vec3(0,0,0), 
            Vec3(0,0,0), 
            Vec3(1,1,1));
	}
	else
	{
	}
}


// Camera zoom
void CViewerScene::CameraZoom (float _fFactor)
{
	m_pCamera->Move (_fFactor);
}


// Camera move
void CViewerScene::CameraMove (float _fX, float _fZ)
{
	m_pCamera->Strafe(5.5f, Vec3(_fX, 0, _fZ));
}