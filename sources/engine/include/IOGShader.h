/*
 *  IOGShader.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
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
    OG_SHADER_SHADOWMODEL,
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
