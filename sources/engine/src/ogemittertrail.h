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
#ifndef OGEMITTERTRAIL_H_
#define OGEMITTERTRAIL_H_

#include "ogemitter.h"
#include <vector>


class COGEmitterTrail : public COGEmitter
{
public:
    COGEmitterTrail();
    virtual ~COGEmitterTrail();

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

    // Is dynamic.
    virtual bool IsDynamic () const {return true;}

    // Get effect type.
    virtual OGEmitterType GetType() const { return s_Type; }

    // Get effect type.
    virtual const std::string& GetAlias() const { return s_Alias; }

protected:

    struct ParticleFormat
    {
        bool    bDirty;
        float   scale;
        float   angle;
        OGVec3  offset;
        TBBVertexEntry verts;
    };

protected:

    std::vector<ParticleFormat> m_BBList;

    float           m_fAlphaFade;
    float           m_fInitialScale;
    float           m_fScaleInc;
    float           m_fEmitDistance;
    float           m_fRotateInc;
    OGVec4          m_color;
    std::string     m_Texture;
    unsigned int    m_MappingId;

    float           m_fDistanceAccum;
    IOGVertexBuffers*   m_pVBO;

public:

    static std::string     s_Alias;
    static OGEmitterType   s_Type;
};


#endif
