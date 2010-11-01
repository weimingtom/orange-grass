/*
 *  ogeffectbonuspick.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogeffectbonuspick.h"
#include "OrangeGrass.h"


float COGEffectBonusPick::m_fAlphaInc;
float COGEffectBonusPick::m_fScaleInc;
float COGEffectBonusPick::m_fInitialScale;
std::string COGEffectBonusPick::m_Texture;
unsigned int COGEffectBonusPick::m_MappingId;


COGEffectBonusPick::~COGEffectBonusPick()
{
}


// Load params.
bool COGEffectBonusPick::LoadParams ()
{
	IOGSettingsReader* pReader = GetSettingsReader();

    IOGSettingsSource* pSource = pReader->OpenSource(GetResourceMgr()->GetFullPath("Effects/bonuspick.xml"));
	if (!pSource)
		return false;

	IOGGroupNode* pRoot = pReader->OpenGroupNode(pSource, NULL, "Effect");
	if (pRoot)
	{
		m_fAlphaInc = pReader->ReadFloatParam(pRoot, "alpha_inc");
		m_fScaleInc = pReader->ReadFloatParam(pRoot, "scale_inc");
		m_fInitialScale = pReader->ReadFloatParam(pRoot, "initial_scale");
		m_Texture = pReader->ReadStringParam(pRoot, "texture");
		m_MappingId = (unsigned int)pReader->ReadIntParam(pRoot, "mapping");
    	pReader->CloseGroupNode(pRoot);
	}
	pReader->CloseSource(pSource);
	return true;
}


// Initialize effect.
void COGEffectBonusPick::Init(OGEffectType _Type)
{
	m_pTexture = GetResourceMgr()->GetTexture(m_Texture);
    m_pMaterial = GetMaterialManager()->GetMaterial(OG_MAT_TEXTUREALPHABLEND);

	Vec4 color = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
    m_pWaveMapping = m_pTexture->GetMapping(m_MappingId);
    m_Wave.scale = m_fInitialScale;
    m_Wave.angle = 0.0f;
    m_Wave.offset = Vec3(0,0,0);
    m_Wave.pVertices[0].c = color;
    m_Wave.pVertices[0].t = Vec2(m_pWaveMapping->t1.x, m_pWaveMapping->t0.y);
    m_Wave.pVertices[1].c = color;
    m_Wave.pVertices[1].t = Vec2(m_pWaveMapping->t0.x, m_pWaveMapping->t0.y);
    m_Wave.pVertices[2].c = color;
    m_Wave.pVertices[2].t = Vec2(m_pWaveMapping->t1.x, m_pWaveMapping->t1.y);
    m_Wave.pVertices[3].c = color;
    m_Wave.pVertices[3].t = Vec2(m_pWaveMapping->t0.x, m_pWaveMapping->t1.y);

    m_AABB.SetMinMax(Vec3(-1,-1,-1), Vec3(1,1,1));
}


// Update.
void COGEffectBonusPick::Update (unsigned long _ElapsedTime)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

    if (m_Wave.pVertices[0].c.w >= m_fAlphaInc)
    {
        m_Wave.scale += m_fScaleInc;
        m_Wave.pVertices[0].c.w -= m_fAlphaInc;
        m_Wave.pVertices[1].c.w -= m_fAlphaInc;
        m_Wave.pVertices[2].c.w -= m_fAlphaInc;
        m_Wave.pVertices[3].c.w -= m_fAlphaInc;
    }
	else
	{
		m_Status = OG_EFFECTSTATUS_INACTIVE;
	}
}


// Render.
void COGEffectBonusPick::Render (const MATRIX& _mWorld, unsigned int _Frame)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

    MATRIX mId; 
    MatrixIdentity(mId);
    m_pRenderer->SetModelMatrix(mId);
	m_pRenderer->SetMaterial(m_pMaterial);
	m_pRenderer->SetTexture(m_pTexture);

    Vec3 vWaveUp = m_vCameraUp * m_Wave.scale;
    Vec3 vWaveRight = m_vCameraRight * m_Wave.scale;
    Vec3 vOffset = Vec3(_mWorld.f[12], _mWorld.f[13], _mWorld.f[14]);
    m_Wave.pVertices[0].p = vOffset + vWaveRight + vWaveUp;
    m_Wave.pVertices[1].p = vOffset - vWaveRight + vWaveUp;
    m_Wave.pVertices[2].p = vOffset + vWaveRight - vWaveUp;
    m_Wave.pVertices[3].p = vOffset - vWaveRight - vWaveUp;
	m_pRenderer->DrawEffectBuffer(&m_Wave.pVertices[0], 0, 4);
}


// Start.
void COGEffectBonusPick::Start ()
{
	m_Status = OG_EFFECTSTATUS_STARTED;
}


// Stop.
void COGEffectBonusPick::Stop ()
{
	m_Status = OG_EFFECTSTATUS_INACTIVE;
}
