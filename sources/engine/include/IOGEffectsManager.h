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
#include <map>


struct EffectItem
{
    EffectItem ()
    {
        type = OG_EFFECT_NO;
        file = std::string("");
    }

    EffectItem (OGEffectType _type, const std::string& _file)
    {
        type = _type;
        file = _file;
    }

    OGEffectType    type;
    std::string     file;
};


class IOGEffectsManager
{
public:
	virtual ~IOGEffectsManager () {}

	// create effect.
	virtual IOGEffect* CreateEffect (const std::string& _TypeStr) = 0;

	// create emitter.
	virtual IOGEmitter* CreateEmitter (OGEmitterType _Type) = 0;

	// create emitter.
	virtual IOGEmitter* CreateEmitter (const std::string& _TypeStr) = 0;

	// get effects list (for editor).
	virtual const std::map<std::string, EffectItem>& GetEffectsList () const = 0;

	// get emitters list (for editor).
	virtual const std::map<std::string, OGEmitterType>& GetEmittersList () const = 0;
};

#endif