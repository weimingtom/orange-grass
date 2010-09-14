/*
 *  IOGFog.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGFOG_H_
#define IOGFOG_H_

#include "Mathematics.h"


class IOGFog
{
public:
	virtual ~IOGFog () {}

	// set light color.
	virtual void SetColor (const Vec4& _vColor) = 0;
	
	// get light color.
	virtual const Vec4& GetColor () const = 0;

	// set fog start.
	virtual void SetStart (float _fStart) = 0;

	// set fog end.
	virtual void SetEnd (float _fEnd) = 0;

	// set fog density.
	virtual void SetDensity (float _fDensity) = 0;

	// get fog start.
	virtual float GetStart () const = 0;

	// get fog end.
	virtual float GetEnd () const = 0;

	// get fog density.
	virtual float GetDensity () const = 0;

	// enable or disable.
	virtual void Enable (bool _bEnable) = 0;

	// get status.
	virtual bool IsEnabled () const = 0;
};

#endif
