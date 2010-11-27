/*
 *  ogeffectgauss.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogeffectgauss.h"
#include "OrangeGrass.h"


std::string COGEffectGauss::m_Texture = std::string("effects");
unsigned int COGEffectGauss::m_MappingStartId = 13;
unsigned int COGEffectGauss::m_MappingFinishId = 14;


COGEffectGauss::~COGEffectGauss()
{
}


// Initialize effect.
void COGEffectGauss::Init(OGEffectType _Type)
{
    m_bPosReady = false;
	m_pTexture = GetResourceMgr()->GetTexture(m_Texture);
    m_Blend = OG_BLEND_ALPHAADD;
    m_fSegment = 50.0f;
    m_fScale = 8.0f;
    m_fSpeed = 1.0f;
	m_color = Vec4(1.0f, 1.0f, 1.0f, 1.0f);

    m_Frames.reserve(m_MappingFinishId - m_MappingStartId + 1);
    for (unsigned int i = m_MappingStartId; i <= m_MappingFinishId; ++i)
    {
        m_Frames.push_back(m_pTexture->GetMapping(i));
    }

    m_AABB.SetMinMax(Vec3(-1,-1,-1), Vec3(1,1,1));
}


// Update.
void COGEffectGauss::Update (unsigned long _ElapsedTime)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE || !m_bPosReady)
		return;

    bool bAdd = false;
    float fNewSegScale = 0.0f;

    std::list<ParticleFormat>::iterator iter = m_BBList.begin();
    while (iter != m_BBList.end())
    {
        ParticleFormat& seg = (*iter);

        if (seg.pos == 0.0f && seg.scale < 1.0f)
        {
            float fAdd = m_fSpeed / m_fSegment;
            if (seg.scale + fAdd > 1.0f)
            {
                float fMove = seg.scale + fAdd - 1.0f;
                
                bAdd = true;
                fNewSegScale = fMove;

                if (ScrollSegment(seg, fMove))
                {
                    iter = m_BBList.erase(iter);
                    continue;
                }
            }
            else
            {
                seg.scale += fAdd;
                seg.start -= fAdd;
            }
        }
        else
        {
            if (seg.pos == 0.0f && m_fSpeed > 0.0f)
            {
                bAdd = true;
                fNewSegScale = (m_fSpeed / m_fSegment);
            }

            if (ScrollSegment(seg, m_fSpeed))
            {
                iter = m_BBList.erase(iter);
                continue;
            }
        }

        UpdateSegment(seg);
        ++iter;
    }

    if (bAdd)
    {
        AddSegment(0.0f, fNewSegScale);
    }
}


// Render.
void COGEffectGauss::Render (const MATRIX& _mWorld)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE || !m_bPosReady)
		return;

    MATRIX mId; 
    MatrixIdentity(mId);
    m_pRenderer->SetModelMatrix(mId);
	m_pRenderer->SetBlend(m_Blend);
	m_pRenderer->SetTexture(m_pTexture);

    std::list<ParticleFormat>::iterator iter = m_BBList.begin();
    for (; iter != m_BBList.end(); ++iter)
    {
        ParticleFormat& particle = (*iter);
		m_pRenderer->DrawEffectBuffer(&particle.pVertices[0], 0, 4);
    }
}


// Start.
void COGEffectGauss::Start ()
{
	m_Status = OG_EFFECTSTATUS_STARTED;
}


// Stop.
void COGEffectGauss::Stop ()
{
    m_Status = OG_EFFECTSTATUS_INACTIVE;
    m_bPosReady = false;
}


// Set start and finish positions.
void COGEffectGauss::SetStartFinishPositions (const Vec3& _vStartPos, const Vec3& _vFinishPos)
{
    if (m_bPosReady)
        return;

    m_bPosReady = true;
    m_vStartPos = _vStartPos;
    m_vFinishPos = _vFinishPos;
    m_Direction = (m_vFinishPos - m_vStartPos);
    m_fRayLength = m_Direction.length();
    m_Direction.normalize();

    float fPos = 0.0f;
    bool bDone = false;
    while (!bDone)
    {
        bDone = AddSegment(fPos, 1.0f);
        fPos += m_fSegment;
    }
}


// Add segment. Returns true if last segment on ray.
bool COGEffectGauss::AddSegment (float _fPos, float _fScale)
{
    bool bLast = false;
    ParticleFormat newseg;
    newseg.pVertices[0].c = m_color;
    newseg.pVertices[1].c = m_color;
    newseg.pVertices[2].c = m_color;
    newseg.pVertices[3].c = m_color;
    newseg.frame = (unsigned int)GetRandomRange(0, m_Frames.size());
    newseg.pos = _fPos;
    newseg.start = 1.0f - _fScale;
    newseg.scale = _fScale;
    newseg.end = 1.0f;
    if (_fPos + m_fSegment > m_fRayLength)
    {
        newseg.end = (m_fRayLength - _fPos) / m_fSegment;
        newseg.scale = newseg.end;
        bLast = true;
    }
    m_BBList.push_back(newseg);
    return bLast;
}


// Scroll segment. Returns true if needs to be removed.
bool COGEffectGauss::ScrollSegment (ParticleFormat& _Segment, float _fScrollValue)
{
    _Segment.pos += _fScrollValue;
    _Segment.start = 0.0f;
    _Segment.scale = 1.0f;
    _Segment.end = 1.0f;
    if (_Segment.pos + m_fSegment > m_fRayLength)
    {
        _Segment.end = (m_fRayLength - _Segment.pos) / m_fSegment;
        _Segment.scale = _Segment.end;
    }
    if (_Segment.pos >= m_fRayLength)
    {
        return true;
    }
    return false;
}


// Update segment.
void COGEffectGauss::UpdateSegment (ParticleFormat& _Segment)
{
    Vec3 vStart = m_vStartPos + m_Direction * _Segment.pos;
    Vec3 vFinish = m_vStartPos + m_Direction * (_Segment.pos + m_fSegment * _Segment.scale);

    Vec3 vSUp = Vec3(0,0,-1) * m_fScale;
    Vec3 vSRight = Vec3(1,0,0) * m_fScale;

    _Segment.pVertices[0].p = vFinish + vSRight;
    _Segment.pVertices[1].p = vFinish - vSRight;
    _Segment.pVertices[2].p = vStart + vSRight;
    _Segment.pVertices[3].p = vStart - vSRight;

    IOGMapping* pMapping = m_Frames[_Segment.frame];
    float t0y = pMapping->t0.y + (pMapping->t1.y - pMapping->t0.y) * _Segment.start;
    float t1y = pMapping->t0.y + (pMapping->t1.y - pMapping->t0.y) * _Segment.end;
    _Segment.pVertices[0].t = Vec2(pMapping->t1.x, t1y);
    _Segment.pVertices[1].t = Vec2(pMapping->t0.x, t1y);
    _Segment.pVertices[2].t = Vec2(pMapping->t1.x, t0y);
    _Segment.pVertices[3].t = Vec2(pMapping->t0.x, t0y);
}
