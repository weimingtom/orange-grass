/*
*  oglight.h
*  OrangeGrass
*
*  Created by Viacheslav Bogdanov on 11.11.09.
*  Copyright 2009 __MyCompanyName__. All rights reserved.
*
*/
#ifndef OGLIGHT_H_
#define OGLIGHT_H_

#include "IOGLight.h"
#include <vector>


class COGLightMgr : public IOGLightMgr
{
public:
    COGLightMgr ();
    virtual ~COGLightMgr ();

    // destroy all lights.
    virtual void Clear ();

    // add light.
    virtual IOGLight* CreateLight ();

    // destroy light.
    virtual void DestroyLight (IOGLight* _pLight);

    // get light.
    virtual IOGLight* GetLight (unsigned int _Id);

    // get global light camera.
    virtual IOGCamera* GetLightCamera ();

    // update global lighting.
    virtual void UpdateGlobalLight (IOGCamera* _pCamera);

    // get global lighting view matrix.
    virtual const OGMatrix& GetGlobalLightViewMatrix () const { return m_LightView; }

    // get global lighting projection matrix.
    virtual const OGMatrix& GetGlobalLightProjMatrix () const { return m_LightProj; }

    // get shadow matrix.
    virtual const OGMatrix& GetShadowMatrix () const { return m_ShadowMVP; }

private:

    std::vector<IOGLight*> m_Lights;
    IOGCamera*  m_pLightCamera;

    OGMatrix    m_LightProj;
    OGMatrix    m_LightView;
    OGMatrix    m_LightVP;
    OGMatrix    m_SMTexAdj;
    OGMatrix    m_ShadowMVP;
};

#endif
