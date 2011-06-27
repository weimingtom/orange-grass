/*
 *  OGModelShader.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenGL2.h"
#include "OrangeGrass.h"
#include "ogmodelshader.h"
#include "GraphicsDevice.h"


COGModelShader::COGModelShader () : m_bAlphaTest(false)
{
}


COGModelShader::~COGModelShader ()
{
}


// load shaders.
bool COGModelShader::Load (const std::string& _VertShader, const std::string& _FragmentShader)
{
    if(ShaderLoadFromFile("blank", _FragmentShader.c_str(), GL_FRAGMENT_SHADER, 0, &m_uiFragShader) == 0)
        return false;
    if(ShaderLoadFromFile("blank", _VertShader.c_str(), GL_VERTEX_SHADER, 0, &m_uiVertShader) == 0)
        return false;

    const char* pszAttribs[] = { "inVertex", "inNormal", "inTexCoord" };
    if (CreateProgram(&m_uiId, m_uiVertShader, m_uiFragShader, pszAttribs, 3) == 0)
        return false;

    m_uiMVPMatrixLoc = glGetUniformLocation(m_uiId, "MVPMatrix");
    m_uiMVMatrixLoc = glGetUniformLocation(m_uiId, "MVMatrix");
	m_uiLightDirLoc = glGetUniformLocation(m_uiId, "LightDirection");
	m_uiTextureLoc = glGetUniformLocation(m_uiId, "sTexture");

    m_uiFogEndLoc = glGetUniformLocation(m_uiId, "FogEnd");
	m_uiFogRcpDiffLoc = glGetUniformLocation(m_uiId, "FogRcpEndStartDiff");
	m_uiFogColorLoc = glGetUniformLocation(m_uiId, "FogColor");
    
    m_uiAlphaReference = glGetUniformLocation(m_uiId, "AlphaReference");

    return true;
}


// unload shaders.
void COGModelShader::Unload ()
{
	glDeleteProgram(m_uiId);
	glDeleteShader(m_uiVertShader);
	glDeleteShader(m_uiFragShader);
}


// apply the shader.
void COGModelShader::Apply ()
{
    MatrixMultiply(m_mMV, m_mModel, m_mView);
    glUniformMatrix4fv(m_uiMVMatrixLoc, 1, GL_FALSE, m_mMV.f);

    MatrixMultiply(m_mMVP, m_mMV, m_mProjection);
    glUniformMatrix4fv(m_uiMVPMatrixLoc, 1, GL_FALSE, m_mMVP.f);

    MATRIX mInvModel;
    MatrixInverse(mInvModel, m_mModel);
    Vec3 vTransformedLightDir;
    MatrixVec3Multiply(vTransformedLightDir, m_vLightDir, mInvModel);
    vTransformedLightDir.normalize();
    glUniform3fv(m_uiLightDirLoc, 1, vTransformedLightDir.ptr());
}


// setup the shader.
void COGModelShader::Setup ()
{
	glUseProgram(m_uiId);
    glUniform1i(m_uiTextureLoc, 0);

	const float fFogRcpEndStartDiff = 1.0f / (m_fFogEnd - m_fFogStart);

    glUniform1f(m_uiFogEndLoc, m_fFogEnd);
	glUniform1f(m_uiFogRcpDiffLoc, fFogRcpEndStartDiff);
    glUniform3fv(m_uiFogColorLoc, 1, m_vFogColor.ptr());
}


// set model matrix
void COGModelShader::SetModelMatrix (const MATRIX& _mModel)
{
    m_mModel = _mModel;
}


// set view matrix
void COGModelShader::SetViewMatrix (const MATRIX& _mView)
{
    m_mView = _mView;
}


// set projection matrix
void COGModelShader::SetProjectionMatrix (const MATRIX& _mProj)
{
    m_mProjection = _mProj;
}


// set light direction
void COGModelShader::SetLightDir (const Vec3& _vLightDir)
{
    m_vLightDir = _vLightDir;
}


// set fog params
void COGModelShader::SetFogParams (float _fFogStart, float _fFogEnd, const Vec4& _vFogColor)
{
    m_vFogColor = _vFogColor;
	m_fFogStart = _fFogStart;
	m_fFogEnd = _fFogEnd;
}


// set alpha test
void COGModelShader::EnableAlphaTest (bool _bEnabled)
{
    m_bAlphaTest = _bEnabled;
    if (m_bAlphaTest)
    {
        m_fAlphaRef = 0.2f;
    }
    else
        m_fAlphaRef = 0;
    glUniform1f(m_uiAlphaReference, m_fAlphaRef);
}

