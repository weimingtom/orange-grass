/*
 *  ViewerScene.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef VIEWERSCENE_H_
#define VIEWERSCENE_H_

#include "IOGResourceMgr.h"
#include "IOGSceneGraph.h"
#include "IOGLevelManager.h"
#include "IOGInputReceiver.h"
#include "IOGActorManager.h"
#include "IOGRenderer.h"
#include <ToolFramework.h>


class CViewerScene
{
public:
	CViewerScene();
	virtual ~CViewerScene();

	// Initialize scene
	bool Init ();

	// Setup viewport
	void SetViewport (int _Width, int _Height);

	// Update controller
	void Update (unsigned long _ElapsedTime);

	// Render controller scene
	void RenderScene ();

    // Setup model.
    void SetupModel(const char* _pModelAlias);

    // Adjust model material.
    void AdjustMaterial(MtlType _type, float _val);

	// Camera zoom
	void CameraZoom (float _fFactor);
	
	// Camera rotate
	void CameraRotate (float _fAngleH, float _fAngleV);

	// Camera rotate horizontally
	void CameraRotateHor (float _fAngle);

	// Camera rotate vertically
	void CameraRotateVer (float _fAngle);

	// Set AABB mode
	void SetAABBMode (bool _bEnable) {m_bShowAABB = _bEnable;}

	// Set Grid mode
	void SetGridMode (bool _bEnable) {m_bShowGrid = _bEnable;}

    // Save changes.
    void SaveChanges();

private:

    // Render scene helpers.
    void RenderHelpers();

    // Convert actor type to group name.
	std::string ActorTypeToGroupName(OGActorType type);

private:
		
	IOGResourceMgr*		m_pResourceMgr;
	IOGSceneGraph*		m_pSg;
	IOGRenderer*		m_pRenderer;
	IOGCamera*			m_pCamera;
	IOGActorManager*	m_pActorMgr;

	OGMatrix			m_mProjection; 
	OGMatrix			m_mView;

	IOGActor*		m_pCurActor;

	float	        m_fCameraDistance;
	bool	        m_bShowAABB;
	bool	        m_bShowGrid;
    bool            m_bInited;

	int				m_ResX;
	int				m_ResY;
};

#endif