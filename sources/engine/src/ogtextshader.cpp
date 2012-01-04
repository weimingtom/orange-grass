/*
 *  OGTextShader.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenGL2.h"
#include "OrangeGrass.h"
#include "ogtextshader.h"
#include "ogshader.h"


COGTextShader::COGTextShader ()
{
}


COGTextShader::~COGTextShader ()
{
}


// load shaders.
bool COGTextShader::Load (const std::string& _VertShader, const std::string& _FragmentShader)
{
    if(ShaderLoadFromFile("blank", _FragmentShader.c_str(), GL_FRAGMENT_SHADER, 0, &m_uiFragShader) == 0)
        return false;
    if(ShaderLoadFromFile("blank", _VertShader.c_str(), GL_VERTEX_SHADER, 0, &m_uiVertShader) == 0)
        return false;

    const char* pszAttribs[] = { "inVertex", "inColor", "inTexCoord" };
    if (CreateProgram(&m_uiId, m_uiVertShader, m_uiFragShader, pszAttribs, 3) == 0)
        return false;

    m_uiMVPMatrixLoc = glGetUniformLocation(m_uiId, "MVPMatrix");
	m_uiTextureLoc = glGetUniformLocation(m_uiId, "sTexture");

    return true;
}


// unload shaders.
void COGTextShader::Unload ()
{
	glDeleteProgram(m_uiId);
	glDeleteShader(m_uiVertShader);
	glDeleteShader(m_uiFragShader);
}


// apply the shader.
void COGTextShader::Apply ()
{
}


// setup the shader.
void COGTextShader::Setup ()
{
	glUseProgram(m_uiId);
    glUniform1i(m_uiTextureLoc, 0);
    glUniformMatrix4fv(m_uiMVPMatrixLoc, 1, GL_FALSE, m_mProjection.f);
}


// set projection matrix
void COGTextShader::SetProjectionMatrix (const OGMatrix& _mProj)
{
    m_mProjection = _mProj;
}
