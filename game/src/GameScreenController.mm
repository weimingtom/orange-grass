/*
 *  GameScreenController.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "GameScreenController.h"
#include "ogcamera.h"


CGameScreenController::CGameScreenController() :	m_pPlatform(NULL),
													m_pResourceMgr(NULL),
													m_pUIHandler(NULL),
													m_State(CSTATE_NO),
													m_pModel(NULL),
													m_pTerrain(NULL),
													m_pCamera(NULL)
{
}


CGameScreenController::~CGameScreenController()
{
	m_pPlatform = NULL;
	m_pResourceMgr = NULL;
	m_pUIHandler = NULL;
	m_State = CSTATE_NO;
	m_pModel = NULL;
	m_pTerrain = NULL;
	if (m_pCamera)
	{
		delete m_pCamera;
		m_pCamera = NULL;
	}
}


// Initialize controller
bool CGameScreenController::Init (IPlatform* _pPlatform)
{
	m_pPlatform = _pPlatform;
	m_pResourceMgr = m_pPlatform->GetResourceManager();
	m_pUIHandler = m_pPlatform->GetUIHandler();
	
	m_pModel = m_pResourceMgr->GetModel ("palm");
	m_pTerrain = m_pResourceMgr->GetTerrain ("main");

	m_pCamera = new COGCamera ();
	m_pCamera->Setup (Vec3(-200, 150, 300), Vec3(-200, 150, 0), Vec3(0, 1, 0));
	m_pCamera->RotateView (-0.9f, Vec3(1, 0, 0));
	
	return true;
}


// Update controller
void CGameScreenController::Update (unsigned int _ElapsedTime)
{
	if (m_State != CSTATE_ACTIVE)
		return;

	m_pCamera->Strafe(0.5f, Vec3(0, 0, 1));
	m_mView = m_pCamera->Update();
	m_pModel->UpdateAnimation (_ElapsedTime);
}


// Render controller scene
void CGameScreenController::RenderScene ()
{
	if (m_State != CSTATE_ACTIVE)
		return;
	
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(m_mProjection.f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m_mView.f);
	
	{
		VECTOR4 vDiffuse;
		vDiffuse.x = f2vt(1.0f);
		vDiffuse.y = f2vt(1.0f);
		vDiffuse.z = f2vt(1.0f);
		vDiffuse.w = f2vt(1.0f);
		VECTOR4 vLightDirection;
		vLightDirection.x = f2vt(0.0f);
		vLightDirection.y = f2vt(1.0f);
		vLightDirection.z = f2vt(0.0f);
		vLightDirection.w = 0;
		
		glLightfv(GL_LIGHT0, GL_POSITION, (VERTTYPE*)&vLightDirection);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, (VERTTYPE*)&vDiffuse);
	}
	
	//glBindTexture(GL_TEXTURE_2D, m_pResourceMgr->GetTexture("land_grass")->GetTextureId());
	m_pTerrain->Render (m_mView);
	m_pModel->Render (m_mView);
	
    /*glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	m_pUIHandler->DisplayText(50, 86, 0.4f, RGBA(255,25,25,255), "0");
	m_pUIHandler->DisplayDefaultTitle("", "", eDisplayTextLogoIMG);
	m_pUIHandler->Flush();	
    glEnable(GL_DEPTH_TEST);*/
}


// Activate
void CGameScreenController::Activate ()
{
	glClearColor(f2vt(0.3f), f2vt(0.3f), f2vt(0.4f), f2vt(1.0f));
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	MatrixPerspectiveFovRH(m_mProjection, f2vt(1.0f), f2vt(WindowHeight/WindowWidth), f2vt(4.0f), f2vt(2500.0f), true);
	
	m_State = CSTATE_ACTIVE;
}


// deactivate
void CGameScreenController::Deactivate ()
{
	m_State = CSTATE_INACTIVE;
}
