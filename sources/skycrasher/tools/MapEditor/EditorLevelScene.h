/*
 *  EditorLevelScene.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef EDITORLEVELSCENE_H_
#define EDITORLEVELSCENE_H_

#include "IOGResourceMgr.h"
#include "IOGSceneGraph.h"
#include "IOGLevelManager.h"
#include "IOGInputReceiver.h"
#include "IOGActorManager.h"
#include "IOGRenderer.h"
#include <ToolFramework.h>

enum CamModes
{
    CAMMODE_EDITOR,
    CAMMODE_GAME
};

class CEditorLevelScene
{
public:
	CEditorLevelScene();
	virtual ~CEditorLevelScene();

	// Initialize scene
	bool Init ();

	// Setup viewport
	void SetViewport (int _Width, int _Height);

	// Update controller
	void Update (unsigned long _ElapsedTime);

	// Render controller scene
	void RenderScene ();

	// Load level
	bool LoadLevel (const std::string& _LevelName);

	// Save level
	bool SaveLevel ();

	// Set editor mode
	void SetEditMode (TerrainEditMode _Mode);

    // Setup new current node for placement.
    void SetNewCurrentNodeForPlacement(const char* _pModelAlias);

	// Place the current node
	void PlaceCurrentNode (const OGVec3& _vPos);

	// Update current actor's position
	void UpdateCurrentNodePosition (const OGVec3& _vPos);

	// Update level start position
	void UpdateLevelStartPosition (const OGVec3& _vPos);

	// Update level start position
	void UpdateLevelFinishPosition (const OGVec3& _vPos);

	// Update level active width
	void UpdateLevelActiveWidth (float _fWidthDiff);

	// Get terrain intersection position.
	bool GetTerrainIntersection (OGVec3& _vOutPos, int _mouseX, int _mouseY);

	// Pick actor
	void PickActor (int _mouseX, int _mouseY);

	// Update picked actor's position
	void UpdatePickedActorPosition (const OGVec3& _vDiff);

	// Update selected actor's rotation
	void UpdateSelectedActorRotation (const OGVec3& _vRotationDiff, bool _bCoarse);

	// Update selected actor's scaling
	void UpdateSelectedActorScaling (float _fScalingDiff, bool _bCoarse);

	// Reset selected actor's transform
	void ResetSelectedActorTansform ();

	// Delete picked actor
	void DeletePickedActor ();

	// Camera zoom
	void CameraZoom (float _fFactor);

	// Camera move
	void CameraMove (float _fX, float _fZ);

	// Set camera mode
	void CameraMode (CamModes mode);

	// Camera move
	void SetAABBMode (bool _bEnable) {m_bShowAABB = _bEnable;}

	// Get current level
	IOGLevel* GetLevel() {return m_pCurLevel;}

private:

	// Get picking ray
	void GetMousePickingRay (OGVec3& _vPos, OGVec3& _vRay, int _mouseX, int _mouseY);

    // Render scene helpers.
    void RenderHelpers();

private:
		
	IOGResourceMgr*		m_pResourceMgr;
	IOGSceneGraph*		m_pSg;
	IOGRenderer*		m_pRenderer;
	IOGCamera*			m_pCamera;
	IOGActorManager*	m_pActorMgr;
	IOGLevelManager*	m_pLevelMgr;

	IOGLevel*	    m_pCurLevel;
	OGMatrix			m_mProjection; 
	OGMatrix			m_mView;

	IOGActor*		m_pCurActor;
	IOGActor*		m_pPickedActor;

	OGVec3			m_vCurRotation;
	OGVec3			m_vCurScaling;
	OGActorType		m_CurActorType;
	std::string		m_CurModelAlias;
	float			m_fAirBotHeight;
	float	        m_fCameraDistance;
	bool	        m_bShowAABB;
    bool            m_bInited;
    float			m_fFineAngleStep;
    float			m_fCoarseAngleStep;

	int				m_ResX;
	int				m_ResY;
	TerrainEditMode	m_EditorMode;

    CamModes        m_CamMode;
};

#endif
