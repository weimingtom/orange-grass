/*
 *  OGShadowedSceneShader.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGSHADOWEDSCENESHADER_H_
#define OGSHADOWEDSCENESHADER_H_

#include "IOGShader.h"


class COGShadowedSceneShader : public IOGShader
{
public:
    COGShadowedSceneShader ();
	virtual ~COGShadowedSceneShader ();

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

    // set shadow matrix
    virtual void SetShadowMatrix (const MATRIX& _mShadowMVP);

    // set fog parameters
    virtual void SetFog (IOGFog* _pFog);
    
    // set alpha test
    virtual void EnableAlphaTest (bool _bEnabled) {}

protected:

    MATRIX  m_mMV;
    MATRIX  m_mMVP;
    MATRIX  m_mModel;
    MATRIX  m_mView;
    MATRIX  m_mProjection;
    MATRIX  m_mShadowMVP;

	unsigned int m_uiVertShader;
	unsigned int m_uiFragShader;
    unsigned int m_uiId;
    unsigned int m_uiMVPMatrixLoc;
	unsigned int m_uiMVMatrixLoc;
	unsigned int m_uiShadowMVPMatrixLoc;
    unsigned int m_uiFogEndLoc;
	unsigned int m_uiFogRcpDiffLoc;
	unsigned int m_uiFogColorLoc;
	unsigned int m_uiFogEnabled;

    IOGFog* m_pFog;
};

#endif
