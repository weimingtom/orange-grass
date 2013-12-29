/*
 *  OGEmitterParticleChain.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGEMITTERPARTICLECHAIN_H_
#define OGEMITTERPARTICLECHAIN_H_

#include "ogemitter.h"
#include <vector>


class COGEmitterParticleChain : public COGEmitter
{
public:
    COGEmitterParticleChain();
    virtual ~COGEmitterParticleChain();

    // Initialize emitter.
    virtual void Init(IOGGroupNode* _pNode);

    // Update.
    virtual void Update (unsigned long _ElapsedTime);

    // Render.
    virtual void Render (const OGMatrix& _mWorld, const OGVec3& _vLook, const OGVec3& _vUp, const OGVec3& _vRight, OGRenderPass _Pass);

    // Start.
    virtual void Start ();

    // Stop.
    virtual void Stop ();

    // Get effect type.
    virtual OGEmitterType GetType() const { return s_Type; }

    // Get effect type.
    virtual const std::string& GetAlias() const { return s_Alias; }

protected:

    struct ParticleFormat
    {
        float   scale;
        OGVec3  offset;
        TBBVertexEntry verts;
    };

protected:

    IOGVertexBuffers*           m_pVBO;
    std::vector<ParticleFormat> m_BBList;

    std::string     m_Texture;
    unsigned int    m_MappingId;
    unsigned int    m_NumParticles;
    OGVec4          m_color;

public:

    static std::string     s_Alias;
    static OGEmitterType   s_Type;
};


#endif
