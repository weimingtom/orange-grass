/*
 *  OGAppSettings.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "Game.h"
#include "ogappsettings.h"


COGAppSettings::COGAppSettings()
{
	m_bInitialized = false;
	m_pReader = GetSettingsReader();
	m_pGlobalVars = GetGlobalVars();
}


COGAppSettings::~COGAppSettings()
{
}


// read settings file.
bool COGAppSettings::Init (const std::string& _File)
{
	if (m_bInitialized)
		return true;

	IOGSettingsSource* pSource = m_pReader->OpenSource(GetResourceMgr()->GetFullPath(_File));
	if (!pSource)
		return false;

	IOGGroupNode* pRoot = m_pReader->OpenGroupNode(pSource, NULL, "Settings");
	IOGGroupNode* pViewNode = m_pReader->OpenGroupNode(pSource, pRoot, "View");
	if (pViewNode != NULL)
	{
		int Landscape = m_pReader->ReadIntParam(pViewNode, "landscape");
		m_pGlobalVars->SetIVar("landscape", Landscape);

		std::string Profile = m_pReader->ReadStringParam(pViewNode, "profile");
		m_pGlobalVars->SetSVar("profile", Profile);

		m_pReader->CloseGroupNode(pViewNode);
	}
	IOGGroupNode* pGameNode = m_pReader->OpenGroupNode(pSource, pRoot, "Game");
	if (pGameNode != NULL)
	{
		IOGGroupNode* pLevelsNode = m_pReader->OpenGroupNode(pSource, pGameNode, "Levels");
		if (pLevelsNode)
		{
			IOGGroupNode* pLevelNode = m_pReader->OpenGroupNode(pSource, pLevelsNode, "Level");
			while (pLevelNode)
			{
				IOGLevelParams level;
				level.alias = m_pReader->ReadStringParam(pLevelNode, "alias");
				level.player_actor = m_pReader->ReadStringParam(pLevelNode, "player");
				level.weapon = m_pReader->ReadStringParam(pLevelNode, "weapon");
				GetGameSequence()->AddLevel(level);
				pLevelNode = m_pReader->ReadNextNode(pLevelNode);
			}
			m_pReader->CloseGroupNode(pLevelsNode);
		}
		m_pReader->CloseGroupNode(pGameNode);
	}
	m_pReader->CloseGroupNode(pRoot);
	m_pReader->CloseSource(pSource);

	return true;
}


// read screen mode settings file.
bool COGAppSettings::InitScreenMode ()
{
	if (m_bInitialized)
		return true;

	IOGSettingsSource* pSource = m_pReader->OpenSource(GetResourceMgr()->GetUIPath("view.xml"));
	if (!pSource)
		return false;

	IOGGroupNode* pRoot = m_pReader->OpenGroupNode(pSource, NULL, "Settings");
	IOGGroupNode* pViewNode = m_pReader->OpenGroupNode(pSource, pRoot, "View");
	if (pViewNode != NULL)
	{
		int ViewWidth = m_pReader->ReadIntParam(pViewNode, "view_width");
		m_pGlobalVars->SetIVar("view_width", ViewWidth);

		int ViewHeight = m_pReader->ReadIntParam(pViewNode, "view_height");
		m_pGlobalVars->SetIVar("view_height", ViewHeight);

		float fZNear = m_pReader->ReadFloatParam(pViewNode, "z_near");
		m_pGlobalVars->SetFVar("z_near", fZNear);

		float fZFar = m_pReader->ReadFloatParam(pViewNode, "z_far");
		m_pGlobalVars->SetFVar("z_far", fZFar);

		float fFOV = m_pReader->ReadFloatParam(pViewNode, "FOV");
		m_pGlobalVars->SetFVar("FOV", fFOV);

		float fViewDist = m_pReader->ReadFloatParam(pViewNode, "view_distance");
		m_pGlobalVars->SetFVar("view_distance", fViewDist);

		m_pReader->CloseGroupNode(pViewNode);
	}
	IOGGroupNode* pCameraNode = m_pReader->OpenGroupNode(pSource, pRoot, "Camera");
	if (pCameraNode != NULL)
	{
		OGVec3 vCamOffset = m_pReader->ReadVec3Param(pCameraNode, "cam_offset_x", "cam_offset_y", "cam_offset_z");
		m_pGlobalVars->SetVec3Var("cam_offset", vCamOffset);

		OGVec3 vCamDir = m_pReader->ReadVec3Param(pCameraNode, "cam_dir_x", "cam_dir_y", "cam_dir_z");
		m_pGlobalVars->SetVec3Var("cam_dir", vCamDir);

		float fCamMargins = m_pReader->ReadFloatParam(pCameraNode, "cam_margins");
		m_pGlobalVars->SetFVar("cam_margins", fCamMargins);

		float fCamDistance = m_pReader->ReadFloatParam(pCameraNode, "cam_distance");
		m_pGlobalVars->SetFVar("cam_distance", fCamDistance);

		m_pReader->CloseGroupNode(pCameraNode);
	}

	m_pReader->CloseGroupNode(pRoot);
	m_pReader->CloseSource(pSource);

	m_bInitialized = true;
	return true;
}
