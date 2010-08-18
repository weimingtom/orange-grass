/*
 *  OGLevel.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#define _CRT_SECURE_NO_WARNINGS
#include "OrangeGrass.h"
#include "oglevel.h"


COGLevel::COGLevel () : m_pTerrain(NULL)
{
    m_vStartPos = Vec3(150,0,-100);
	m_vFinishPos = Vec3(150,0,-1000);
	m_vLightDir = Vec3(0,1,0);
	m_vLightColor = Vec3(1,1,1);
    m_fActiveWidth = 200.0f;
}


COGLevel::~COGLevel ()
{
	Unload();
}


// load scene from file.
bool COGLevel::Load ()
{
	if (m_LoadState == OG_RESSTATE_UNKNOWN)
	{
		return false;
	}

    m_pTerrain = GetResourceMgr()->GetTerrain(m_ResourceAlias);
    if (m_pTerrain == NULL)
        return false;

    FILE* pIn = fopen(m_ResourceFile.c_str(), "rb");
    if (pIn == NULL)
    {
        GetSceneGraph()->GetLight()->SetDirection(Vec4(m_vLightDir.x, m_vLightDir.y, m_vLightDir.z, 0.0f));
        GetSceneGraph()->GetLight()->SetColor(Vec4(m_vLightColor.x, m_vLightColor.y, m_vLightColor.z, 1.0f));
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
        fclose(pIn);
        return false;
    }
    unsigned int ver = 0;
    fread(&ver, sizeof(unsigned int), 1, pIn);
    if (ver > GetLevelManager()->GetVersion())
    {
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
    GetSceneGraph()->GetLight()->SetDirection(Vec4(m_vLightDir.x, m_vLightDir.y, m_vLightDir.z, 0.0f));
    GetSceneGraph()->GetLight()->SetColor(Vec4(m_vLightColor.x, m_vLightColor.y, m_vLightColor.z, 1.0f));

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

		IOGActor* pActor = GetActorManager()->CreateActor(type, std::string(pAlias), vPos, vRot, vScale);
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

	GetResourceMgr()->ReleaseTerrain(m_pTerrain);
	m_pTerrain = NULL;
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
        return false;
    }

	Vec4 vL = GetSceneGraph()->GetLight()->GetDirection();
	Vec4 vC = GetSceneGraph()->GetLight()->GetColor();
	m_vLightDir = Vec3(vL.x, vL.y, vL.z);
	m_vLightColor = Vec3(vC.x, vC.y, vC.z);

    FILE* pOut = fopen(m_ResourceFile.c_str(), "wb");
    
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
    const std::vector<IOGActor*> actors = GetActorManager()->GetActorsList();
    unsigned int numActors = actors.size();
    fwrite(&numActors, sizeof(unsigned int), 1, pOut);
    for (unsigned int i = 0; i < numActors; ++i)
    {
        // actor's model alias
		const std::string& Alias = actors[i]->GetAlias();
		unsigned int AliasLen = Alias.length();
        fwrite(&AliasLen, sizeof(unsigned int), 1, pOut);
		fwrite(Alias.c_str(), sizeof(char), AliasLen, pOut);

        // type
        OGActorType type = actors[i]->GetType();
        fwrite(&type, sizeof(OGActorType), 1, pOut);

        // position
        vVec = actors[i]->GetPhysicalObject()->GetPosition();
        fwrite(&vVec.x, sizeof(float), 1, pOut);
        fwrite(&vVec.y, sizeof(float), 1, pOut);
        fwrite(&vVec.z, sizeof(float), 1, pOut);

        // rotation
        vVec = actors[i]->GetPhysicalObject()->GetRotation();
        fwrite(&vVec.x, sizeof(float), 1, pOut);
        fwrite(&vVec.y, sizeof(float), 1, pOut);
        fwrite(&vVec.z, sizeof(float), 1, pOut);

        // scale
        vVec = actors[i]->GetPhysicalObject()->GetScaling();
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
