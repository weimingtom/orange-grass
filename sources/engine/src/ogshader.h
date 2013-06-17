#ifndef OGSHADER_H_
#define OGSHADER_H_

#include "OpenGL2.h"
#include <stdio.h>
#include <string>


/*****************************************************************************
 @Function		ShaderLoadSourceFromMemory
 @Input         pszShaderCode	shader source code
 @Input         Type			GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
 @Output        pObject		    the resulting shader object
 @Returns       SUCCESS on success and FAIL on failure
 @Description   Loads a shader source file into memory and passes it to the GL.
 ****************************************************************************/
unsigned int ShaderLoadSourceFromMemory(	
    const char* pszShaderCode, 
    GLenum Type, 
    GLuint* const pObject);


/*!***************************************************************************
 @Function		ShaderLoadFromFile
 @Input			pszSrcFile	source shader filename
 @Input			Type		type of shader (GL_VERTEX_SHADER or GL_FRAGMENT_SHADER)
 @Output		pObject		the resulting shader object
 @Returns       SUCCESS on success and FAIL on failure
 @Description   Loads a shader file into memory and passes it to the GL.
 ****************************************************************************/
unsigned int ShaderLoadFromFile(	
	const char* const pszSrcFile, 
	GLenum Type,
	GLuint* const pObject);


/*!***************************************************************************
 @Function		CreateProgram
 @Output		pProgramObject			the created program object
 @Input			VertexShader			the vertex shader to link
 @Input			FragmentShader			the fragment shader to link
 @Input			pszAttribs				an array of attribute names
 @Input			i32NumAttribs			the number of attributes to bind
 @Returns		SUCCESS on success, FAIL if failure
 @Description	Links a shader program.
 ****************************************************************************/
unsigned int CreateProgram(	
    GLuint* const pProgramObject, 
    GLuint VertexShader, 
    GLuint FragmentShader, 
    const char** const pszAttribs,
    int i32NumAttribs);


#endif
