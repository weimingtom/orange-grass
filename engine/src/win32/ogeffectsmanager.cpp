/*
 *  ogeffectsmanager.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogeffectsmanager.h"
#include "ogeffect.h"
#include "ogemitteranimatedbb.h"
#include "ogemitterlightflash.h"
#include "ogemitterpulseglow.h"
#include "ogemitterringwave.h"
#include "ogemitterscrollingray.h"
#include "ogemitterrotatingsparks.h"
#include "ogemittertrail.h"
#include "ogemitterglow.h"
#include "ogemitterparticlechain.h"
#include "OrangeGrass.h"
#include <algorithm>


COGEffectsManager::COGEffectsManager ()
{
	m_EffectsLookup["plasma"] = EffectItem(OG_EFFECT_PLASMA, "Effects/plasma.xml");
	m_EffectsLookup["missile_smoke"] = EffectItem(OG_EFFECT_MISSILESMOKE, "Effects/missile_smoke.xml");
	m_EffectsLookup["explosion"] = EffectItem(OG_EFFECT_EXPLOSION, "Effects/explosion.xml");
	m_EffectsLookup["bonus_pick"] = EffectItem(OG_EFFECT_BONUSPICK, "Effects/bonus_pick.xml");
	m_EffectsLookup["collision"] = EffectItem(OG_EFFECT_COLLISION, "Effects/collision.xml");
	m_EffectsLookup["trail_smoke"] = EffectItem(OG_EFFECT_TRAILSMOKE, "Effects/trail_smoke.xml");
	m_EffectsLookup["gauss"] = EffectItem(OG_EFFECT_GAUSS, "Effects/gauss.xml");

	m_EmittersLookup["animated_bb"] = OG_EMITTER_ANIMATEDBB;
	m_EmittersLookup["glow"] = OG_EMITTER_GLOW;
	m_EmittersLookup["light_flash"] = OG_EMITTER_LIGHTFLASH;
	m_EmittersLookup["particle_chain"] = OG_EMITTER_PARTICLECHAIN;
	m_EmittersLookup["pulse_glow"] = OG_EMITTER_PULSEGLOW;
	m_EmittersLookup["ring_wave"] = OG_EMITTER_RINGWAVE;
	m_EmittersLookup["rotating_sparks"] = OG_EMITTER_ROTATINGSPARKS;
	m_EmittersLookup["scrolling_ray"] = OG_EMITTER_SCROLLINGRAY;
	m_EmittersLookup["trail"] = OG_EMITTER_TRAIL;
}


COGEffectsManager::~COGEffectsManager ()
{
}


// create effect.
IOGEffect* COGEffectsManager::CreateEffect (const std::string& _TypeStr)
{
    std::map<std::string, EffectItem>::const_iterator iter = m_EffectsLookup.find(_TypeStr);
    if (iter != m_EffectsLookup.end())
    {
        COGEffect* pEffect = new COGEffect();
        pEffect->Init(iter->second.type, iter->second.file);
        return pEffect;
    }
    return NULL;
}


// create emitter.
IOGEmitter* COGEffectsManager::CreateEmitter (OGEmitterType _Type)
{
	switch (_Type)
	{
    case OG_EMITTER_ANIMATEDBB:
        return new COGEmitterAnimatedBB();

    case OG_EMITTER_GLOW:
        return new COGEmitterGlow();

    case OG_EMITTER_LIGHTFLASH:
        return new COGEmitterLightFlash();

    case OG_EMITTER_PARTICLECHAIN:
        return new COGEmitterParticleChain();

    case OG_EMITTER_PULSEGLOW:
        return new COGEmitterPulseGlow();

    case OG_EMITTER_RINGWAVE:
        return new COGEmitterRingWave();

    case OG_EMITTER_ROTATINGSPARKS:
        return new COGEmitterRotatingSparks();

    case OG_EMITTER_SCROLLINGRAY:
        return new COGEmitterScrollingRay();

    case OG_EMITTER_TRAIL:
        return new COGEmitterTrail();

    default:
    case OG_EMITTER_NO:
		return NULL;
	}
	
	return NULL;
}


// create emitter.
IOGEmitter* COGEffectsManager::CreateEmitter (const std::string& _TypeStr)
{
	return CreateEmitter(m_EmittersLookup[_TypeStr]);
}


// get effects list (for editor).
const std::map<std::string, EffectItem>& COGEffectsManager::GetEffectsList () const
{
	return m_EffectsLookup;
}


// get emitters list (for editor).
const std::map<std::string, OGEmitterType>& COGEffectsManager::GetEmittersList () const
{
    return m_EmittersLookup;
}
