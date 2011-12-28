#ifndef _SHADER_H_
#define _SHADER_H_

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


/*****************************************************************************
 @Function		ShaderLoadBinaryFromMemory
 @Input         ShaderData		shader compiled binary data
 @Input         Size			shader binary data size (bytes)
 @Input         Type			GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
 @Input         Format			shader binary format
 @Output        pObject		    the resulting shader object
 @Returns       SUCCESS on success and FAIL on failure
 @Description   Loads a shader binary file into memory and passes it to the GL.
 ****************************************************************************/
unsigned int ShaderLoadBinaryFromMemory(	
    const void*  const ShaderData, 
    size_t Size, 
    GLenum Type, 
    GLenum Format, 
    GLuint*  const pObject); 


/*!***************************************************************************
 @Function		ShaderLoadFromFile
 @Input			pszBinFile	binary shader filename
 @Input			pszSrcFile	source shader filename
 @Input			Type		type of shader (GL_VERTEX_SHADER or GL_FRAGMENT_SHADER)
 @Input			Format		shader binary format, or 0 for source shader
 @Output		pObject		the resulting shader object
 @Returns       SUCCESS on success and FAIL on failure
 @Description   Loads a shader file into memory and passes it to the GL.
 ****************************************************************************/
unsigned int ShaderLoadFromFile(	
    const char* const pszBinFile, 
	const char* const pszSrcFile, 
	GLenum Type,
	GLenum Format, 
	GLuint* const pObject);


/*!***************************************************************************
 @Function		CreateProgram
 @Output		pProgramObject			the created program object
 @Input			VertexShader			the vertex shader to link
 @Input			FragmentShader			the fragment shader to link
 @Input			pszAttribs				an array of attribute names
 @Input			i32NumAttribs			the number of attributes to bind
 @Returns		PVR_SUCCESS on success, PVR_FAIL if failure
 @Description	Links a shader program.
 ****************************************************************************/
unsigned int CreateProgram(	
    GLuint* const pProgramObject, 
    GLuint VertexShader, 
    GLuint FragmentShader, 
    const char** const pszAttribs,
    int i32NumAttribs);


#endif
