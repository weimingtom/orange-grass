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
#include "OpenGL2.h"
#include "OrangeGrass.h"
#include "ogshadowedtranspsceneshader.h"
#include "ogshader.h"


COGShadowedTranspSceneShader::COGShadowedTranspSceneShader () 
    : m_pFog(NULL)
    , m_pLightMgr(NULL)
{
}


COGShadowedTranspSceneShader::~COGShadowedTranspSceneShader ()
{
}


// load shaders.
bool COGShadowedTranspSceneShader::Load (OGShaderID _Id, const std::string& _VertShader, const std::string& _FragmentShader)
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
    m_uiLightDirLoc = glGetUniformLocation(m_uiId, "LightDirection");
    m_uiTextureLoc = glGetUniformLocation(m_uiId, "sTexture");
    m_uiShadowTextureLoc = glGetUniformLocation(m_uiId, "sShadowTexture");

    m_uiFogEndLoc = glGetUniformLocation(m_uiId, "FogEnd");
    m_uiFogRcpDiffLoc = glGetUniformLocation(m_uiId, "FogRcpEndStartDiff");
    m_uiFogColorLoc = glGetUniformLocation(m_uiId, "FogColor");
    m_uiFogEnabled = glGetUniformLocation(m_uiId, "FogEnabled");

    m_uiAlphaReference = glGetUniformLocation(m_uiId, "AlphaReference");

    m_uiMaterialAmbient = glGetUniformLocation(m_uiId, "MaterialAmbient");
    m_uiMaterialDiffuse = glGetUniformLocation(m_uiId, "MaterialDiffuse");

    m_Id = _Id;
    m_fAlphaRef = 0.5f;

    return true;
}


// unload shaders.
void COGShadowedTranspSceneShader::Unload ()
{
    glDeleteProgram(m_uiId);
    glDeleteShader(m_uiVertShader);
    glDeleteShader(m_uiFragShader);
}


// apply the shader.
void COGShadowedTranspSceneShader::Apply ()
{
    MatrixMultiply(m_mMV, m_mModel, m_mView);
    glUniformMatrix4fv(m_uiMVMatrixLoc, 1, GL_FALSE, m_mMV.f);

    MatrixMultiply(m_mMVP, m_mMV, m_mProjection);
    glUniformMatrix4fv(m_uiMVPMatrixLoc, 1, GL_FALSE, m_mMVP.f);

    OGMatrix mInvModel;
    MatrixInverse(mInvModel, m_mModel);
    OGVec3 vTransformedLightDir;
    MatrixVec3Multiply(vTransformedLightDir, m_pLightMgr->GetLight(0)->vPosition, mInvModel);
    vTransformedLightDir.normalize();
    glUniform3fv(m_uiLightDirLoc, 1, vTransformedLightDir.ptr());

    MatrixMultiply(m_mShadowMVP, m_mModel, m_pLightMgr->GetShadowMatrix());
    glUniformMatrix4fv(m_uiShadowMVPMatrixLoc, 1, GL_FALSE, m_mShadowMVP.f);
}


// setup the shader.
void COGShadowedTranspSceneShader::Setup ()
{
    glUseProgram(m_uiId);

    glUniform1i(m_uiTextureLoc, 0);
    glUniform1i(m_uiShadowTextureLoc, 1);

    float fFogStart = m_pFog->GetStart();
    float fFogEnd = m_pFog->GetEnd();
    OGVec4 vFogColor = m_pFog->GetColor();
    const float fFogRcpEndStartDiff = 1.0f / (fFogEnd - fFogStart);

    glUniform1f(m_uiFogEndLoc, fFogEnd);
    glUniform1f(m_uiFogRcpDiffLoc, fFogRcpEndStartDiff);
    glUniform3fv(m_uiFogColorLoc, 1, OGVec3(vFogColor.x, vFogColor.y, vFogColor.z).ptr());
    glUniform1i(m_uiFogEnabled, m_pFog->IsEnabled());
}


// set model matrix
void COGShadowedTranspSceneShader::SetModelMatrix (const OGMatrix& _mModel)
{
    m_mModel = _mModel;
}


// set view matrix
void COGShadowedTranspSceneShader::SetViewMatrix (const OGMatrix& _mView)
{
    m_mView = _mView;
}


// set projection matrix
void COGShadowedTranspSceneShader::SetProjectionMatrix (const OGMatrix& _mProj)
{
    m_mProjection = _mProj;
}


// set light and fog
void COGShadowedTranspSceneShader::SetLighting (IOGFog* _pFog, IOGLightMgr* _pLightMgr)
{
    m_pFog = _pFog;
    m_pLightMgr = _pLightMgr;
}


// set material
void COGShadowedTranspSceneShader::SetMaterial (IOGMaterial* _pMaterial)
{
    const OGVec4& vAmbient = _pMaterial->GetAmbient();
    const OGVec4& vDiffuse = _pMaterial->GetDiffuse();

    glUniform3fv(m_uiMaterialAmbient, 1, OGVec3(vAmbient.x, vAmbient.y, vAmbient.z).ptr());
    glUniform3fv(m_uiMaterialDiffuse, 1, OGVec3(vDiffuse.x, vDiffuse.y, vDiffuse.z).ptr());
    glUniform1f(m_uiAlphaReference, m_fAlphaRef);
}


// set alpha test
void COGShadowedTranspSceneShader::EnableAlphaTest (bool _bEnabled)
{
    m_bAlphaTest = _bEnabled;
    if (m_bAlphaTest)
    {
        m_fAlphaRef = 0.5f;
    }
    else
        m_fAlphaRef = 0;
    glUniform1f(m_uiAlphaReference, m_fAlphaRef);
}
