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


COGLevel::COGLevel () : m_pTerrain(NULL)
{
	m_pReader = GetSettingsReader();

	m_vStartPos = Vec3(150,0,-100);
	m_vFinishPos = Vec3(150,0,-1000);
    m_fActiveWidth = 200.0f;

	m_vLightDir = Vec3(0,1,0);
	m_vLightColor = Vec3(1,1,1);
	
	m_vFogColor = Vec4(0.8f, 0.9f, 0.5f, 1.0f);
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
	}

	Cfg cfg;
	if (!LoadConfig(cfg))
	{
        OG_LOG_ERROR("Failed to load level from config");
		return false;
	}

	m_SceneFile = cfg.scene_file;

    m_pTerrain = new COGTerrain();
	m_pTerrain->Init(std::string(""), cfg.terrain_file);
	if (!m_pTerrain->Load())
    {
        OG_LOG_ERROR("Failed to load terrain from %s", cfg.terrain_file.c_str());
        return false;
    }
	IOGSgNode* pTerrainSg = GetSceneGraph()->CreateLandscapeNode(m_pTerrain);
	GetSceneGraph()->AddLandscapeNode(pTerrainSg);

    FILE* pIn = fopen(cfg.scene_file.c_str(), "rb");
    if (pIn == NULL)
    {
		OG_LOG_WARNING("No level scene found in file %s", cfg.scene_file.c_str());

		IOGLight* pMainLight = GetRenderer()->GetLightMgr()->CreateLight();
		pMainLight->type = OG_LIGHT_DIRECTIONAL;
		pMainLight->vPosition = m_vLightDir;
		pMainLight->fIntensity = 100.0f;
		pMainLight->vAmbientColor = Vec4(m_vLightColor.x, m_vLightColor.y, m_vLightColor.z, 1.0f);
		pMainLight->vDiffuseColor = Vec4(m_vLightColor.x, m_vLightColor.y, m_vLightColor.z, 1.0f);
		pMainLight->vSpecularColor = Vec4(m_vLightColor.x, m_vLightColor.y, m_vLightColor.z, 1.0f);

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
    fread(&signature[0], sizeof(char), 3, pIn);
    signature[3] = 0;
    if (strcmp(&signature[0], "SCN") != 0)
    {
		OG_LOG_ERROR("Level loading failure: signature mismatch");
        fclose(pIn);
        return false;
    }
    unsigned int ver = 0;
    fread(&ver, sizeof(unsigned int), 1, pIn);
    if (ver > GetLevelManager()->GetVersion())
    {
		OG_LOG_ERROR("Level loading failure: trying to load newer version %d while current is %d", ver, GetLevelManager()->GetVersion());
        fclose(pIn);
        return false;
    }

    // Level start position
    fread(&m_vStartPos.x, sizeof(float), 1, pIn);
    fread(&m_vStartPos.y, sizeof(float), 1, pIn);
    fread(&m_vStartPos.z, sizeof(float), 1, pIn);

    // Level finish position
    fread(&m_vFinishPos.x, sizeof(float), 1, pIn);
    fread(&m_vFinishPos.y, sizeof(float), 1, pIn);
    fread(&m_vFinishPos.z, sizeof(float), 1, pIn);

    // Level light direction
    fread(&m_vLightDir.x, sizeof(float), 1, pIn);
    fread(&m_vLightDir.y, sizeof(float), 1, pIn);
    fread(&m_vLightDir.z, sizeof(float), 1, pIn);

	// Ver.2 and higher
	if (ver >= 2)
	{
		// Level active width
	    fread(&m_fActiveWidth, sizeof(float), 1, pIn);

		// Level light color
		fread(&m_vLightColor.x, sizeof(float), 1, pIn);
		fread(&m_vLightColor.y, sizeof(float), 1, pIn);
		fread(&m_vLightColor.z, sizeof(float), 1, pIn);
	}

    GetPhysics()->SetLevelBorders(m_vStartPos, m_vFinishPos, m_fActiveWidth);

	IOGLight* pMainLight = GetRenderer()->GetLightMgr()->CreateLight();
	pMainLight->type = OG_LIGHT_DIRECTIONAL;
	pMainLight->vPosition = m_vLightDir;
	pMainLight->fIntensity = 100.0f;
	pMainLight->vAmbientColor = Vec4(m_vLightColor.x, m_vLightColor.y, m_vLightColor.z, 1.0f);
	pMainLight->vDiffuseColor = Vec4(m_vLightColor.x, m_vLightColor.y, m_vLightColor.z, 1.0f);
	pMainLight->vSpecularColor = Vec4(m_vLightColor.x, m_vLightColor.y, m_vLightColor.z, 1.0f);

	GetRenderer()->GetFog()->SetColor(m_vFogColor);
	GetRenderer()->GetFog()->SetStart(m_fFogStart);
	GetRenderer()->GetFog()->SetEnd(m_fFogEnd);
	GetRenderer()->GetFog()->SetDensity(m_fFogDensity);

    unsigned int numActors = 0;
    fread(&numActors, sizeof(unsigned int), 1, pIn);
    for (unsigned int i = 0; i < numActors; ++i)
    {
        // actor's model alias
        char pAlias[OG_MAX_PATH];
        unsigned int AliasLen = 0;
        fread(&AliasLen, sizeof(unsigned int), 1, pIn);
        fread(&pAlias[0], sizeof(char), AliasLen, pIn);
        pAlias[AliasLen] = 0;

        // type
        OGActorType type = OG_ACTOR_NONE;
        fread(&type, sizeof(OGActorType), 1, pIn);

        // position
        Vec3 vPos;
        fread(&vPos.x, sizeof(float), 1, pIn);
        fread(&vPos.y, sizeof(float), 1, pIn);
        fread(&vPos.z, sizeof(float), 1, pIn);

        // rotation
        Vec3 vRot;
        fread(&vRot.x, sizeof(float), 1, pIn);
        fread(&vRot.y, sizeof(float), 1, pIn);
        fread(&vRot.z, sizeof(float), 1, pIn);

        // scaling
        Vec3 vScale;
        fread(&vScale.x, sizeof(float), 1, pIn);
        fread(&vScale.y, sizeof(float), 1, pIn);
        fread(&vScale.z, sizeof(float), 1, pIn);

		IOGActor* pActor = GetActorManager()->CreateActor(std::string(pAlias), vPos, vRot, vScale);
        GetActorManager()->AddActor(pActor);
    }

    fclose(pIn);

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
	m_vLightColor = Vec3(pMainLight->vDiffuseColor.x, pMainLight->vDiffuseColor.y, pMainLight->vDiffuseColor.z);

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
    
    Vec3 vVec;

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

	// Level light color
	fwrite(&m_vLightColor.x, sizeof(float), 1, pOut);
	fwrite(&m_vLightColor.y, sizeof(float), 1, pOut);
	fwrite(&m_vLightColor.z, sizeof(float), 1, pOut);

    // actors list
    const std::list<IOGActor*>& actors = GetActorManager()->GetActorsList();
    unsigned int numActors = actors.size();
    fwrite(&numActors, sizeof(unsigned int), 1, pOut);
	std::list<IOGActor*>::const_iterator iter = actors.begin();
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
const Vec3& COGLevel::GetStartPosition () const
{
	return m_vStartPos;
}


// get level start finish.
const Vec3& COGLevel::GetFinishPosition () const
{
	return m_vFinishPos;
}


// set level start position.
void COGLevel::SetStartPosition (const Vec3& _Pos)
{
    m_vStartPos = _Pos;
}


// set level start finish.
void COGLevel::SetFinishPosition (const Vec3& _Pos)
{
    m_vFinishPos = _Pos;
}
