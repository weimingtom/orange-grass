/*
*  OGShadowedSceneShader.cpp
*  OrangeGrass
*
*  Created by Viacheslav Bogdanov on 11.11.09.
*  Copyright 2009 __MyCompanyName__. All rights reserved.
*
*/
#include "OpenGL2.h"
#include "OrangeGrass.h"
#include "ogshadowedsceneshader.h"
#include "ogshader.h"


COGShadowedSceneShader::COGShadowedSceneShader () : m_pFog(NULL)
{
}


COGShadowedSceneShader::~COGShadowedSceneShader ()
{
}


// load shaders.
bool COGShadowedSceneShader::Load (OGShaderID _Id, const std::string& _VertShader, const std::string& _FragmentShader)
{
    if(ShaderLoadFromFile(_FragmentShader.c_str(), GL_FRAGMENT_SHADER, &m_uiFragShader) == 0)
        return false;
    if(ShaderLoadFromFile(_VertShader.c_str(), GL_VERTEX_SHADER, &m_uiVertShader) == 0)
        return false;

    const char* pszAttribs[] = { "inVertex", "inNormal", "inTexCoord" };
    if (CreateProgram(&m_uiId, m_uiVertShader, m_uiFragShader, pszAttribs, 3) == 0)
        return false;

    m_uiMVPMatrixLoc = glGetUniformLocation(m_uiId, "MVPMatrix");
    m_uiMVMatrixLoc = glGetUniformLocation(m_uiId, "MVMatrix");
    m_uiShadowMVPMatrixLoc = glGetUniformLocation(m_uiId, "ShadowMVPMatrix");

    m_uiFogEndLoc = glGetUniformLocation(m_uiId, "FogEnd");
    m_uiFogRcpDiffLoc = glGetUniformLocation(m_uiId, "FogRcpEndStartDiff");
    m_uiFogColorLoc = glGetUniformLocation(m_uiId, "FogColor");
    m_uiFogEnabled = glGetUniformLocation(m_uiId, "FogEnabled");

    m_Id = _Id;

    return true;
}


// unload shaders.
void COGShadowedSceneShader::Unload ()
{
    glDeleteProgram(m_uiId);
    glDeleteShader(m_uiVertShader);
    glDeleteShader(m_uiFragShader);
}


// apply the shader.
void COGShadowedSceneShader::Apply ()
{
    MatrixMultiply(m_mMV, m_mModel, m_mView);
    glUniformMatrix4fv(m_uiMVMatrixLoc, 1, GL_FALSE, m_mMV.f);

    MatrixMultiply(m_mMVP, m_mMV, m_mProjection);
    glUniformMatrix4fv(m_uiMVPMatrixLoc, 1, GL_FALSE, m_mMVP.f);

    glUniformMatrix4fv(m_uiShadowMVPMatrixLoc, 1, GL_FALSE, m_mShadowMVP.f);
}


// setup the shader.
void COGShadowedSceneShader::Setup ()
{
    glUseProgram(m_uiId);

    float fFogStart = m_pFog->GetStart();
    float fFogEnd = m_pFog->GetEnd();
    OGVec4 vFogColor = m_pFog->GetColor();

    const float fFogRcpEndStartDiff = 1.0f / (fFogEnd - fFogStart);

    glUniform1f(m_uiFogEndLoc, fFogEnd);
    glUniform1f(m_uiFogRcpDiffLoc, fFogRcpEndStartDiff);
    glUniform3fv(m_uiFogColorLoc, 1, OGVec3(vFogColor.x, vFogColor.y, vFogColor.z).ptr());
    glUniform1f(m_uiFogEnabled, m_pFog->IsEnabled() ? 1.0f : 0.0f);
}


// set model matrix
void COGShadowedSceneShader::SetModelMatrix (const OGMatrix& _mModel)
{
    m_mModel = _mModel;
}


// set view matrix
void COGShadowedSceneShader::SetViewMatrix (const OGMatrix& _mView)
{
    m_mView = _mView;
}


// set projection matrix
void COGShadowedSceneShader::SetProjectionMatrix (const OGMatrix& _mProj)
{
    m_mProjection = _mProj;
}


// set light and fog
void COGShadowedSceneShader::SetLighting (IOGFog* _pFog, IOGLightMgr* _pLightMgr)
{
    m_pFog = _pFog;
    m_mShadowMVP = _pLightMgr->GetShadowMatrix();
}
