/*
*  OGEmitterPulseGlow.h
*  OrangeGrass
*
*  Created by Viacheslav Bogdanov on 11.11.09.
*  Copyright 2009 __MyCompanyName__. All rights reserved.
*
*/
#ifndef OGEMITTERPULSEGLOW_H_
#define OGEMITTERPULSEGLOW_H_

#include "ogemitter.h"
#include <vector>


class COGEmitterPulseGlow : public COGEmitter
{
public:
    COGEmitterPulseGlow();
    virtual ~COGEmitterPulseGlow();

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
        bool    bDirty;
        float   scale;
        TBBVertexEntry verts;
    };

protected:

    ParticleFormat  m_Glow;
    int             m_GlowPulse;

    std::string     m_Texture;
    unsigned int    m_MappingId;
    float           m_fGlowAlphaInc;
    float           m_fAlphaInc;
    float           m_fInitialScale;
    OGVec4          m_color;

    IOGVertexBuffers*   m_pVBO;

public:

    static std::string     s_Alias;
    static OGEmitterType   s_Type;
};


#endif
