#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#include "App.h"
#include "Mathematics.h"
#include "GraphicsDevice.h"
#include "Geometry.h"
#include "UI.h"
#include "App.h"
#include "MemoryManager.h"
#include "Macros.h"
#include "Pathes.h"
#include "ogmesh.h"
#include "ogsprite.h"
#include "ogresourcemgr.h"
#include <stdio.h>
#include <sys/time.h>


MATRIX			m_mProjection, m_mView;
int				m_iTimePrev;
CDisplayText*	AppDisplayText;
bool			bLoaded = false;
COGModel*		m_pModel = NULL;
COGSprite		m_pHUD;
COGSprite		m_pLoadProgress;
COGResourceMgr	m_pResourceMgr;


bool CShell::InitApplication()
{
	AppDisplayText = (CDisplayText*)malloc(sizeof(CDisplayText));    
	memset(AppDisplayText, 0, sizeof(CDisplayText));

	char buffer[2048];
	GetResourcePathASCII(buffer, 2048);
	
	char resource_filename[2048];
	sprintf(resource_filename, "%s/resources.xml", buffer);
	m_pResourceMgr.Init (resource_filename);
	m_pHUD.Init (m_pResourceMgr.GetTexture ("load_scr"));
	m_pLoadProgress.Init (m_pResourceMgr.GetTexture ("load_progress"));
	
	timeval tv;
	gettimeofday(&tv,NULL);
	m_iTimePrev = ((tv.tv_sec*1000) + (tv.tv_usec/1000.0));
	
	glClearColor(f2vt(0.6f), f2vt(0.8f), f2vt(1.0f), f2vt(1.0f));
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	if(AppDisplayText->SetTextures(WindowHeight, WindowWidth))
		printf("Display text textures loaded");
	return true;
}


bool CShell::QuitApplication()
{
	AppDisplayText->ReleaseTextures();
	free(AppDisplayText);
	return true;
}


bool CShell::UpdateScene()
{
    glEnable(GL_DEPTH_TEST);
	glClearColor(0.3f, 0.3f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glDisable(GL_CULL_FACE);
	return true;
}


bool CShell::RenderScene()
{
	if (!bLoaded)
	{
		if (m_pResourceMgr.LoadNext())
		{
			m_pHUD.SetPosition(0, 0, 480, 320);
			m_pHUD.Render ();
			float fProgress = m_pResourceMgr.GetLoadProgress ();
			m_pLoadProgress.SetPosition(55, 273, 383 * fProgress / 100.0f, 13);
			m_pLoadProgress.Render ();
			glDisable(GL_DEPTH_TEST);
			AppDisplayText->DisplayText(50, 86, 0.4f, RGBA(255,25,25,255), "%3.f", fProgress);
			AppDisplayText->DisplayDefaultTitle("", "", eDisplayTextLogoIMG);
			AppDisplayText->Flush();
			glEnable(GL_DEPTH_TEST);
			return true;
		}
		else
		{
			m_pModel = m_pResourceMgr.GetModel ("spectator");
			bLoaded = true;
		}
	}
	
	timeval tv;
	gettimeofday(&tv,NULL);
	int iTime = ((tv.tv_sec*1000) + (tv.tv_usec/1000.0));
	if(m_iTimePrev > iTime)
		m_iTimePrev = iTime;
	int iDeltaTime = iTime - m_iTimePrev;
	m_iTimePrev	= iTime;

	m_pModel->UpdateAnimation (iDeltaTime);

	{
		VECTOR3	vFrom, vTo, vUp;
		VERTTYPE	fFOV;
		vUp.x = f2vt(0.0f);
		vUp.y = f2vt(1.0f);
		vUp.z = f2vt(0.0f);
		vFrom.x = f2vt(0.0f);
		vFrom.y = f2vt(0.0f);
		vFrom.z = f2vt(400.0f);
		vTo.x = f2vt(0.0f);
		vTo.y = f2vt(0.0f);
		vTo.z = f2vt(0.0f);
		fFOV = f2vt(1.0f);
		MatrixLookAtRH(m_mView, vFrom, vTo, vUp);
		MatrixPerspectiveFovRH(m_mProjection, fFOV, f2vt(480/320), f2vt(4.0f), f2vt(500.0f), true);
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(m_mProjection.f);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m_mView.f);

	{
		VECTOR4 vLightDirection;
		VECTOR3 vPos;
		vPos.x = f2vt(0.0f);
		vPos.y = f2vt(-10.0f);
		vPos.z = f2vt(10.0f);
		vLightDirection.x = f2vt(0.0f);
		vLightDirection.y = f2vt(0.0f);
		vLightDirection.z = f2vt(1.0f);
		vLightDirection.w = 0;
	
		glLightfv(GL_LIGHT0, GL_POSITION, (VERTTYPE*)&vLightDirection);
	}
	
	m_pModel->Render (m_mView);
	//AppDisplayText->DisplayText(0, 6, 0.4f, RGBA(255,255,255,255), "frame: %3.f", m_pModel->m_fFrame);
	AppDisplayText->DisplayDefaultTitle("Scene", "", eDisplayTextLogoIMG);

	AppDisplayText->Flush();	
	
	return true;
}
