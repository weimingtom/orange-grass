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
#ifndef IOGEFFECT_H_
#define IOGEFFECT_H_

#include "IOGEmitter.h"
#include <list>

typedef std::vector<IOGEmitter*>    TEmittersList;


enum OGEffectType
{
    OG_EFFECT_NO = 0,
    OG_EFFECT_PLASMA,
    OG_EFFECT_MISSILESMOKE,
    OG_EFFECT_EXPLOSION,
    OG_EFFECT_BONUSPICK,
    OG_EFFECT_COLLISION,
    OG_EFFECT_TRAILSMOKE,
    OG_EFFECT_GAUSS
};


struct BBVert
{
    OGVec3 p;
    OGVec2 t;
    OGVec4 c;
};

typedef std::list<BBVert*>              TBBVertexList;
typedef std::list<BBVert*>::iterator    TBBVertexEntry;


class IOGEffect
{
public:
    virtual ~IOGEffect() {}

    // Initialize effect.
    virtual void Init(OGEffectType _Type, const std::string& _File) = 0;

    // Set billboard basis vectors.
    virtual void SetBillboardVectors (const OGVec3& _vLook, const OGVec3& _vUp, const OGVec3& _vRight) = 0;

    // Set direction.
    virtual void SetDirection (const OGVec3& _vDir) = 0;

    // Set start and finish positions.
    virtual void SetStartFinishPositions (const OGVec3& _vStartPos, const OGVec3& _vFinishPos) = 0;

    // Update.
    virtual void Update (unsigned long _ElapsedTime) = 0;

    // Update position.
    virtual void UpdatePosition (const OGVec3& _vPosition) = 0;

    // Render.
    virtual void Render (const OGMatrix& _mWorld, OGRenderPass _Pass) = 0;

    // Start.
    virtual void Start () = 0;

    // Stop.
    virtual void Stop () = 0;

    // Is dynamic.
    virtual bool IsDynamic () const = 0;

    // Get effect run status.
    virtual OGEffectStatus GetStatus() const = 0;

    // Get effect type.
    virtual OGEffectType GetType() const = 0;

    // Get combined AABB
    virtual const IOGAabb& GetAABB () const = 0;

    // Get emitters list.
    virtual TEmittersList& GetEmitters () = 0;
};

#endif
