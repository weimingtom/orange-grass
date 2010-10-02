/******************************************************************************
 @File         Shader.cpp
 @Title        PFX file parser.
 @Copyright    Copyright (C)  Imagination Technologies Limited.
 @Platform     ANSI compatible
 @Description  Shader handling for OpenGL ES 2.0
******************************************************************************/
#include "..\..\OpenGL2\include\OpenGL2.h"
#include "Shader.h"
#include <string>
#include "ResourceFile.h"


#define GL_SUCCESS		0x3000
#define SUCCESS			1
#define FAIL			0


/*!***************************************************************************
 @Function		ShaderLoadSourceFromMemory
 @Input			pszShaderCode	shader source code
 @Input			Type			type of shader (GL_VERTEX_SHADER or GL_FRAGMENT_SHADER)
 @Output		pObject			the resulting shader object
 @Output		pReturnError	the error message if it failed
 @Return		SUCCESS on success and FAIL on failure
 @Description	Loads a shader source code into memory and compiles it.
*****************************************************************************/
unsigned int ShaderLoadSourceFromMemory(	const char* pszShaderCode, 
											const GLenum Type, 
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
        delete [] pszInfoLog;

        // Delete shader.
        glDeleteShader(*pObject);

        // Return false, couldn't compile.
        return FAIL;
    }

    return SUCCESS;
}

/*!***************************************************************************
 @Function		ShaderLoadFromFile
 @Input			pszBinFile		binary shader filename
 @Input			pszSrcFile		source shader filename
 @Input			Type			type of shader (GL_VERTEX_SHADER or GL_FRAGMENT_SHADER)
 @Input			Format			shader binary format, or 0 for source shader
 @Output		pObject			the resulting shader object
 @Output		pReturnError	the error message if it failed
 @Input			pContext		Context
 @Return		SUCCESS on success and FAIL on failure
 @Description	Loads a shader file into memory and passes it to the GL.
*****************************************************************************/
unsigned int ShaderLoadFromFile(	const char* const pszBinFile, 
									const char* const pszSrcFile, 
									const GLenum Type,
									const GLenum Format, 
									GLuint* const pObject)
{
    if(Format)
    {
        // Unsupported on Win32
        return FAIL;
    }

    CPVRTResourceFile ShaderFile(pszSrcFile);
    if (!ShaderFile.IsOpen())
    {
        return FAIL;
    }

    return ShaderLoadSourceFromMemory(ShaderFile.StringPtr(), Type, pObject);
}


/*!***************************************************************************
 @Function		CreateProgram
 @Output		pProgramObject			the created program object
 @Input			VertexShader			the vertex shader to link
 @Input			FragmentShader			the fragment shader to link
 @Input			pszAttribs				an array of attribute names
 @Input			i32NumAttribs			the number of attributes to bind
 @Returns		SUCCESS on success, FAIL if failure
 @Description	Links a shader program.
*****************************************************************************/
unsigned int CreateProgram(	GLuint* const pProgramObject, 
							const GLuint VertexShader, 
							const GLuint FragmentShader, 
							const char** const pszAttribs,
							const int i32NumAttribs)
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
        delete [] pszInfoLog;
        return FAIL;
    }

    // Actually use the created program.
    glUseProgram(*pProgramObject);

    return SUCCESS;
}

/*!***************************************************************************
 @Function		TestGLError
 @Output		pszLocation			the error message if it failed
 @Returns		SUCCESS on success, FAIL if failure
 @Description	Tests for last state encountered.
 *****************************************************************************/
bool TestGLError(const char* pszLocation)
{
    /*
    TestGLError returns the last error that has happened using egl,
    not the status of the last called function. The user has to
    check after every single egl call or at least once every frame.
    */
    GLint iErr = glGetError();
    if (iErr != GL_SUCCESS)
    {
        return FAIL;
    }

    return SUCCESS;
}
