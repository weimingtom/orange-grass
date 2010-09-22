/*
 *  IOGEffectsManager.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGEFFECTSMANAGER_H_
#define IOGEFFECTSMANAGER_H_

#include "IOGEffect.h"
#include <string>


class IOGEffectsManager
{
public:
	virtual ~IOGEffectsManager () {}

	// create effect.
	virtual IOGEffect* CreateEffect (OGEffectType _Type) = 0;

	// destroy effect.
	virtual void DestroyEffect (IOGEffect* _pEffect) = 0;
};

#endif