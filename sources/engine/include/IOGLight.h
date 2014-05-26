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
#ifndef IOGLIGHT_H_
#define IOGLIGHT_H_

#include "IOGMath.h"
#include "IOGCamera.h"


enum OGLightType
{
    OG_LIGHT_DIRECTIONAL,
    OG_LIGHT_POINT
};


struct IOGLight
{
    OGVec4 vDiffuseColor;
    OGVec4 vAmbientColor;
    OGVec4 vSpecularColor;
    float fIntensity;
    OGVec3 vPosition;
    OGLightType type;
};


class IOGLightMgr
{
public:
    virtual ~IOGLightMgr () {}

    // destroy all lights.
    virtual void Clear () = 0;

    // add light.
    virtual IOGLight* CreateLight () = 0;

    // destroy light.
    virtual void DestroyLight (IOGLight* _pLight) = 0;

    // get light.
    virtual IOGLight* GetLight (unsigned int _Id) = 0;

    // get global light camera.
    virtual IOGCamera* GetLightCamera () = 0;

    // update global lighting.
    virtual void UpdateGlobalLight (IOGCamera* _pCamera) = 0;

    // get global lighting view matrix.
    virtual const OGMatrix& GetGlobalLightViewMatrix () const = 0;

    // get global lighting projection matrix.
    virtual const OGMatrix& GetGlobalLightProjMatrix () const = 0;

    // get shadow matrix.
    virtual const OGMatrix& GetShadowMatrix () const = 0;
};

#endif
