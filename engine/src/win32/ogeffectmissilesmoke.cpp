/*
 *  ogeffectmissilesmoke.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogeffectmissilesmoke.h"
#include "OrangeGrass.h"


float			COGEffectMissileSmoke::m_fAlphaFade;
float			COGEffectMissileSmoke::m_fInitialScale;
float			COGEffectMissileSmoke::m_fScaleInc;
unsigned int	COGEffectMissileSmoke::m_numVertsAtOnce;
float			COGEffectMissileSmoke::m_fRotateInc;
Vec4			COGEffectMissileSmoke::m_color;
std::string     COGEffectMissileSmoke::m_Texture;
unsigned int    COGEffectMissileSmoke::m_MappingId;
unsigned int    COGEffectMissileSmoke::m_GlowMappingId;


COGEffectMissileSmoke::~COGEffectMissileSmoke()
{
}


// Load params.
bool COGEffectMissileSmoke::LoadParams ()
{
	IOGSettingsReader* pReader = GetSettingsReader();

    IOGSettingsSource* pSource = pReader->OpenSource(GetResourceMgr()->GetFullPath("Effects/missilesmoke.xml"));
	if (!pSource)
		return false;

	IOGGroupNode* pRoot = pReader->OpenGroupNode(pSource, NULL, "Effect");
	if (pRoot)
	{
		m_fAlphaFade = pReader->ReadFloatParam(pRoot, "alpha_fade");
		m_fScaleInc = pReader->ReadFloatParam(pRoot, "scale_inc");
		m_fRotateInc = pReader->ReadFloatParam(pRoot, "rotate_inc");
		m_fInitialScale = pReader->ReadFloatParam(pRoot, "initial_scale");
		m_numVertsAtOnce = (unsigned int)pReader->ReadIntParam(pRoot, "particles_at_once");
		m_Texture = pReader->ReadStringParam(pRoot, "texture");
		m_MappingId = (unsigned int)pReader->ReadIntParam(pRoot, "mapping");
		m_GlowMappingId = (unsigned int)pReader->ReadIntParam(pRoot, "glow_mapping");
		m_color = pReader->ReadVec4Param(pRoot, "r", "g", "b", "a");
    	pReader->CloseGroupNode(pRoot);
	}
	pReader->CloseSource(pSource);
	return true;
}


// Initialize effect.
void COGEffectMissileSmoke::Init(OGEffectType _Type)
{
	m_pTexture = GetResourceMgr()->GetTexture(m_Texture);
	m_pMapping = m_pTexture->GetMapping(m_MappingId);
	m_pGlowMapping = m_pTexture->GetMapping(m_GlowMappingId);
    m_pMaterial = GetMaterialManager()->GetMaterial(OG_MAT_TEXTUREALPHABLEND);

	m_bPositionUpdated = false;
    m_BBList.reserve(60);

    m_Glow.bDirty = false;
    m_Glow.scale = 2.0f;
    m_Glow.angle = GetRandomRange(-314,314) * 0.01f;
    m_Glow.pVertices[0].c = Vec4(1.0f,1.0f,1.0f,0.6f);
    m_Glow.pVertices[1].c = Vec4(1.0f,1.0f,1.0f,0.6f);
    m_Glow.pVertices[2].c = Vec4(1.0f,1.0f,1.0f,0.6f);
    m_Glow.pVertices[3].c = Vec4(1.0f,1.0f,1.0f,0.6f);

    m_AABB.SetMinMax(Vec3(-1,-1,-1), Vec3(1,1,1));
}


// Update.
void COGEffectMissileSmoke::Update (unsigned long _ElapsedTime)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

    std::vector<ParticleFormat>::iterator iter = m_BBList.begin();
    while (iter != m_BBList.end())
    {
        ParticleFormat& particle = (*iter);
        if (particle.pVertices[0].c.w >= m_fAlphaFade)
        {
            particle.scale += m_fScaleInc;
            particle.angle += m_fRotateInc;
    		particle.pVertices[0].c.w -= m_fAlphaFade;
    		particle.pVertices[1].c.w -= m_fAlphaFade;
    		particle.pVertices[2].c.w -= m_fAlphaFade;
    		particle.pVertices[3].c.w -= m_fAlphaFade;
            ++iter;
        }
        else
        {
            iter = m_BBList.erase(iter);
            if (m_BBList.empty())
            {
                m_Status = OG_EFFECTSTATUS_INACTIVE;
                //m_pRenderer->GetLight()->DestroyPointLight(m_pLight);
                return;
            }
        }
    }

	if (m_Status == OG_EFFECTSTATUS_STARTED && m_bPositionUpdated && m_vCurPosition != m_vPrevPosition)
	{
		Vec3 vDir = m_vPrevPosition - m_vCurPosition;
		float fDist = vDir.length();
		vDir.normalize();

		for (unsigned int n = 0; n < m_numVertsAtOnce; ++n)
		{
			ParticleFormat particle;
			particle.offset = vDir * (fDist * (float)n);
			particle.scale = m_fInitialScale;
			particle.angle = rand() * 0.01f;
			particle.bDirty = true;
			particle.pVertices[0].c = m_color;
			particle.pVertices[1].c = m_color;
			particle.pVertices[2].c = m_color;
			particle.pVertices[3].c = m_color;
			m_BBList.push_back(particle);
		}
	}
}


// Update position.
void COGEffectMissileSmoke::UpdatePosition (const Vec3& _vPosition)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	if (!m_bPositionUpdated)
	{
		m_vCurPosition = _vPosition;
		m_vPrevPosition = _vPosition;
		m_bPositionUpdated = true;
	}
	else
	{
		m_vPrevPosition = m_vCurPosition;
		m_vCurPosition = _vPosition;
	}
}


// Render.
void COGEffectMissileSmoke::Render (const MATRIX& _mWorld)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

    MATRIX mId; 
    MatrixIdentity(mId);
    m_pRenderer->SetModelMatrix(mId);
	m_pRenderer->SetMaterial(m_pMaterial);
	m_pRenderer->SetTexture(m_pTexture);

    MATRIX mR;
	BBVert* pVert = NULL;
    std::vector<ParticleFormat>::iterator iter = m_BBList.begin();
    for (; iter != m_BBList.end(); ++iter)
    {
        ParticleFormat& particle = (*iter);
        if (particle.bDirty)
        {
            particle.offset += m_vCurPosition;
            particle.bDirty = false;
        }

        MatrixRotationAxis(mR, particle.angle, m_vCameraLook.x, m_vCameraLook.y, m_vCameraLook.z);

        Vec3 vSUp = m_vCameraUp * particle.scale;
		Vec3 vSRight = m_vCameraRight * particle.scale;

		pVert = &particle.pVertices[0];
        MatrixVecMultiply(pVert->p, vSRight + vSUp, mR);
		pVert->p += particle.offset;
        pVert->t.x = m_pMapping->t1.x; pVert->t.y = m_pMapping->t0.y;

		pVert = &particle.pVertices[1];
        MatrixVecMultiply(pVert->p, -vSRight + vSUp, mR);
		pVert->p += particle.offset;
        pVert->t.x = m_pMapping->t0.x; pVert->t.y = m_pMapping->t0.y;

		pVert = &particle.pVertices[2];
        MatrixVecMultiply(pVert->p, vSRight - vSUp, mR);
		pVert->p += particle.offset;
        pVert->t.x = m_pMapping->t1.x; pVert->t.y = m_pMapping->t1.y;

		pVert = &particle.pVertices[3];
        MatrixVecMultiply(pVert->p, -vSRight - vSUp, mR);
		pVert->p += particle.offset;
        pVert->t.x = m_pMapping->t0.x; pVert->t.y = m_pMapping->t1.y;

		m_pRenderer->DrawEffectBuffer(&particle.pVertices[0], 0, 4);
    }

    if (m_Status != OG_EFFECTSTATUS_STOPPED)
    {
        MatrixRotationAxis(mR, m_Glow.angle, m_vCameraLook.x, m_vCameraLook.y, m_vCameraLook.z);

        Vec3 vSUp = m_vCameraUp * m_Glow.scale;
        Vec3 vSRight = m_vCameraRight * m_Glow.scale;

        pVert = &m_Glow.pVertices[0];
        MatrixVecMultiply(pVert->p, vSRight + vSUp, mR);
        pVert->p += m_vCurPosition;
        pVert->t.x = m_pGlowMapping->t1.x; pVert->t.y = m_pGlowMapping->t0.y;

        pVert = &m_Glow.pVertices[1];
        MatrixVecMultiply(pVert->p, -vSRight + vSUp, mR);
        pVert->p += m_vCurPosition;
        pVert->t.x = m_pGlowMapping->t0.x; pVert->t.y = m_pGlowMapping->t0.y;

        pVert = &m_Glow.pVertices[2];
        MatrixVecMultiply(pVert->p, vSRight - vSUp, mR);
        pVert->p += m_vCurPosition;
        pVert->t.x = m_pGlowMapping->t1.x; pVert->t.y = m_pGlowMapping->t1.y;

        pVert = &m_Glow.pVertices[3];
        MatrixVecMultiply(pVert->p, -vSRight - vSUp, mR);
        pVert->p += m_vCurPosition;
        pVert->t.x = m_pGlowMapping->t0.x; pVert->t.y = m_pGlowMapping->t1.y;

        m_pRenderer->DrawEffectBuffer(&m_Glow.pVertices[0], 0, 4);
    }

    //if (m_pLight)
    //{
    //    m_pLight->vPosition = m_vCurPosition;
    //    m_pLight->vColor = Vec4(1, 0, 0, 1);
    //    m_pLight->fIntensity = 10.0f;
    //}
}


// Start.
void COGEffectMissileSmoke::Start ()
{
	m_Status = OG_EFFECTSTATUS_STARTED;
    //m_pLight = m_pRenderer->GetLight()->CreatePointLight();
    m_BBList.clear();
}


// Stop.
void COGEffectMissileSmoke::Stop ()
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	m_Status = OG_EFFECTSTATUS_STOPPED;
}
