/*
 *  ogeffectcollision.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogeffectcollision.h"
#include "OrangeGrass.h"


unsigned int COGEffectCollision::m_MappingStartId;
unsigned int COGEffectCollision::m_MappingFinishId;
float COGEffectCollision::m_fFrameInc;
float COGEffectCollision::m_fInitialScale;
float COGEffectCollision::m_fScaleInc;
float COGEffectCollision::m_fRotateInc;
std::string COGEffectCollision::m_Texture;


COGEffectCollision::~COGEffectCollision()
{
}


// Load params.
bool COGEffectCollision::LoadParams ()
{
	IOGSettingsReader* pReader = GetSettingsReader();

    IOGSettingsSource* pSource = pReader->OpenSource(GetResourceMgr()->GetFullPath("Effects/collision.xml"));
	if (!pSource)
		return false;

	IOGGroupNode* pRoot = pReader->OpenGroupNode(pSource, NULL, "Effect");
	if (pRoot)
	{
		m_fFrameInc = pReader->ReadFloatParam(pRoot, "frame_inc");
		m_fScaleInc = pReader->ReadFloatParam(pRoot, "scale_inc");
		m_fRotateInc = pReader->ReadFloatParam(pRoot, "rotate_inc");
		m_fInitialScale = pReader->ReadFloatParam(pRoot, "initial_scale");
		m_Texture = pReader->ReadStringParam(pRoot, "texture");
		m_MappingStartId = (unsigned int)pReader->ReadIntParam(pRoot, "mapping_start");
		m_MappingFinishId = (unsigned int)pReader->ReadIntParam(pRoot, "mapping_finish");
    	pReader->CloseGroupNode(pRoot);
	}
	pReader->CloseSource(pSource);
	return true;
}


// Initialize effect.
void COGEffectCollision::Init(OGEffectType _Type)
{
    m_pLight = NULL;
	m_pTexture = GetResourceMgr()->GetTexture(m_Texture);
    m_Blend = OG_BLEND_ALPHABLEND;

    m_Frames.reserve(m_MappingFinishId - m_MappingStartId + 1);
    for (unsigned int i = m_MappingStartId; i <= m_MappingFinishId; ++i)
    {
        m_Frames.push_back(m_pTexture->GetMapping(i));
    }
    m_BB.bDirty = true;

    m_AABB.SetMinMax(Vec3(-1,-1,-1), Vec3(1,1,1));
}


// Update.
void COGEffectCollision::Update (unsigned long _ElapsedTime)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	Vec4 color = Vec4(1.0f, 1.0f, 1.0f, 1.0f);

    if (m_BB.bDirty)
    {
        m_BB.bDirty = false;
        m_BB.scale = m_fInitialScale;
        m_BB.frame = 0.0f;
        m_BB.angle = GetRandomRange(-314,314) * 0.01f;
        m_BB.pVertices[0].c = color;
        m_BB.pVertices[1].c = color;
        m_BB.pVertices[2].c = color;
        m_BB.pVertices[3].c = color;
    }
    else
    {
        if (m_BB.frame < m_Frames.size() - 1)
        {
            m_BB.scale += m_fScaleInc;
            m_BB.angle += m_fRotateInc;
            m_BB.frame += m_fFrameInc;
        }
        else
        {
            Stop();
            return;
        }
    }
}


// Render.
void COGEffectCollision::Render (const MATRIX& _mWorld)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

    MATRIX mId; 
    MatrixIdentity(mId);
    m_pRenderer->SetModelMatrix(mId);
	m_pRenderer->SetBlend(m_Blend);
	m_pRenderer->SetTexture(m_pTexture);

    Vec3 vSUp = m_vCameraUp * m_BB.scale;
    Vec3 vSRight = m_vCameraRight * m_BB.scale;

    MATRIX mR;
    MatrixRotationAxis(mR, m_BB.angle, m_vCameraLook.x, m_vCameraLook.y, m_vCameraLook.z);

    MatrixVecMultiply(m_BB.pVertices[0].p, vSRight + vSUp, mR);
    MatrixVecMultiply(m_BB.pVertices[1].p, -vSRight + vSUp, mR);
    MatrixVecMultiply(m_BB.pVertices[2].p, vSRight - vSUp, mR);
    MatrixVecMultiply(m_BB.pVertices[3].p, -vSRight - vSUp, mR);

    Vec3 vOffset = Vec3(_mWorld.f[12], _mWorld.f[13], _mWorld.f[14]);
    m_BB.pVertices[0].p += vOffset;
    m_BB.pVertices[1].p += vOffset;
    m_BB.pVertices[2].p += vOffset;
    m_BB.pVertices[3].p += vOffset;

    IOGMapping* pMapping = m_Frames[(unsigned int)m_BB.frame];
    m_BB.pVertices[0].t = Vec2(pMapping->t1.x, pMapping->t0.y);
    m_BB.pVertices[1].t = Vec2(pMapping->t0.x, pMapping->t0.y);
    m_BB.pVertices[2].t = Vec2(pMapping->t1.x, pMapping->t1.y);
    m_BB.pVertices[3].t = Vec2(pMapping->t0.x, pMapping->t1.y);

    m_pRenderer->DrawEffectBuffer(&m_BB.pVertices[0], 0, 4);

    if (m_pLight)
    {
        m_pLight->vPosition = vOffset;
        m_pLight->fIntensity = ((m_Frames.size()-(unsigned int)m_BB.frame) * 2.0f);
    }
}


// Start.
void COGEffectCollision::Start ()
{
	m_Status = OG_EFFECTSTATUS_STARTED;
    m_BB.bDirty = true;
    m_pLight = m_pRenderer->GetLightMgr()->CreateLight();
    if (m_pLight)
    {
        m_pLight->vDiffuseColor = Vec4(1, 1, 0, 1);
        m_pLight->vAmbientColor = Vec4(1, 1, 0, 1);
        m_pLight->vSpecularColor = Vec4(1, 1, 0, 1);
        m_pLight->fIntensity = 20.0f;
    }
}


// Stop.
void COGEffectCollision::Stop ()
{
	m_Status = OG_EFFECTSTATUS_INACTIVE;
    m_BB.bDirty = true;
    if (m_pLight)
    {
        m_pRenderer->GetLightMgr()->DestroyLight(m_pLight);
        m_pLight = NULL;
    }
}
