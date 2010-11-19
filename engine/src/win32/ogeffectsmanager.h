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


class COGEffectsManager : public IOGEffectsManager
{
public:
	COGEffectsManager ();
	virtual ~COGEffectsManager ();

	// create effect.
	virtual IOGEffect* CreateEffect (OGEffectType _Type);

	// create effect.
	virtual IOGEffect* CreateEffect (const std::string& _TypeStr);

	// destroy effect.
	virtual void DestroyEffect (IOGEffect* _pEffect);

	// get effects list (for editor).
	virtual const std::map<std::string, OGEffectType>& GetEffectsList () const;

protected:

	std::map<std::string, OGEffectType>	m_EffectsLookup;
};

#endif