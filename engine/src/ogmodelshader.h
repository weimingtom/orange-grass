/*
 *  OGModelShader.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGMODELSHADER_H_
#define OGMODELSHADER_H_

#include "IOGShader.h"
#include "IOGLight.h"
#include "IOGFog.h"


class COGModelShader : public IOGShader
{
public:
    COGModelShader ();
	virtual ~COGModelShader ();

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

    // set light and fog
    void SetLighting (IOGFog* _pFog, IOGLightMgr* _pLightMgr);

    // set material
    void SetMaterial (IOGMaterial* _pMaterial);
    
    // set alpha test
    virtual void EnableAlphaTest (bool _bEnabled);

protected:

    MATRIX  m_mMV;
    MATRIX  m_mMVP;
    MATRIX  m_mModel;
    MATRIX  m_mView;
    MATRIX  m_mProjection;
    
    // alpha test
    float   m_fAlphaRef;
    bool    m_bAlphaTest;

	unsigned int m_uiVertShader;
	unsigned int m_uiFragShader;
    unsigned int m_uiId;
	unsigned int m_uiMVPMatrixLoc;
	unsigned int m_uiMVMatrixLoc;
	unsigned int m_uiLightDirLoc;
    unsigned int m_uiTextureLoc;
    unsigned int m_uiFogEndLoc;
	unsigned int m_uiFogRcpDiffLoc;
	unsigned int m_uiFogColorLoc;
	unsigned int m_uiFogEnabled;
    unsigned int m_uiAlphaReference;

	unsigned int m_uiMaterialAmbient;
	unsigned int m_uiMaterialDiffuse;
	unsigned int m_uiMaterialSpecular;

    IOGFog* m_pFog;
    IOGLightMgr* m_pLightMgr;
};

#endif
