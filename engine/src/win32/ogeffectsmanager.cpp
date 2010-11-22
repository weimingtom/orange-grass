/*
 *  ogeffectsmanager.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogeffectsmanager.h"
#include "ogeffectplasma.h"
#include "ogeffectmissilesmoke.h"
#include "ogeffecttrailsmoke.h"
#include "ogeffectexplosion.h"
#include "ogeffectbonuspick.h"
#include "ogeffectcollision.h"
#include "ogeffectgauss.h"
#include "OrangeGrass.h"
#include <algorithm>


COGEffectsManager::COGEffectsManager ()
{
    COGEffectBonusPick::LoadParams();
    COGEffectCollision::LoadParams();
    COGEffectMissileSmoke::LoadParams();
    COGEffectTrailSmoke::LoadParams();

	m_EffectsLookup["plasma"] = OG_EFFECT_PLASMA;
	m_EffectsLookup["missile_smoke"] = OG_EFFECT_MISSILESMOKE;
	m_EffectsLookup["explosion"] = OG_EFFECT_EXPLOSION;
	m_EffectsLookup["bonus_pick"] = OG_EFFECT_BONUSPICK;
	m_EffectsLookup["collision"] = OG_EFFECT_COLLISION;
	m_EffectsLookup["trail_smoke"] = OG_EFFECT_TRAILSMOKE;
	m_EffectsLookup["gauss"] = OG_EFFECT_GAUSS;
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
			COGEffectPlasma* pEffect = new COGEffectPlasma();
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

	case OG_EFFECT_TRAILSMOKE:
		{
			COGEffectTrailSmoke* pEffect = new COGEffectTrailSmoke();
			pEffect->Init(_Type);
			return pEffect;
		}
		break;

	case OG_EFFECT_GAUSS:
		{
			COGEffectGauss* pEffect = new COGEffectGauss();
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


// create effect.
IOGEffect* COGEffectsManager::CreateEffect (const std::string& _TypeStr)
{
	return CreateEffect(m_EffectsLookup[_TypeStr]);
}


// destroy effect.
void COGEffectsManager::DestroyEffect (IOGEffect* _pEffect)
{
	OG_SAFE_DELETE(_pEffect);
}


// get effects list (for editor).
const std::map<std::string, OGEffectType>& COGEffectsManager::GetEffectsList () const
{
	return m_EffectsLookup;
}
