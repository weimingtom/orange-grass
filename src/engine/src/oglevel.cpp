/*
 *  OGLevel.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "oglevel.h"
#include "ogresourcefile.h"


COGLevel::COGLevel () : m_pTerrain(NULL)
{
	m_pReader = GetSettingsReader();

	m_vStartPos = OGVec3(150,0,-100);
	m_vFinishPos = OGVec3(150,0,-1000);
    m_fActiveWidth = 200.0f;

	m_vLightDir = OGVec3(0,1,0);
	m_vLightAmbColor = OGVec3(1,1,1);
	m_vLightDifColor = OGVec3(1,1,1);
	m_vLightSpcColor = OGVec3(1,1,1);
	
	m_vFogColor = OGVec4(0.8f, 0.9f, 0.5f, 1.0f);
	m_fFogStart = 150.0f;
	m_fFogEnd = 300.0f;
	m_fFogDensity = 0.15f;
}


COGLevel::~COGLevel ()
{
	Unload();
}


// Load level configuration
bool COGLevel::LoadConfig (COGLevel::Cfg& _cfg)
{
	IOGSettingsSource* pSource = m_pReader->OpenSource(m_ResourceFile);
	if (!pSource)
	{
		OG_LOG_ERROR("Failed to load level config file %s", m_ResourceFile.c_str());
		return false;
	}

	IOGGroupNode* pLevelNode = m_pReader->OpenGroupNode(pSource, NULL, "Level");
	if (pLevelNode != NULL)
	{
		_cfg.terrain_file = GetResourceMgr()->GetFullPath(m_pReader->ReadStringParam(pLevelNode, "terrain_file"));
		_cfg.scene_file = GetResourceMgr()->GetFullPath(m_pReader->ReadStringParam(pLevelNode, "scene_file"));
		m_pReader->CloseGroupNode(pLevelNode);
	}

	m_pReader->CloseSource(pSource);
	return true;
}


// load scene from file.
bool COGLevel::Load ()
{
	switch (m_LoadState)
	{
	case OG_RESSTATE_UNKNOWN:
		return false;

	case OG_RESSTATE_LOADED:
        return true;

    case OG_RESSTATE_DEFINED:
        break;
	}

	Cfg cfg;
	if (!LoadConfig(cfg))
	{
        OG_LOG_ERROR("Failed to load level from config");
		return false;
	}

	m_SceneFile = cfg.scene_file;

    m_pTerrain = new COGTerrain();
	m_pTerrain->Init(std::string(""), cfg.terrain_file, m_ResourcePool);
	if (!m_pTerrain->Load())
    {
        OG_LOG_ERROR("Failed to load terrain from %s", cfg.terrain_file.c_str());
        return false;
    }
	IOGSgNode* pTerrainSg = GetSceneGraph()->CreateLandscapeNode(m_pTerrain);
	GetSceneGraph()->AddLandscapeNode(pTerrainSg);

    COGResourceFile level_file;
    level_file.OpenForRead(cfg.scene_file);
    if (!level_file.IsOpenForRead())
    {
		OG_LOG_WARNING("No level scene found in file %s", cfg.scene_file.c_str());

		IOGLight* pMainLight = GetRenderer()->GetLightMgr()->CreateLight();
		pMainLight->type = OG_LIGHT_DIRECTIONAL;
		pMainLight->vPosition = m_vLightDir;
		pMainLight->fIntensity = 100.0f;
		pMainLight->vAmbientColor = OGVec4(m_vLightAmbColor.x, m_vLightAmbColor.y, m_vLightAmbColor.z, 1.0f);
		pMainLight->vDiffuseColor = OGVec4(m_vLightDifColor.x, m_vLightDifColor.y, m_vLightDifColor.z, 1.0f);
		pMainLight->vSpecularColor = OGVec4(m_vLightSpcColor.x, m_vLightSpcColor.y, m_vLightSpcColor.z, 1.0f);

		GetRenderer()->GetFog()->SetColor(m_vFogColor);
		GetRenderer()->GetFog()->SetStart(m_fFogStart);
		GetRenderer()->GetFog()->SetEnd(m_fFogEnd);
		GetRenderer()->GetFog()->SetDensity(m_fFogDensity);
		GetPhysics()->SetLevelBorders(m_vStartPos, m_vFinishPos, m_fActiveWidth);

	    m_LoadState = OG_RESSTATE_LOADED;
        return true;    
    }

    // Prolog: "SCN" + version
    char signature[4];
    level_file.Read(signature, 3);
    signature[3] = 0;
    if (strcmp(&signature[0], "SCN") != 0)
    {
		OG_LOG_ERROR("Level loading failure: signature mismatch");
        level_file.Close();
        return false;
    }
    unsigned int ver = 0;
    level_file.Read(ver);
    if (ver > GetLevelManager()->GetVersion())
    {
		OG_LOG_ERROR("Level loading failure: trying to load newer version %d while current is %d", ver, GetLevelManager()->GetVersion());
        level_file.Close();
        return false;
    }

    // Level start position
    level_file.Read(m_vStartPos);

    // Level finish position
    level_file.Read(m_vFinishPos);

    // Level light direction
    level_file.Read(m_vLightDir);

	// Ver.2 and higher
	if (ver == 2)
	{
		// Level active width
        level_file.Read(m_fActiveWidth);

		// Level light color
        level_file.Read(m_vLightAmbColor);
        m_vLightDifColor = m_vLightAmbColor;
        m_vLightSpcColor = m_vLightAmbColor;
	}
    else if (ver >= 3)
    {
		// Level active width
        level_file.Read(m_fActiveWidth);

		// Level ambient light color
        level_file.Read(m_vLightAmbColor);

		// Level diffuse light color
        level_file.Read(m_vLightDifColor);

		// Level specular light color
        level_file.Read(m_vLightSpcColor);

		// Level fog params
        level_file.Read(m_fFogStart);
        level_file.Read(m_fFogEnd);
        level_file.Read(m_fFogDensity);
        level_file.Read(m_vFogColor);
    }

    GetPhysics()->SetLevelBorders(m_vStartPos, m_vFinishPos, m_fActiveWidth);

	IOGLight* pMainLight = GetRenderer()->GetLightMgr()->CreateLight();
	pMainLight->type = OG_LIGHT_DIRECTIONAL;
	pMainLight->vPosition = m_vLightDir;
	pMainLight->fIntensity = 100.0f;
	pMainLight->vAmbientColor = OGVec4(m_vLightAmbColor.x, m_vLightAmbColor.y, m_vLightAmbColor.z, 1.0f);
	pMainLight->vDiffuseColor = OGVec4(m_vLightDifColor.x, m_vLightDifColor.y, m_vLightDifColor.z, 1.0f);
	pMainLight->vSpecularColor = OGVec4(m_vLightSpcColor.x, m_vLightSpcColor.y, m_vLightSpcColor.z, 1.0f);

	GetRenderer()->GetFog()->SetColor(m_vFogColor);
	GetRenderer()->GetFog()->SetStart(m_fFogStart);
	GetRenderer()->GetFog()->SetEnd(m_fFogEnd);
	GetRenderer()->GetFog()->SetDensity(m_fFogDensity);

    unsigned int numActors = 0;
    level_file.Read(numActors);
    for (unsigned int i = 0; i < numActors; ++i)
    {
        // actor's model alias
        char pAlias[OG_MAX_PATH];
        unsigned int AliasLen = 0;
        level_file.Read(AliasLen);
        level_file.Read(&pAlias[0], AliasLen);
        pAlias[AliasLen] = 0;

        // type
        OGActorType type = OG_ACTOR_NONE;
        level_file.Read(type);

        // position
        OGVec3 vPos;
        level_file.Read(vPos);

        // rotation
        OGVec3 vRot;
        level_file.Read(vRot);

        // scaling
        OGVec3 vScale;
        level_file.Read(vScale);

		IOGActor* pActor = GetActorManager()->CreateActor(std::string(pAlias), vPos, vRot, vScale);
        GetActorManager()->AddActor(pActor);
    }

    level_file.Close();

	m_LoadState = OG_RESSTATE_LOADED;
    return true;    
}


// Unload resource.
void COGLevel::Unload ()
{
	if (m_LoadState != OG_RESSTATE_LOADED)
	{
		return;
	}

	if (m_pTerrain)
	{
		m_pTerrain->Unload();
		OG_SAFE_DELETE(m_pTerrain);
	}
	GetActorManager()->Clear();
	GetSceneGraph()->Clear();
	GetPhysics()->Clear();
    GetRenderer()->GetLightMgr()->Clear();

	m_LoadState = OG_RESSTATE_DEFINED;
}

	
// save level.
bool COGLevel::Save ()
{
    if (m_LoadState != OG_RESSTATE_LOADED)
    {
		OG_LOG_WARNING("Level saving failure: level is not loaded");
        return false;
    }
	
	IOGLight* pMainLight = GetRenderer()->GetLightMgr()->GetLight(0);
	m_vLightDir = pMainLight->vPosition;
	m_vLightAmbColor = OGVec3(pMainLight->vAmbientColor.x, pMainLight->vAmbientColor.y, pMainLight->vAmbientColor.z);
	m_vLightDifColor = OGVec3(pMainLight->vDiffuseColor.x, pMainLight->vDiffuseColor.y, pMainLight->vDiffuseColor.z);
	m_vLightSpcColor = OGVec3(pMainLight->vSpecularColor.x, pMainLight->vSpecularColor.y, pMainLight->vSpecularColor.z);

    m_fFogStart = GetRenderer()->GetFog()->GetStart();
    m_fFogEnd = GetRenderer()->GetFog()->GetEnd();
    m_fFogDensity = GetRenderer()->GetFog()->GetDensity();
    m_vFogColor = GetRenderer()->GetFog()->GetColor();

    FILE* pOut = fopen(m_SceneFile.c_str(), "wb");
	if (pOut == NULL)
	{
		OG_LOG_WARNING("Level saving failure: cannot open file %s for write", m_SceneFile.c_str());
		return false;
	}
    
    // Prolog: "SCN" + version
    fwrite("SCN", sizeof(char), 3, pOut);
    unsigned int ver = GetLevelManager()->GetVersion();
    fwrite(&ver, sizeof(unsigned int), 1, pOut);
    
    OGVec3 vVec;

    // Level start position
    fwrite(&m_vStartPos.x, sizeof(float), 1, pOut);
    fwrite(&m_vStartPos.y, sizeof(float), 1, pOut);
    fwrite(&m_vStartPos.z, sizeof(float), 1, pOut);

    // Level finish position
    fwrite(&m_vFinishPos.x, sizeof(float), 1, pOut);
    fwrite(&m_vFinishPos.y, sizeof(float), 1, pOut);
    fwrite(&m_vFinishPos.z, sizeof(float), 1, pOut);

    // Lighting direction
    fwrite(&m_vLightDir.x, sizeof(float), 1, pOut);
    fwrite(&m_vLightDir.y, sizeof(float), 1, pOut);
    fwrite(&m_vLightDir.z, sizeof(float), 1, pOut);

	// Level active width
	fwrite(&m_fActiveWidth, sizeof(float), 1, pOut);

	// Level ambient light color
	fwrite(&m_vLightAmbColor.x, sizeof(float), 1, pOut);
	fwrite(&m_vLightAmbColor.y, sizeof(float), 1, pOut);
	fwrite(&m_vLightAmbColor.z, sizeof(float), 1, pOut);

    // Level diffuse light color
    fwrite(&m_vLightDifColor.x, sizeof(float), 1, pOut);
    fwrite(&m_vLightDifColor.y, sizeof(float), 1, pOut);
    fwrite(&m_vLightDifColor.z, sizeof(float), 1, pOut);

    // Level specular light color
    fwrite(&m_vLightSpcColor.x, sizeof(float), 1, pOut);
    fwrite(&m_vLightSpcColor.y, sizeof(float), 1, pOut);
    fwrite(&m_vLightSpcColor.z, sizeof(float), 1, pOut);

    // Level fog params
    fwrite(&m_fFogStart, sizeof(float), 1, pOut);
    fwrite(&m_fFogEnd, sizeof(float), 1, pOut);
    fwrite(&m_fFogDensity, sizeof(float), 1, pOut);
    fwrite(&m_vFogColor.x, sizeof(float), 1, pOut);
    fwrite(&m_vFogColor.y, sizeof(float), 1, pOut);
    fwrite(&m_vFogColor.z, sizeof(float), 1, pOut);
    fwrite(&m_vFogColor.w, sizeof(float), 1, pOut);

    // actors list
	const IOGActorManager::TActorsList& actors = GetActorManager()->GetActorsList();
    unsigned int numActors = actors.size();
    fwrite(&numActors, sizeof(unsigned int), 1, pOut);
	IOGActorManager::TActorsList::const_iterator iter = actors.begin();
    for (; iter != actors.end(); ++iter)
    {
        // actor's model alias
		const std::string& Alias = (*iter)->GetAlias();
		unsigned int AliasLen = Alias.length();
        fwrite(&AliasLen, sizeof(unsigned int), 1, pOut);
		fwrite(Alias.c_str(), sizeof(char), AliasLen, pOut);

        // type
        OGActorType type = (*iter)->GetType();
        fwrite(&type, sizeof(OGActorType), 1, pOut);

        // position
        vVec = (*iter)->GetPhysicalObject()->GetPosition();
        fwrite(&vVec.x, sizeof(float), 1, pOut);
        fwrite(&vVec.y, sizeof(float), 1, pOut);
        fwrite(&vVec.z, sizeof(float), 1, pOut);

        // rotation
        vVec = (*iter)->GetPhysicalObject()->GetRotation();
        fwrite(&vVec.x, sizeof(float), 1, pOut);
        fwrite(&vVec.y, sizeof(float), 1, pOut);
        fwrite(&vVec.z, sizeof(float), 1, pOut);

        // scale
        vVec = (*iter)->GetPhysicalObject()->GetScaling();
        fwrite(&vVec.x, sizeof(float), 1, pOut);
        fwrite(&vVec.y, sizeof(float), 1, pOut);
        fwrite(&vVec.z, sizeof(float), 1, pOut);
    }
    fclose(pOut);

    return true;
}


// get associated terrain.
IOGTerrain* COGLevel::GetTerrain ()
{
    return m_pTerrain;
}


// get level start position.
const OGVec3& COGLevel::GetStartPosition () const
{
	return m_vStartPos;
}


// get level start finish.
const OGVec3& COGLevel::GetFinishPosition () const
{
	return m_vFinishPos;
}


// set level start position.
void COGLevel::SetStartPosition (const OGVec3& _Pos)
{
    m_vStartPos = _Pos;
}


// set level start finish.
void COGLevel::SetFinishPosition (const OGVec3& _Pos)
{
    m_vFinishPos = _Pos;
}
