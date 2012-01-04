/*
 *  EffectViewerScene.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef EFFECTVIEWERSCENE_H_
#define EFFECTVIEWERSCENE_H_

#include "IOGResourceMgr.h"
#include "IOGSceneGraph.h"
#include "IOGLevelManager.h"
#include "IOGInputReceiver.h"
#include "IOGActorManager.h"
#include "IOGRenderer.h"
#include <ToolFramework.h>


class CEffectViewerScene
{
public:
	CEffectViewerScene();
	virtual ~CEffectViewerScene();

	// Initialize scene
	bool Init ();

	// Setup viewport
	void SetViewport (int _Width, int _Height);

	// Update controller
	void Update (unsigned long _ElapsedTime);

	// Render controller scene
	void RenderScene ();

    // Setup effect.
    void SetupEffect(const char* _pEffectAlias);

	// Camera zoom
	void CameraZoom (float _fFactor);

	// Set AABB mode
	void SetAABBMode (bool _bEnable) {m_bShowAABB = _bEnable;}

	// Set Grid mode
	void SetGridMode (bool _bEnable) {m_bShowGrid = _bEnable;}

private:

    // Render scene helpers.
    void RenderHelpers();

	// update camera
	void UpdateCamera();

private:
		
	IOGResourceMgr*		m_pResourceMgr;
	IOGSceneGraph*		m_pSg;
	IOGRenderer*		m_pRenderer;
	IOGCamera*			m_pCamera;
	IOGActorManager*	m_pActorMgr;

	OGMatrix			m_mProjection; 
	OGMatrix			m_mView;

	IOGEffect*			m_pCurEffect;
	IOGSgNode*			m_pCurNode;
	IOGPhysicalObject*	m_pCurPhysics;
	IOGPhysicalParams	m_PhysicalParams;

	float	        m_fCameraDistance;
	bool	        m_bShowAABB;
	bool	        m_bShowGrid;
    bool            m_bInited;

	int				m_ResX;
	int				m_ResY;
};

#endif
