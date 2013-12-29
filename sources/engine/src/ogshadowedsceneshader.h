/*
 *  OGShadowedSceneShader.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGSHADOWEDSCENESHADER_H_
#define OGSHADOWEDSCENESHADER_H_

#include "IOGShader.h"


class COGShadowedSceneShader : public IOGShader
{
public:
    COGShadowedSceneShader ();
    virtual ~COGShadowedSceneShader ();

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

    // set alpha test
    virtual void EnableAlphaTest (bool _bEnabled) {}

    // set light and fog
    virtual void SetLighting (IOGFog* _pFog, IOGLightMgr* _pLightMgr);

    // set material
    virtual void SetMaterial (IOGMaterial* _pMaterial);

    // set camera
    virtual void SetCamera (IOGCamera* _pCamera) {}

    // get shader id
    virtual OGShaderID GetShaderID () const { return m_Id; }

protected:

    OGMatrix        m_mMV;
    OGMatrix        m_mMVP;
    OGMatrix        m_mModel;
    OGMatrix        m_mView;
    OGMatrix        m_mProjection;
    OGMatrix        m_mShadowMVP;

    OGShaderID      m_Id;

    unsigned int    m_uiVertShader;
    unsigned int    m_uiFragShader;
    unsigned int    m_uiId;
    unsigned int    m_uiMVPMatrixLoc;
    unsigned int    m_uiMVMatrixLoc;
    unsigned int    m_uiProjMatrixLoc;
    unsigned int    m_uiShadowMVPMatrixLoc;
    unsigned int    m_uiLightDirLoc;
    unsigned int    m_uiTextureLoc;
    unsigned int    m_uiShadowTextureLoc;
    unsigned int    m_uiFogEndLoc;
    unsigned int    m_uiFogRcpDiffLoc;
    unsigned int    m_uiFogColorLoc;
    unsigned int    m_uiFogEnabled;
    unsigned int    m_uiMaterialAmbient;
    unsigned int    m_uiMaterialDiffuse;

    IOGFog*         m_pFog;
    IOGLightMgr*    m_pLightMgr;
};

#endif
