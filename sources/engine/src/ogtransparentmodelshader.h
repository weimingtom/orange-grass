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
#ifndef OGTRANSPARENTMODELSHADER_H_
#define OGTRANSPARENTMODELSHADER_H_

#include "IOGShader.h"


class COGTransparentModelShader : public IOGShader
{
public:
    COGTransparentModelShader ();
    virtual ~COGTransparentModelShader ();

    // load shaders.
    virtual bool Load (OGShaderID _Id, const std::string& _VertShader, const std::string& _FragmentShader);

    // unload shaders.
    virtual void Unload ();

    // apply the shader.
    virtual void Apply ();

    // setup the shader.
    virtual void Setup ();

    // set model matrix
    virtual void SetModelMatrix (const OGMatrix& _mModel);

    // set view matrix
    virtual void SetViewMatrix (const OGMatrix& _mView);

    // set projection matrix
    virtual void SetProjectionMatrix (const OGMatrix& _mProj);

    // set light and fog
    virtual void SetLighting (IOGFog* _pFog, IOGLightMgr* _pLightMgr);

    // set material
    virtual void SetMaterial (IOGMaterial* _pMaterial);

    // set camera
    virtual void SetCamera (IOGCamera* _pCamera) {}

    // set alpha test
    virtual void EnableAlphaTest (bool _bEnabled);

    // get shader id
    virtual OGShaderID GetShaderID () const { return m_Id; }

protected:

    OGMatrix    m_mMV;
    OGMatrix    m_mMVP;
    OGMatrix    m_mModel;
    OGMatrix    m_mView;
    OGMatrix    m_mProjection;
    OGShaderID  m_Id;

    // alpha test
    float   m_fAlphaRef;
    bool    m_bAlphaTest;

    unsigned int m_uiVertShader;
    unsigned int m_uiFragShader;
    unsigned int m_uiId;
    unsigned int m_uiMVPMatrixLoc;
    unsigned int m_uiMVMatrixLoc;
    unsigned int m_uiLightDirLoc;
    unsigned int m_uiTextureLoc;
    unsigned int m_uiFogEndLoc;
    unsigned int m_uiFogRcpDiffLoc;
    unsigned int m_uiFogColorLoc;
    unsigned int m_uiFogEnabled;
    unsigned int m_uiAlphaReference;

    unsigned int m_uiMaterialAmbient;
    unsigned int m_uiMaterialDiffuse;

    IOGFog* m_pFog;
    IOGLightMgr* m_pLightMgr;
};

#endif
