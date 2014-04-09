/*
 *  ogshadermanager.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 07.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGSHADERMANAGER_H_
#define OGSHADERMANAGER_H_

#include "IOGShaderManager.h"
#include <vector>


class COGShaderManager : public IOGShaderManager
{
public:
    COGShaderManager ();
    virtual ~COGShaderManager ();

    // initialize shaders.
    virtual bool Init ();

    // destroy shaders.
    virtual void Destroy ();

    // get shader.
    virtual IOGShader* GetShader (OGShaderID _ShaderId);

    // get shader.
    virtual IOGShader* GetShader (const std::string& _ShaderAlias);

private:

    IOGShader* m_ShaderStorage[OG_SHADERS_MAX];
};


#endif