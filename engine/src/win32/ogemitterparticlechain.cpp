/*
 *  ogemitterparticlechain.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogemitterparticlechain.h"
#include "OrangeGrass.h"


COGEmitterParticleChain::COGEmitterParticleChain()
{
}


COGEmitterParticleChain::~COGEmitterParticleChain()
{
}


// Initialize emitter.
void COGEmitterParticleChain::Init()
{
	m_pTexture = GetResourceMgr()->GetTexture(m_Texture);
    m_Blend = OG_BLEND_ALPHAADD;
	m_pMapping = m_pTexture->GetMapping(m_MappingId);

	for (int i = 0; i < MAX_PLASMA_PARTILES; ++i)
	{
		ParticleFormat& particle = m_BB[i];
		particle.scale = ((float)MAX_PLASMA_PARTILES - i) / 4.5f;
        particle.pVertices[0].t = Vec2(m_pMapping->t1.x, m_pMapping->t0.y);
        particle.pVertices[1].t = Vec2(m_pMapping->t0.x, m_pMapping->t0.y);
        particle.pVertices[2].t = Vec2(m_pMapping->t1.x, m_pMapping->t1.y);
        particle.pVertices[3].t = Vec2(m_pMapping->t0.x, m_pMapping->t1.y);
		particle.pVertices[0].c = m_color;
		particle.pVertices[1].c = m_color;
		particle.pVertices[2].c = m_color;
		particle.pVertices[3].c = m_color;
	}

	m_bPositionUpdated = false;
}


// Update.
void COGEmitterParticleChain::Update (unsigned long _ElapsedTime)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	for (int i = 0; i < MAX_PLASMA_PARTILES; ++i)
	{
		m_BB[i].offset = m_Direction * (float)i;
	}
}


// Render.
void COGEmitterParticleChain::Render (const MATRIX& _mWorld, const Vec3& _vLook, const Vec3& _vUp, const Vec3& _vRight)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

    MATRIX mId; 
    MatrixIdentity(mId);
    m_pRenderer->SetModelMatrix(mId);
	m_pRenderer->SetBlend(m_Blend);
	m_pRenderer->SetTexture(m_pTexture);

    Vec3 vOffset = Vec3(_mWorld.f[12], _mWorld.f[13], _mWorld.f[14]);

	for (int i = 0; i < MAX_PLASMA_PARTILES; ++i)
	{
		ParticleFormat& particle = m_BB[i];
		Vec3 vSUp = _vUp * particle.scale;
		Vec3 vSRight = _vRight * particle.scale;
		particle.pVertices[0].p = vOffset + vSRight + vSUp + particle.offset;
		particle.pVertices[1].p = vOffset - vSRight + vSUp + particle.offset;
		particle.pVertices[2].p = vOffset + vSRight - vSUp + particle.offset;
		particle.pVertices[3].p = vOffset - vSRight - vSUp + particle.offset;

		m_pRenderer->DrawEffectBuffer(&particle.pVertices[0], 0, 4);
	}
}


// Start.
void COGEmitterParticleChain::Start ()
{
	m_Status = OG_EFFECTSTATUS_STARTED;
	Update(0);
}


// Stop.
void COGEmitterParticleChain::Stop ()
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	m_Status = OG_EFFECTSTATUS_INACTIVE;
}


// Set direction.
void COGEmitterParticleChain::SetDirection (const Vec3& _vDir)
{
	m_Direction = _vDir;
}
