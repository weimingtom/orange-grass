/*
 *  IOGShader.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGSHADER_H_
#define IOGSHADER_H_

#include "Mathematics.h"
#include <string>


class IOGShader
{
public:
	virtual ~IOGShader() {}

    // load shaders.
    virtual bool Load (const std::string& _VertShader, const std::string& _FragmentShader) = 0;

    // unload shaders.
    virtual void Unload () = 0;
		
	// apply the shader.
	virtual void Apply () = 0;
		
	// setup the shader.
	virtual void Setup () = 0;

    // set model matrix
    virtual void SetModelMatrix (const MATRIX& _mModel) = 0;

    // set view matrix
    virtual void SetViewMatrix (const MATRIX& _mView) = 0;

    // set projection matrix
    virtual void SetProjectionMatrix (const MATRIX& _mProj) = 0;
};


#endif
