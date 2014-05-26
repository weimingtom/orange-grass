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
#include "OrangeGrass.h"
#include "oglight.h"
#include <algorithm>
#include "ogcamera.h"


COGLightMgr::COGLightMgr ()
{
    m_Lights.reserve(8);

    MatrixScaling(m_SMTexAdj, 0.5f, 0.5f, 0.5f);
    m_SMTexAdj.f[12] = 0.5f;
    m_SMTexAdj.f[13] = 0.5f;
    m_SMTexAdj.f[14] = 0.5f;
    MatrixOrthoRH(m_LightProj, 350.0f, 350.0f, 0.01f, 1000.0f, false);

    m_pLightCamera = new COGCamera();
    m_pLightCamera->SetupViewport(m_LightProj);
}


COGLightMgr::~COGLightMgr ()
{
    OG_SAFE_DELETE(m_pLightCamera);
}


// destroy all lights.
void COGLightMgr::Clear ()
{
    std::vector<IOGLight*>::iterator iter = m_Lights.begin();
    for (; iter != m_Lights.end(); ++iter)
    {
        OG_SAFE_DELETE((*iter));
    }
    m_Lights.clear();
}


// add light.
IOGLight* COGLightMgr::CreateLight ()
{
    if (m_Lights.size() < 8)
    {
        IOGLight* pLight = new IOGLight;
        m_Lights.push_back(pLight);
        return pLight;
    }
    return NULL;
}


// destroy light.
void COGLightMgr::DestroyLight (IOGLight* _pLight)
{
    std::vector<IOGLight*>::iterator iter = std::find(m_Lights.begin(), m_Lights.end(), _pLight);
    if (iter != m_Lights.end())
    {
        OG_SAFE_DELETE((*iter));
        m_Lights.erase(iter);
    }
}


// get light.
IOGLight* COGLightMgr::GetLight (unsigned int _Id)
{
    if (m_Lights.size() <= _Id)
    {
        return NULL;
    }

    return m_Lights[_Id];
}


// get global light camera.
IOGCamera* COGLightMgr::GetLightCamera ()
{
    return m_pLightCamera;
}


// update global lighting.
void COGLightMgr::UpdateGlobalLight (IOGCamera* _pCamera)
{
    const OGVec3& vCameraPos = _pCamera->GetPosition();
    OGVec3 vLookAt  = vCameraPos + (_pCamera->GetDirection() * 350.0f);
    vLookAt.y = 0;
    OGVec3 vEyePt = vLookAt - OGVec3(0, -1, 0) * vCameraPos.y;
    m_pLightCamera->Setup(vEyePt, vLookAt, OGVec3(0, 0, -1));
    m_pLightCamera->Update();
    m_LightView = m_pLightCamera->GetViewMatrix();
    MatrixMultiply(m_LightVP, m_LightView, m_LightProj);
    MatrixMultiply(m_ShadowMVP, m_LightVP, m_SMTexAdj);
}
