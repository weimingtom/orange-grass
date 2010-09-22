/*
 *  ogeffectsmanager.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenGL2.h"
#include "ogeffectsmanager.h"
#include "ogplasmaeffect.h"
#include "OrangeGrass.h"
#include <algorithm>


COGEffectsManager::COGEffectsManager ()
{
}


COGEffectsManager::~COGEffectsManager ()
{
}


// create effect.
IOGEffect* COGEffectsManager::CreateEffect (OGEffectType _Type)
{
	switch (_Type)
	{
	case OG_EFFECT_PLASMA:
		{
			COGPlasmaEffect* pEffect = new COGPlasmaEffect();
			pEffect->Init(_Type);
			return pEffect;
		}
		break;

	default:
	case OG_EFFECT_NO:
		return NULL;
	}
	
	return NULL;
}


// destroy effect.
void COGEffectsManager::DestroyEffect (IOGEffect* _pEffect)
{
	OG_SAFE_DELETE(_pEffect);
}
