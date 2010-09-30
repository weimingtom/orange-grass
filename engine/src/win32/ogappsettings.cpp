/*
 *  OGAppSettings.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogappsettings.h"


COGAppSettings::COGAppSettings()
{
	m_pReader = GetSettingsReader();
	m_pGlobalVars = GetGlobalVars();
}


COGAppSettings::~COGAppSettings()
{
}


// read settings file.
bool COGAppSettings::Init (const std::string& _File)
{
	IOGSettingsSource* pSource = m_pReader->OpenSource(GetResourceMgr()->GetFullPath(_File));
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
		Vec3 vCamOffset = m_pReader->ReadVec3Param(pCameraNode, "cam_offset_x", "cam_offset_y", "cam_offset_z");
		m_pGlobalVars->SetVec3Var("cam_offset", vCamOffset);

		Vec3 vCamDir = m_pReader->ReadVec3Param(pCameraNode, "cam_dir_x", "cam_dir_y", "cam_dir_z");
		m_pGlobalVars->SetVec3Var("cam_dir", vCamDir);

		float fCamMargins = m_pReader->ReadFloatParam(pCameraNode, "cam_margins");
		m_pGlobalVars->SetFVar("cam_margins", fCamMargins);

		float fCamDistance = m_pReader->ReadFloatParam(pCameraNode, "cam_distance");
		m_pGlobalVars->SetFVar("cam_distance", fCamDistance);

		m_pReader->CloseGroupNode(pCameraNode);
	}
	IOGGroupNode* pGameNode = m_pReader->OpenGroupNode(pSource, pRoot, "Game");
	if (pGameNode != NULL)
	{
		std::string level_0 = m_pReader->ReadStringParam(pGameNode, "level_0");
		m_pGlobalVars->SetSVar("level_0", level_0);

		std::string level_1 = m_pReader->ReadStringParam(pGameNode, "level_1");
		m_pGlobalVars->SetSVar("level_1", level_1);

		m_pReader->CloseGroupNode(pGameNode);
	}
	m_pReader->CloseGroupNode(pRoot);
	m_pReader->CloseSource(pSource);

	return true;
}
