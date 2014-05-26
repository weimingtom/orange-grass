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
#include "ogcoloreffectshader.h"
#include "ogshader.h"


COGColorEffectShader::COGColorEffectShader ()
{
}


COGColorEffectShader::~COGColorEffectShader ()
{
}


// load shaders.
bool COGColorEffectShader::Load (OGShaderID _Id, const std::string& _VertShader, const std::string& _FragmentShader)
{
    if(ShaderLoadFromFile(_FragmentShader.c_str(), GL_FRAGMENT_SHADER, &m_uiFragShader) == 0)
        return false;
    if(ShaderLoadFromFile(_VertShader.c_str(), GL_VERTEX_SHADER, &m_uiVertShader) == 0)
        return false;

    const char* pszAttribs[] = { "inVertex", "inTexCoord", "inColor" };
    if (CreateProgram(&m_uiId, m_uiVertShader, m_uiFragShader, pszAttribs, 3) == 0)
        return false;

    m_uiMVPMatrixLoc = glGetUniformLocation(m_uiId, "MVPMatrix");
    m_uiTextureLoc = glGetUniformLocation(m_uiId, "sTexture");

    m_Id = _Id;

    return true;
}


// unload shaders.
void COGColorEffectShader::Unload ()
{
    glDeleteProgram(m_uiId);
    glDeleteShader(m_uiVertShader);
    glDeleteShader(m_uiFragShader);
}


// apply the shader.
void COGColorEffectShader::Apply ()
{
    MatrixMultiply(m_mMV, m_mModel, m_mView);
    MatrixMultiply(m_mMVP, m_mMV, m_mProjection);
    glUniformMatrix4fv(m_uiMVPMatrixLoc, 1, GL_FALSE, m_mMVP.f);
}


// setup the shader.
void COGColorEffectShader::Setup ()
{
    glUseProgram(m_uiId);
    glUniform1i(m_uiTextureLoc, 0);
}


// set model matrix
void COGColorEffectShader::SetModelMatrix (const OGMatrix& _mModel)
{
    m_mModel = _mModel;
}


// set view matrix
void COGColorEffectShader::SetViewMatrix (const OGMatrix& _mView)
{
    m_mView = _mView;
}


// set projection matrix
void COGColorEffectShader::SetProjectionMatrix (const OGMatrix& _mProj)
{
    m_mProjection = _mProj;
}
