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


/*****************************************************************************
 @Function		ShaderLoadBinaryFromMemory
 @Input         ShaderData		shader compiled binary data
 @Input         Size			shader binary data size (bytes)
 @Input         Type			GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
 @Input         Format			shader binary format
 @Output        pObject		    the resulting shader object
 @Returns       OG_SUCCESS on success and OG_FAIL on failure
 @Description   Loads a shader binary file into memory and passes it to the GL.
 ****************************************************************************/
unsigned int ShaderLoadBinaryFromMemory(	
    const void* const ShaderData, 
    size_t Size, 
    GLenum Type, 
    GLenum Format, 
    GLuint* const pObject) 
{
#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 30000
	// Create and compile the shader object
    *pObject = glCreateShader(Type);
    glShaderBinary(1, pObject, Format, ShaderData, (GLint)Size);
    if (glGetError() != GL_NO_ERROR)
    {
        OG_LOG_ERROR("ShaderLoadBinaryFromMemory: Failed to load binary shader");
    	glDeleteShader(*pObject);
    	return OG_FAIL;
    }
#endif
	return OG_SUCCESS;
}


/*!***************************************************************************
 @Function		ShaderLoadFromFile
 @Input			pszBinFile	binary shader filename
 @Input			pszSrcFile	source shader filename
 @Input			Type		type of shader (GL_VERTEX_SHADER or GL_FRAGMENT_SHADER)
 @Input			Format		shader binary format, or 0 for source shader
 @Output		pObject		the resulting shader object
 @Returns       OG_SUCCESS on success and OG_FAIL on failure
 @Description   Loads a shader file into memory and passes it to the GL.
 ****************************************************************************/
unsigned int ShaderLoadFromFile(	
    const char* const pszBinFile, 
    const char* const pszSrcFile, 
    GLenum Type,
    GLenum Format, 
    GLuint* const pObject)
{
    if(Format)
    {
        COGResourceFile ShaderFile;
        if (ShaderFile.OpenForRead(pszBinFile))
        {
            if(ShaderLoadBinaryFromMemory(ShaderFile.DataPtr(), ShaderFile.Size(), Type, Format, pObject) == OG_SUCCESS)
                return OG_SUCCESS;
        }

        OG_LOG_WARNING("ShaderLoadFromFile: Failed to open shader %s", pszBinFile);
    }

    COGResourceFile ShaderFile;
    if (!ShaderFile.OpenForRead(pszSrcFile))
    {
        OG_LOG_ERROR("ShaderLoadFromFile: Failed to open shader %s", pszSrcFile);
        return OG_FAIL;
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
 @Returns		PVR_SUCCESS on success, PVR_FAIL if failure
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
