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
#include "OrangeGrass.h"
#include <string>
#include "ogshader.h"
#include "ogresourcefile.h"


/*****************************************************************************
 @Function		ShaderLoadSourceFromMemory
 @Input         pszShaderCode	shader source code
 @Input         Type			GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
 @Output        pObject		    the resulting shader object
 @Returns       OG_SUCCESS on success and OG_FAIL on failure
 @Description   Loads a shader source file into memory and passes it to the GL.
 ****************************************************************************/
unsigned int ShaderLoadSourceFromMemory(	
    const char* pszShaderCode, 
    GLenum Type, 
    GLuint* const pObject)
{
	// Create the shader object.
    *pObject = glCreateShader(Type);
	
	// Load the source code into it.
    glShaderSource(*pObject, 1, &pszShaderCode, NULL);
	
	// Compile the source code.
    glCompileShader(*pObject);

	// Test if compilation succeeded.
	GLint bShaderCompiled;
    glGetShaderiv(*pObject, GL_COMPILE_STATUS, &bShaderCompiled);
	if (!bShaderCompiled)
	{
		// There was an error here, first get the length of the log message.
		int i32InfoLogLength, i32CharsWritten;
		glGetShaderiv(*pObject, GL_INFO_LOG_LENGTH, &i32InfoLogLength);
		
		// Allocate enough space for the message, and retrieve it.
		char* pszInfoLog = new char[i32InfoLogLength];
        glGetShaderInfoLog(*pObject, i32InfoLogLength, &i32CharsWritten, pszInfoLog);
		
        OG_LOG_ERROR("ShaderLoadSourceFromMemory: Failed to compile fragment shader: %s", pszInfoLog);
		delete [] pszInfoLog;
		
		// Delete shader.
		glDeleteShader(*pObject);
		
		// Return false, couldn't compile.
		return OG_FAIL;
	}
	return OG_SUCCESS;
}


/*!***************************************************************************
 @Function		ShaderLoadFromFile
 @Input			pszSrcFile	source shader filename
 @Input			Type		type of shader (GL_VERTEX_SHADER or GL_FRAGMENT_SHADER)
 @Output		pObject		the resulting shader object
 @Returns       OG_SUCCESS on success and OG_FAIL on failure
 @Description   Loads a shader file into memory and passes it to the GL.
 ****************************************************************************/
unsigned int ShaderLoadFromFile(	
    const char* const pszSrcFile, 
    GLenum Type,
    GLuint* const pObject)
{
    COGResourceFile ShaderFile;
    if (!ShaderFile.OpenForRead(pszSrcFile))
    {
        OG_LOG_ERROR("ShaderLoadFromFile: Failed to open shader %s", pszSrcFile);
        return OG_FAIL;
    }

	unsigned int result = ShaderLoadSourceFromMemory(ShaderFile.StringPtr(), Type, pObject);
    if (result == OG_FAIL)
    {
        OG_LOG_ERROR("ShaderLoadFromFile: Failed to load source shader %s", pszSrcFile);
    }
    return result;
}


/*!***************************************************************************
 @Function		CreateProgram
 @Output		pProgramObject			the created program object
 @Input			VertexShader			the vertex shader to link
 @Input			FragmentShader			the fragment shader to link
 @Input			pszAttribs				an array of attribute names
 @Input			i32NumAttribs			the number of attributes to bind
 @Returns		OG_SUCCESS on success, OG_FAIL if failure
 @Description	Links a shader program.
 ****************************************************************************/
unsigned int CreateProgram(	
    GLuint* const pProgramObject, 
    GLuint VertexShader, 
    GLuint FragmentShader, 
    const char** const pszAttribs,
    int i32NumAttribs)
{
	// Create the shader program.
	*pProgramObject = glCreateProgram();

	// Attach the fragment and vertex shaders to it.
	glAttachShader(*pProgramObject, FragmentShader);
	glAttachShader(*pProgramObject, VertexShader);

	// For every member in pszAttribs, bind the proper attributes.
	for (int i = 0; i < i32NumAttribs; ++i)
	{
		glBindAttribLocation(*pProgramObject, i, pszAttribs[i]);
	}

	// Link the program object
	glLinkProgram(*pProgramObject);
	
	// Check if linking succeeded.
	GLint bLinked;
	glGetProgramiv(*pProgramObject, GL_LINK_STATUS, &bLinked);
	if (!bLinked)
	{
		int i32InfoLogLength, i32CharsWritten;
		glGetProgramiv(*pProgramObject, GL_INFO_LOG_LENGTH, &i32InfoLogLength);
		char* pszInfoLog = new char[i32InfoLogLength];
		glGetProgramInfoLog(*pProgramObject, i32InfoLogLength, &i32CharsWritten, pszInfoLog);
        OG_LOG_ERROR("CreateProgram: Failed to link: %s", pszInfoLog);
		delete [] pszInfoLog;
		return OG_FAIL;
	}

	// Actually use the created program.
	glUseProgram(*pProgramObject);
	return OG_SUCCESS;
}
