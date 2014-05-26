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
