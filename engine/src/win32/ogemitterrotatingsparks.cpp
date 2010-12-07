/*
 *  ogemitterrotatingsparks.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogemitterrotatingsparks.h"
#include "OrangeGrass.h"


COGEmitterRotatingSparks::COGEmitterRotatingSparks()
{
    m_Texture = std::string("effects");
    m_MappingId = 11;
	m_NumParticles = 10;
	m_fAlphaInc = 0.02f;
	m_fScaleInc = 1.5f;
	m_fInitialScale = 3.0f;
    m_color = Vec4(1.0f, 1.0f, 1.0f, 0.5f);

	AddStringParam("texture", &m_Texture);
	AddIntParam("mapping", &m_MappingId);
	AddIntParam("num_particles", &m_NumParticles);
	AddFloatParam("alpha_inc", &m_fAlphaInc);
	AddFloatParam("scale_inc", &m_fScaleInc);
	AddFloatParam("init_scale", &m_fInitialScale);
	AddColorParam("color", &m_color);
}


COGEmitterRotatingSparks::~COGEmitterRotatingSparks()
{
}


// Initialize emitter.
void COGEmitterRotatingSparks::Init(IOGGroupNode* _pNode)
{
	LoadParams(_pNode);

	m_pTexture = GetResourceMgr()->GetTexture(m_Texture);
	m_pMapping = m_pTexture->GetMapping(m_MappingId);
    m_Blend = OG_BLEND_ALPHABLEND;

	m_BBList.reserve(m_NumParticles);

    int a = 0;
    for (unsigned int i = 0; i < m_NumParticles; ++i)
    {
        ParticleFormat p;
        p.scale = m_fInitialScale;
        p.angle = 0.0f;
        p.axis = a;
        p.tilt = i * 0.7f;
        p.offset = Vec3(0,0,0);
        m_color.y = GetRandomRange(0, 90) * 0.01f;
        m_color.z = GetRandomRange(0, 70) * 0.01f;
        p.pVertices[0].c = m_color;
        p.pVertices[0].t = Vec2(m_pMapping->t1.x, m_pMapping->t0.y);
        p.pVertices[1].c = m_color;
        p.pVertices[1].t = Vec2(m_pMapping->t0.x, m_pMapping->t0.y);
        p.pVertices[2].c = m_color;
        p.pVertices[2].t = Vec2(m_pMapping->t1.x, m_pMapping->t1.y);
        p.pVertices[3].c = m_color;
        p.pVertices[3].t = Vec2(m_pMapping->t0.x, m_pMapping->t1.y);
        p.bDirty = true;
        ++a;
        if (a > 2)
            a = 0;
		m_BBList.push_back(p);
    }

	m_bPositionUpdated = false;
}


// Update.
void COGEmitterRotatingSparks::Update (unsigned long _ElapsedTime)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

    switch (m_Status)
    {
    case OG_EFFECTSTATUS_STARTED:
        {
			std::vector<ParticleFormat>::iterator iter = m_BBList.begin();
			for (; iter != m_BBList.end(); ++iter)
			{
				ParticleFormat& p = (*iter);
                p.angle += 0.1f;
            }
        }
        break;

    case OG_EFFECTSTATUS_STOPPED:
        {
			std::vector<ParticleFormat>::iterator iter = m_BBList.begin();
			for (; iter != m_BBList.end(); ++iter)
			{
				ParticleFormat& p = (*iter);
                if (p.pVertices[0].c.w >= m_fAlphaInc)
                {
                    p.angle += 0.1f;
                    p.pVertices[0].c.w -= m_fAlphaInc;
                    p.pVertices[1].c.w -= m_fAlphaInc;
                    p.pVertices[2].c.w -= m_fAlphaInc;
                    p.pVertices[3].c.w -= m_fAlphaInc;
                }
                else
                {
                    m_Status = OG_EFFECTSTATUS_INACTIVE;
					return;
                }
            }
        }
        break;

    case OG_EFFECTSTATUS_INACTIVE:
    default:
        return;
    }
}


// Render.
void COGEmitterRotatingSparks::Render (const MATRIX& _mWorld, const Vec3& _vLook, const Vec3& _vUp, const Vec3& _vRight)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

    MATRIX mId; 
    MatrixIdentity(mId);
    m_pRenderer->SetModelMatrix(mId);
	m_pRenderer->SetBlend(m_Blend);
	m_pRenderer->SetTexture(m_pTexture);

    Vec3 vOffset = Vec3(_mWorld.f[12], _mWorld.f[13], _mWorld.f[14]);

    MATRIX mR;
	std::vector<ParticleFormat>::iterator iter = m_BBList.begin();
	for (; iter != m_BBList.end(); ++iter)
	{
		ParticleFormat& p = (*iter);

        Vec3 vUp = _vUp * p.scale;
        Vec3 vRight = _vRight * p.scale;

        if (m_Status == OG_EFFECTSTATUS_STARTED)
        {
            if (p.axis == 0)
                MatrixRotationX(mR, p.tilt);
            else if (p.axis == 1)
                MatrixRotationY(mR, p.tilt);
            else
                MatrixRotationZ(mR, p.tilt);
            p.offset = Vec3(10, 0, 0);
            if (p.bDirty)
            {
                p.bDirty = false;
            }
            Rotate2DPoint(p.offset.x, p.offset.z, p.angle, 0, 0);
            MatrixVec3Multiply(p.offset, p.offset, mR);
        }
        else if (m_Status == OG_EFFECTSTATUS_STOPPED)
        {
            Vec3 vDir = (p.pVertices[0].p - vOffset).normalized();
            p.offset += vDir * 3;
        }

        p.pVertices[0].p = vOffset + p.offset + vRight + vUp;
        p.pVertices[1].p = vOffset + p.offset - vRight + vUp;
        p.pVertices[2].p = vOffset + p.offset + vRight - vUp;
        p.pVertices[3].p = vOffset + p.offset - vRight - vUp;
        m_pRenderer->DrawEffectBuffer(&p.pVertices[0], 0, 4);
    }
}


// Start.
void COGEmitterRotatingSparks::Start ()
{
	m_Status = OG_EFFECTSTATUS_STARTED;
}


// Stop.
void COGEmitterRotatingSparks::Stop ()
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	m_Status = OG_EFFECTSTATUS_STOPPED;
}
