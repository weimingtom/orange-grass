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


class CEditorLevelScene
{
public:
	CEditorLevelScene();
	virtual ~CEditorLevelScene();

	// Initialize scene
	virtual bool Init ();

	// Setup viewport
	virtual void SetViewport (int _Width, int _Height);

	// Update controller
	virtual void Update (unsigned long _ElapsedTime);

	// Render controller scene
	virtual void RenderScene ();

	// Load level
	virtual bool LoadLevel (const std::string& _LevelName);

	// Set editor mode
	virtual void SetEditMode (TerrainEditMode _Mode);

public:
		
	IOGResourceMgr*	m_pResourceMgr;
	IOGSceneGraph*	m_pSg;
	IOGRenderer*	m_pRenderer;
	IOGCamera*		m_pCamera;

	IOGLevel*	    m_pCurLevel;
	MATRIX			m_mProjection; 
	MATRIX			m_mView;

	IOGActor*		m_pCurActor;
	IOGActor*		m_pPickedActor;

	bool			m_bIntersectionFound = false;
	Vec3			m_vIntersection;
	Vec3			m_vCurRotation;
	Vec3			m_vCurScaling;
	OGActorType		m_CurActorType;
	std::string		m_CurModelAlias;
	float			m_fAirBotHeight;

	int				m_ResX;
	int				m_ResY;
	TerrainEditMode	m_EditorMode;
};

#endif
