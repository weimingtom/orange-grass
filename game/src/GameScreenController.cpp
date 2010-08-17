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


CGameScreenController::CGameScreenController() :	m_pResourceMgr(NULL),
													m_pSg(NULL),
													m_pCamera(NULL),
													m_State(CSTATE_NO),
                                                    m_Type(SCRTYPE_GAME),
													m_pCurLevel(NULL)
{
}


CGameScreenController::~CGameScreenController()
{
	m_pResourceMgr = NULL;
	m_pSg = NULL;
	m_pCamera = NULL;

	m_State = CSTATE_NO;
	m_pCurLevel = NULL;
}


// Initialize controller
bool CGameScreenController::Init ()
{
	m_pResourceMgr = GetResourceMgr();
	m_pSg = GetSceneGraph();
	m_pCamera = m_pSg->GetCamera();

    m_pCurLevel = GetLevelManager()->LoadLevel(std::string("level_0"));
    
#ifdef WIN32
    float fRatio = float(SCR_WIDTH)/float(SCR_HEIGHT);
	Vec3 vRight = Vec3(0, 1, 0);
#else
    float fRatio = float(SCR_HEIGHT)/float(SCR_WIDTH);
	Vec3 vRight = Vec3(1, 0, 0);
#endif
    
    MatrixPerspectiveFovRH(m_mProjection, 1.0f, fRatio, 4.0f, 450.0f, true);
	
	const Vec3& vTarget = m_pCurLevel->GetStartPosition();
    Vec3 vDir (0, 0.6f, 0.4f);
    vDir = vDir.normalize();
    Vec3 vUp = vDir.cross (vRight);
    m_pCamera->Setup (vTarget + (vDir*120.0f), vTarget, vUp);

    glClearColor(0.3f, 0.3f, 0.4f, 1.0f);
    glEnable(GL_TEXTURE_2D);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnable(GL_NORMALIZE);

    m_pSg->GetLight()->Apply();

    return true;
}


// Update controller
void CGameScreenController::Update (unsigned long _ElapsedTime)
{
	if (m_State != CSTATE_ACTIVE)
		return;
    
    m_pCamera->Strafe(0.5f, Vec3(0,0,-1.0f));

    GetPhysics()->Update(_ElapsedTime);
    GetActorManager()->Update(_ElapsedTime);

	const Vec3& vFinishPoint = m_pCurLevel->GetFinishPosition();
	const Vec3& vCurPoint = m_pCamera->GetPosition();
	if (Dist2DSq(vCurPoint, vFinishPoint) <= 90000.0f)
	{
		Deactivate();
	}
}


// Render controller scene
void CGameScreenController::RenderScene ()
{
	if (m_State != CSTATE_ACTIVE)
		return;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(m_mProjection.f);

    glMatrixMode(GL_MODELVIEW);
    m_mView = m_pCamera->Update();
    glLoadMatrixf(m_mView.f);

    if (m_pCurLevel)
        m_pCurLevel->GetTerrain()->Render(m_mView);

    m_pSg->Render(m_mView);
}


// Activate
void CGameScreenController::Activate ()
{
	m_State = CSTATE_ACTIVE;
}


// deactivate
void CGameScreenController::Deactivate ()
{
	m_State = CSTATE_INACTIVE;
}
