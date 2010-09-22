/*
 *  OGEffectsManager.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGEFFECTSMANAGER_H_
#define OGEFFECTSMANAGER_H_

#include "IOGEffectsManager.h"
#include <list>


class COGEffectsManager : public IOGEffectsManager
{
public:
	COGEffectsManager ();
	virtual ~COGEffectsManager ();

	// create effect.
	virtual IOGEffect* CreateEffect (OGEffectType _Type);

	// destroy effect.
	virtual void DestroyEffect (IOGEffect* _pEffect);
};

#endif