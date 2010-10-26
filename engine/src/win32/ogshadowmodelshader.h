/*
 *  OGShadowModelShader.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGSHADOWMODELSHADER_H_
#define OGSHADOWMODELSHADER_H_

#include "IOGShader.h"
#ifdef GLES20

class COGShadowModelShader : public IOGShader
{
public:
    COGShadowModelShader ();
	virtual ~COGShadowModelShader ();

    // load shaders.
    virtual bool Load (const std::string& _VertShader, const std::string& _FragmentShader);

    // unload shaders.
    virtual void Unload ();
		
	// apply the shader.
	virtual void Apply ();

	// setup the shader.
	virtual void Setup ();

    // set model matrix
    virtual void SetModelMatrix (const MATRIX& _mModel);

    // set view matrix
    virtual void SetViewMatrix (const MATRIX& _mView);

    // set projection matrix
    virtual void SetProjectionMatrix (const MATRIX& _mProj);

protected:

    MATRIX  m_mMV;
    MATRIX  m_mMVP;
    MATRIX  m_mModel;
    MATRIX  m_mView;
    MATRIX  m_mProjection;

	unsigned int m_uiVertShader;
	unsigned int m_uiFragShader;
    unsigned int m_uiId;
	unsigned int m_uiMVPMatrixLoc;
};
#endif
#endif
