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


struct IOGPointLight
{
    Vec4 vColor;
    float fIntensity;
    Vec3 vPosition;
};


class IOGLight
{
public:
	virtual ~IOGLight () {}

	// set light color.
	virtual void SetMainLightColor (const Vec4& _vColor) = 0;

	// get light color.
	virtual const Vec4& GetMainLightColor () const = 0;

	// set light direction.
	virtual void SetMainLightDirection (const Vec3& _vDirection) = 0;

	// get light direction.
	virtual const Vec3& GetMainLightDirection () const = 0;

	// add light.
	virtual IOGPointLight* CreatePointLight () = 0;

	// add light.
	virtual void DestroyPointLight (IOGPointLight* _pLight) = 0;

	// get light.
	virtual IOGPointLight* GetPointLight (unsigned int _Id) = 0;
};

#endif
