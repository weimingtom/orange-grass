/*
 *  GameScreenController.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include <OpenGL2.h>
#include "GameScreenController.h"
#include <OrangeGrass.h>
#include "common.h"


CGameScreenController::CGameScreenController() :	m_pResourceMgr(NULL),
													m_State(CSTATE_NO),
                                                    m_Type(SCRTYPE_GAME),
													m_pCurLevel(NULL)
{
}


CGameScreenController::~CGameScreenController()
{
	m_pResourceMgr = NULL;
	m_State = CSTATE_NO;
	m_pCurLevel = NULL;
}


// Initialize controller
bool CGameScreenController::Init ()
{
	m_pResourceMgr = GetResourceMgr();
    m_pCurLevel = GetLevelManager()->LoadLevel(std::string("level_0"));
    
    MatrixPerspectiveFovRH(m_mProjection, 1.0f, float(SCR_WIDTH)/float(SCR_HEIGHT), 4.0f, 4500.0f, true);
	
    Vec3 vTarget (150, 0, -100);
    Vec3 vDir (0, 0.4f, 0.6f);
    vDir = vDir.normalize();
    Vec3 vUp = vDir.cross (Vec3(0, 1, 0));
    GetSceneGraph()->GetCamera()->Setup (vTarget + (vDir* 200.0f), vTarget, vUp);

    glClearColor(0.3f, 0.3f, 0.4f, 1.0f);
    glEnable(GL_TEXTURE_2D);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnable(GL_NORMALIZE);

    GetSceneGraph()->GetLight()->Apply();

    return true;
}


// Update controller
void CGameScreenController::Update (unsigned int _ElapsedTime)
{
	if (m_State != CSTATE_ACTIVE)
		return;

    GetPhysics()->Update(10);
    GetActorManager()->Update(10);
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
    m_mView = GetSceneGraph()->GetCamera()->Update();
    glLoadMatrixf(m_mView.f);

    if (m_pCurLevel)
        m_pCurLevel->GetTerrain()->Render(m_mView);

    GetSceneGraph()->Render(m_mView);
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
