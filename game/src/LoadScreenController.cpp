/*
 *  LoadScreenController.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenGL2.h"
#include "LoadScreenController.h"
#include "OrangeGrass.h"
#include "common.h"


CLoadScreenController::CLoadScreenController() :	m_pResourceMgr(NULL),
													m_State(CSTATE_NO),
                                                    m_Type(SCRTYPE_LOAD),
													m_pHUD(NULL),
                                                    m_pCurLevel(NULL),
													m_bLoaded(false),
                                                    m_bDisplayed(false)
{
}


CLoadScreenController::~CLoadScreenController()
{
	OG_SAFE_DELETE(m_pHUD);
	
	m_pResourceMgr = NULL;
	m_State = CSTATE_NO;
	m_bLoaded = false;
}


// Initialize controller
bool CLoadScreenController::Init ()
{
	m_pResourceMgr = GetResourceMgr();
    m_pResourceMgr->Init();
	m_pHUD = CreateSprite("load_scr");
	
	return true;
}


// Update controller
void CLoadScreenController::Update (unsigned long _ElapsedTime)
{
	if (!m_bLoaded && m_State == CSTATE_ACTIVE && m_bDisplayed)
	{
        GetLevelManager()->Init();

    	std::vector<IOGResourceInfo> resInfo;
		if (m_pResourceMgr->Load(resInfo))
		{
            m_pCurLevel = GetLevelManager()->LoadLevel(std::string("level_0"));
			m_bLoaded = true;
			Deactivate();
		}
        else 
        {
            printf("Failed to load level\n");
        }

	}
}


// Render controller scene
void CLoadScreenController::RenderScene ()
{
	if (!m_bLoaded && m_State == CSTATE_ACTIVE)
	{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
		m_pHUD->SetPosition(0, 0, SCR_WIDTH, SCR_HEIGHT);
		m_pHUD->Render ();
        m_bDisplayed = true;
	}
}


// Activate
void CLoadScreenController::Activate ()
{
	glClearColor(f2vt(0.0f), f2vt(0.0f), f2vt(0.0f), f2vt(1.0f));
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

    m_bDisplayed = false;
	m_State = CSTATE_ACTIVE;
}


// deactivate
void CLoadScreenController::Deactivate ()
{
	m_State = CSTATE_INACTIVE;
    m_bDisplayed = false;
}
