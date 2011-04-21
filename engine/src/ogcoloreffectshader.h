/*
 *  OGColorEffectShader.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGCOLOREFFECTSHADER_H_
#define OGCOLOREFFECTSHADER_H_

#include "IOGShader.h"


class COGColorEffectShader : public IOGShader
{
public:
    COGColorEffectShader ();
	virtual ~COGColorEffectShader ();

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

    // set light direction
    void SetLightDir (const Vec3& _vLightDir);

    // set fog params
    void SetFogParams (float _fFogStart, float _fFogEnd, const Vec4& _vFogColor);

protected:

    MATRIX  m_mMV;
    MATRIX  m_mMVP;
    MATRIX  m_mModel;
    MATRIX  m_mView;
    MATRIX  m_mProjection;

    // fog params
    Vec4	m_vFogColor;
	float	m_fFogStart;
	float	m_fFogEnd;

	unsigned int m_uiVertShader;
	unsigned int m_uiFragShader;
    unsigned int m_uiId;
	unsigned int m_uiMVPMatrixLoc;
	unsigned int m_uiMVMatrixLoc;
    unsigned int m_uiTextureLoc;
    unsigned int m_uiFogEndLoc;
	unsigned int m_uiFogRcpDiffLoc;
	unsigned int m_uiFogColorLoc;
};

#endif
