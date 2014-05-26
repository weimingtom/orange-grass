/*
 * OrangeGrass
 * Copyright (C) 2009 Vyacheslav Bogdanov.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/lgpl-3.0-standalone.html>.
 */
#include "ogemitterscrollingray.h"
#include "OrangeGrass.h"


std::string COGEmitterScrollingRay::s_Alias = std::string("scrolling_ray");
OGEmitterType COGEmitterScrollingRay::s_Type = OG_EMITTER_SCROLLINGRAY;


COGEmitterScrollingRay::COGEmitterScrollingRay()
{
    m_pVBO = NULL;

    m_Texture = std::string("effects");
    m_MappingStartId = 13;
    m_MappingFinishId = 14;
    m_color = OGVec4(1.0f, 1.0f, 1.0f, 1.0f);
    m_fSegment = 50.0f;
    m_fScale = 8.0f;
    m_fSpeed = 1.0f;

    AddStringParam("texture", &m_Texture);
    AddIntParam("mapping_start", &m_MappingStartId);
    AddIntParam("mapping_finish", &m_MappingFinishId);
    AddFloatParam("segment", &m_fSegment);
    AddFloatParam("scale", &m_fScale);
    AddFloatParam("speed", &m_fSpeed);
    AddColorParam("color", &m_color);
}


COGEmitterScrollingRay::~COGEmitterScrollingRay()
{
    OG_SAFE_DELETE(m_pVBO);
}


// Initialize emitter.
void COGEmitterScrollingRay::Init(IOGGroupNode* _pNode)
{
    LoadParams(_pNode);

    m_pTexture = GetResourceMgr()->GetTexture(OG_RESPOOL_GAME, m_Texture);
    m_Blend = OG_BLEND_ALPHAONE;
    m_pVBO = m_pRenderer->CreateDynVertexBuffer(2*60);

    m_bPositionUpdated = false;
    m_bPosReady = false;

    m_Frames.reserve(m_MappingFinishId - m_MappingStartId + 1);
    for (unsigned int i = m_MappingStartId; i <= m_MappingFinishId; ++i)
    {
        m_Frames.push_back(m_pTexture->GetMapping(i));
    }
}


// Update.
void COGEmitterScrollingRay::Update (unsigned long _ElapsedTime)
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
                    GetEffectsManager()->ReleaseParticle(seg.verts);
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
                GetEffectsManager()->ReleaseParticle(seg.verts);
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
void COGEmitterScrollingRay::Render (const OGMatrix& _mWorld, const OGVec3& _vLook, const OGVec3& _vUp, const OGVec3& _vRight, OGRenderPass _Pass)
{
    if (m_Status == OG_EFFECTSTATUS_INACTIVE || !m_bPosReady)
        return;

    unsigned int vertOffset = 0;
    m_pVBO->Map();
    std::list<ParticleFormat>::iterator iter = m_BBList.begin();
    for (; iter != m_BBList.end(); ++iter)
    {
        ParticleFormat& particle = (*iter);
        BBVert* pVert = (*particle.verts);
        m_pVBO->Update(vertOffset, pVert, 4*sizeof(BBVert));
        vertOffset += 4*sizeof(BBVert);
    }
    m_pVBO->Unmap();
    m_pRenderer->RenderEffect(m_pTexture, m_pVBO, m_Blend, OG_SHADER_COLOREFFECT, _Pass);
}


// Start.
void COGEmitterScrollingRay::Start ()
{
    m_Status = OG_EFFECTSTATUS_STARTED;
}


// Stop.
void COGEmitterScrollingRay::Stop ()
{
    if (m_Status == OG_EFFECTSTATUS_INACTIVE)
        return;

    for(auto it = m_BBList.begin(); it != m_BBList.end(); ++it)
    {
        GetEffectsManager()->ReleaseParticle(it->verts);
    }
    m_BBList.clear();

    m_bPosReady = false;
    m_Status = OG_EFFECTSTATUS_INACTIVE;
}


// Set start and finish positions.
void COGEmitterScrollingRay::SetStartFinishPositions (const OGVec3& _vStartPos, const OGVec3& _vFinishPos)
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
bool COGEmitterScrollingRay::AddSegment (float _fPos, float _fScale)
{
    bool bLast = false;
    ParticleFormat newseg;
    newseg.verts = GetEffectsManager()->AddParticle();
    BBVert* pV = (*newseg.verts);
    pV[0].c = m_color;
    pV[1].c = m_color;
    pV[2].c = m_color;
    pV[3].c = m_color;
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
bool COGEmitterScrollingRay::ScrollSegment (ParticleFormat& _Segment, float _fScrollValue)
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
void COGEmitterScrollingRay::UpdateSegment (ParticleFormat& _Segment)
{
    OGVec3 vStart = m_vStartPos + m_Direction * _Segment.pos;
    OGVec3 vFinish = m_vStartPos + m_Direction * (_Segment.pos + m_fSegment * _Segment.scale);
    OGVec3 vSRight = OGVec3(1,0,0) * m_fScale;

    BBVert* pV = (*_Segment.verts);
    pV[0].p = vFinish + vSRight;
    pV[1].p = vFinish - vSRight;
    pV[2].p = vStart + vSRight;
    pV[3].p = vStart - vSRight;

    IOGMapping* pMapping = m_Frames[_Segment.frame];
    float t0y = pMapping->t0.y + (pMapping->t1.y - pMapping->t0.y) * _Segment.start;
    float t1y = pMapping->t0.y + (pMapping->t1.y - pMapping->t0.y) * _Segment.end;
    pV[0].t = OGVec2(pMapping->t1.x, t1y);
    pV[1].t = OGVec2(pMapping->t0.x, t1y);
    pV[2].t = OGVec2(pMapping->t1.x, t0y);
    pV[3].t = OGVec2(pMapping->t0.x, t0y);
}
