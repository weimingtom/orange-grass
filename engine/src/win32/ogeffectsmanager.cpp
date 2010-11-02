/*
 *  ogeffectsmanager.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogeffectsmanager.h"
#include "ogplasmaeffect.h"
#include "ogeffectmissilesmoke.h"
#include "ogeffectexplosion.h"
#include "ogeffectbonuspick.h"
#include "ogeffectcollision.h"
#include "OrangeGrass.h"
#include <algorithm>


COGEffectsManager::COGEffectsManager ()
{
    COGEffectBonusPick::LoadParams();
    COGEffectCollision::LoadParams();
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

	case OG_EFFECT_MISSILESMOKE:
		{
			COGEffectMissileSmoke* pEffect = new COGEffectMissileSmoke();
			pEffect->Init(_Type);
			return pEffect;
		}
		break;

	case OG_EFFECT_EXPLOSION:
		{
			COGEffectExplosion* pEffect = new COGEffectExplosion();
			pEffect->Init(_Type);
			return pEffect;
		}
		break;

	case OG_EFFECT_BONUSPICK:
		{
			COGEffectBonusPick* pEffect = new COGEffectBonusPick();
			pEffect->Init(_Type);
			return pEffect;
		}
		break;

	case OG_EFFECT_COLLISION:
		{
			COGEffectCollision* pEffect = new COGEffectCollision();
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
