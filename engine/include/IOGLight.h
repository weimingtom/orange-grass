/*
 *  IOGLight.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGLIGHT_H_
#define IOGLIGHT_H_

#include "Mathematics.h"


enum OGLightType
{
	OG_LIGHT_DIRECTIONAL,
	OG_LIGHT_POINT
};


struct IOGLight
{
    Vec4 vDiffuseColor;
    Vec4 vAmbientColor;
    Vec4 vSpecularColor;
    float fIntensity;
    Vec3 vPosition;
	OGLightType type;
};


class IOGLightMgr
{
public:
	virtual ~IOGLightMgr () {}

	// add light.
	virtual IOGLight* CreateLight () = 0;

	// destroy light.
	virtual void DestroyLight (IOGLight* _pLight) = 0;

	// get light.
	virtual IOGLight* GetLight (unsigned int _Id) = 0;
};

#endif
