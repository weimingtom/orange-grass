/*
 *  IOGShaderManager.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 07.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGSHADERMANAGER_H_
#define IOGSHADERMANAGER_H_

#include "IOGShader.h"
#include <string>


enum OGShaderID
{
	OG_SHADER_NO = 0,
	OG_SHADER_COLOREFFECT,
	OG_SHADER_MODEL,
	OG_SHADER_SHADOWEDSCENE,
	OG_SHADER_SHADOWMODEL,
	OG_SHADER_SPRITE,
	OG_SHADER_TEXT,
    OG_SHADERS_MAX
};


class IOGShaderManager
{
public:
    virtual ~IOGShaderManager () {}

    // initialize shaders.
	virtual bool Init () = 0;

    // destroy shaders.
	virtual void Destroy () = 0;

    // get shader.
	virtual IOGShader* GetShader (OGShaderID _ShaderId) = 0;

    // get shader.
    virtual IOGShader* GetShader (const std::string& _ShaderAlias) = 0;
};


#endif