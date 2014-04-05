/*
 *  oglight.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
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
    //MatrixPerspectiveFovRH(m_LightProj, 0.78539819f, 1.0f, 0.01f, 1000.0f, false);
    MatrixOrthoRH(m_LightProj, 400.0f, 400.0f, 0.01f, 1000.0f, false);

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
    OGVec3 vLookAt  = vCameraPos + (_pCamera->GetDirection() * 600.0f);
    vLookAt.y = 0;
    OGVec3 vEyePt = vLookAt - OGVec3(0, -1, 0) * vCameraPos.y;
    m_pLightCamera->Setup(vEyePt, vLookAt, OGVec3(0, 0, -1));
    m_pLightCamera->Update();
    m_LightView = m_pLightCamera->GetViewMatrix();

    OGMatrix viewInv;
    MatrixInverse(viewInv, _pCamera->GetViewMatrix());
    MatrixMultiply(viewInv, viewInv, m_LightView);
    MatrixMultiply(m_LightVP, m_LightView, m_LightProj);
    MatrixMultiply(m_ShadowMVP, m_LightVP, m_SMTexAdj);
}
