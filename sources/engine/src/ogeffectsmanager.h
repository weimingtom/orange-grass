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
#ifndef OGEFFECTSMANAGER_H_
#define OGEFFECTSMANAGER_H_

#include "IOGEffectsManager.h"


class COGEffectsManager : public IOGEffectsManager
{
public:
    COGEffectsManager ();
    virtual ~COGEffectsManager ();

    // create effect.
    virtual IOGEffect* CreateEffect (const std::string& _TypeStr);

    // create emitter.
    virtual IOGEmitter* CreateEmitter (OGEmitterType _Type);

    // create emitter.
    virtual IOGEmitter* CreateEmitter (const std::string& _TypeStr);

    // get effects list (for editor).
    virtual const std::map<std::string, EffectItem>& GetEffectsList () const;

    // get emitters list (for editor).
    virtual const std::map<std::string, OGEmitterType>& GetEmittersList () const;

    // allocate new particle in a storage
    virtual TBBVertexEntry AddParticle ();

    // release existing particle in a storage
    virtual void ReleaseParticle (const TBBVertexEntry& _Particle);

    // get particle storage for rendering
    virtual const TBBVertexList& GetParticleStorage() const;

protected:

    std::map<std::string, EffectItem>       m_EffectsLookup;
    std::map<std::string, OGEmitterType>    m_EmittersLookup;
    TBBVertexList                           m_ParticleStorage;
};

#endif