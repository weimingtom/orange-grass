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
    virtual void SetModelMatrix (const OGMatrix& _mModel);

    // set view matrix
    virtual void SetViewMatrix (const OGMatrix& _mView);

    // set projection matrix
    virtual void SetProjectionMatrix (const OGMatrix& _mProj);
    
    // set alpha test
    virtual void EnableAlphaTest (bool _bEnabled) {}

protected:

    OGMatrix  m_mMV;
    OGMatrix  m_mMVP;
    OGMatrix  m_mModel;
    OGMatrix  m_mView;
    OGMatrix  m_mProjection;

	unsigned int m_uiVertShader;
	unsigned int m_uiFragShader;
    unsigned int m_uiId;
	unsigned int m_uiMVPMatrixLoc;
};

#endif
