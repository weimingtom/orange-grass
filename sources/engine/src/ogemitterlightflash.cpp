/*
 *  ogemitterlightflash.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogemitterlightflash.h"
#include "OrangeGrass.h"


std::string COGEmitterLightFlash::s_Alias = std::string("light_flash");
OGEmitterType COGEmitterLightFlash::s_Type = OG_EMITTER_LIGHTFLASH;


COGEmitterLightFlash::COGEmitterLightFlash()
{
    m_fFadeFactor = 0.64f;
    m_fInitialIntensity = 100.0f;
    m_color = OGVec4(1, 1, 0, 1);

    AddFloatParam("init_intensity", &m_fInitialIntensity);
    AddFloatParam("fade_factor", &m_fFadeFactor);
    AddColorParam("color", &m_color);
}


COGEmitterLightFlash::~COGEmitterLightFlash()
{
}


// Initialize emitter.
void COGEmitterLightFlash::Init(IOGGroupNode* _pNode)
{
    LoadParams(_pNode);

    m_bPositionUpdated = false;
    m_pLight = NULL;
}


// Update.
void COGEmitterLightFlash::Update (unsigned long _ElapsedTime)
{
    if (m_Status == OG_EFFECTSTATUS_INACTIVE)
        return;

    if (m_pLight)
    {
        if (m_pLight->fIntensity >= m_fFadeFactor)
        {
            m_pLight->fIntensity -= m_fFadeFactor;
        }
        else
        {
            Stop();
        }
    }
}


// Render.
void COGEmitterLightFlash::Render (const OGMatrix& _mWorld, const OGVec3& _vLook, const OGVec3& _vUp, const OGVec3& _vRight, OGRenderPass _Pass)
{
    if (m_Status == OG_EFFECTSTATUS_INACTIVE)
        return;

    OGVec3 vOffset = OGVec3(_mWorld.f[12], _mWorld.f[13], _mWorld.f[14]);
    if (m_pLight)
    {
        m_pLight->vPosition = vOffset;
    }
}


// Start.
void COGEmitterLightFlash::Start ()
{
    m_Status = OG_EFFECTSTATUS_STARTED;

    if (m_pLight)
    {
        m_pRenderer->GetLightMgr()->DestroyLight(m_pLight);
        m_pLight = NULL;
    }

    m_pLight = m_pRenderer->GetLightMgr()->CreateLight();

    if (m_pLight)
    {
        m_pLight->vDiffuseColor = m_color;
        m_pLight->vSpecularColor = m_color;
        m_pLight->vAmbientColor = m_color;
        m_pLight->type = OG_LIGHT_POINT;
        m_pLight->fIntensity = m_fInitialIntensity;
    }
}


// Stop.
void COGEmitterLightFlash::Stop ()
{
    if (m_Status == OG_EFFECTSTATUS_INACTIVE)
        return;

    if (m_pLight)
    {
        m_pRenderer->GetLightMgr()->DestroyLight(m_pLight);
        m_pLight = NULL;
    }

    m_Status = OG_EFFECTSTATUS_INACTIVE;
}
