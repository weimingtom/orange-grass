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