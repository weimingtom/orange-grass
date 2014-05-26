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
#ifndef IOGSHADER_H_
#define IOGSHADER_H_

#include "IOGMath.h"
#include <string>
#include "IOGLight.h"
#include "IOGFog.h"
#include "IOGMaterial.h"
#include "IOGCamera.h"


enum OGShaderID
{
    OG_SHADER_NO = 0,
    OG_SHADER_COLOREFFECT,
    OG_SHADER_MODEL,
    OG_SHADER_TRANSPARENTMODEL,
    OG_SHADER_SHADOWEDSCENE,
    OG_SHADER_SHADOWEDTRANSPARENTSCENE,
    OG_SHADER_SHADOWMODEL,
    OG_SHADER_SHADOWTRANSPARENTMODEL,
    OG_SHADER_SPRITE,
    OG_SHADER_TEXT,
    OG_SHADERS_MAX
};


class IOGShader
{
public:
    virtual ~IOGShader() {}

    // load shaders.
    virtual bool Load (OGShaderID _Id, const std::string& _VertShader, const std::string& _FragmentShader) = 0;

    // unload shaders.
    virtual void Unload () = 0;

    // apply the shader.
    virtual void Apply () = 0;

    // setup the shader.
    virtual void Setup () = 0;

    // set model matrix
    virtual void SetModelMatrix (const OGMatrix& _mModel) = 0;

    // set view matrix
    virtual void SetViewMatrix (const OGMatrix& _mView) = 0;

    // set projection matrix
    virtual void SetProjectionMatrix (const OGMatrix& _mProj) = 0;

    // set alpha test
    virtual void EnableAlphaTest (bool _bEnabled) = 0;

    // set light and fog
    virtual void SetLighting (IOGFog* _pFog, IOGLightMgr* _pLightMgr) = 0;

    // set material
    virtual void SetMaterial (IOGMaterial* _pMaterial) = 0;

    // set camera
    virtual void SetCamera (IOGCamera* _pCamera) = 0;

    // get shader id
    virtual OGShaderID GetShaderID () const = 0;
};


#endif
