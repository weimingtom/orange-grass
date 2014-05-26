/*
 * OrangeGrass
 * Copyright (C) 2009 Vyacheslav Bogdanov.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/lgpl-3.0-standalone.html>.
 */
#ifndef IOGEFFECTSMANAGER_H_
#define IOGEFFECTSMANAGER_H_

#include "IOGEffect.h"
#include <string>
#include <map>
#include <list>


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

    // allocate new particle in a storage
    virtual TBBVertexEntry AddParticle () = 0;

    // release existing particle in a storage
    virtual void ReleaseParticle (const TBBVertexEntry& _Particle) = 0;

    // get particle storage for rendering
    virtual const TBBVertexList& GetParticleStorage() const = 0;
};

#endif
