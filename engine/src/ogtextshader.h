/*
 *  OGTextShader.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGTEXTSHADER_H_
#define OGTEXTSHADER_H_

#include "IOGShader.h"


class COGTextShader : public IOGShader
{
public:
    COGTextShader ();
	virtual ~COGTextShader ();

    // load shaders.
    virtual bool Load (const std::string& _VertShader, const std::string& _FragmentShader);

    // unload shaders.
    virtual void Unload ();
		
	// apply the shader.
	virtual void Apply ();

	// setup the shader.
	virtual void Setup ();

    // set model matrix
    virtual void SetModelMatrix (const MATRIX& _mModel){}

    // set view matrix
    virtual void SetViewMatrix (const MATRIX& _mView){}

    // set projection matrix
    virtual void SetProjectionMatrix (const MATRIX& _mProj);
    
    // set alpha test
    virtual void EnableAlphaTest (bool _bEnabled) {}

protected:

    MATRIX  m_mProjection;

	unsigned int m_uiVertShader;
	unsigned int m_uiFragShader;
    unsigned int m_uiId;
	unsigned int m_uiMVPMatrixLoc;
    unsigned int m_uiTextureLoc;
};

#endif
