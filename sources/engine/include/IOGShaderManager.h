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