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
    TEffectsList::iterator iter = m_EffectsList.begin();
    for (; iter != m_EffectsList.end(); ++iter)
    {
		OG_SAFE_DELETE((*iter));
	}
	m_EffectsList.clear();
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
			m_EffectsList.push_back(pEffect);
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
	TEffectsList::iterator iter = std::find(
		m_EffectsList.begin(), m_EffectsList.end(), _pEffect);
	if (iter != m_EffectsList.end())
	{
		OG_SAFE_DELETE((*iter));
		m_EffectsList.erase(iter);
	}
}


// Update effects.
void COGEffectsManager::Update (unsigned long _ElapsedTime)
{
    TEffectsList::iterator iter = m_EffectsList.begin();
    for (; iter != m_EffectsList.end(); ++iter)
    {
		(*iter)->Update(_ElapsedTime);
	}
}


// Render effects.
void COGEffectsManager::Render (const MATRIX& _mView)
{
	Vec3 vUp, vRight, vLook;
	MatrixGetBasis(vRight, vUp, vLook, _mView);
	vUp.normalize();
	vRight.normalize();
	vLook.normalize();

	glMatrixMode(GL_MODELVIEW);

	TEffectsList::iterator iter = m_EffectsList.begin();
    for (; iter != m_EffectsList.end(); ++iter)
    {
		(*iter)->Render(_mView, vRight, vUp);
	}
}
