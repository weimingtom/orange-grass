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
#ifndef OGSGEFFECTNODE_H_
#define OGSGEFFECTNODE_H_

#include "IOGMath.h"
#include "IOGSgNode.h"


class COGSgEffectNode : public IOGSgNode
{
    COGSgEffectNode ();

public:
    COGSgEffectNode (IOGEffect* _pRenderable, IOGPhysicalObject* _pPhysics);
    virtual ~COGSgEffectNode ();

    // get world transform.
    virtual const OGMatrix& GetWorldTransform () const;

    // Get OBB
    virtual const IOGObb& GetOBB () const;

    // render.
    virtual void Render (IOGCamera* _pCamera, OGRenderPass _Pass);

    // update transform.
    virtual void Update (unsigned long _ElapsedTime);

    // get physics.
    virtual IOGPhysicalObject* GetPhysics ();

    // Get type of the renderable.
    virtual RenderableType GetRenderableType () const {return OG_RENDERABLE_EFFECT;}

    // start animation.
    virtual void StartAnimation (const std::string& _Alias);

    // Get active point
    virtual bool GetActivePoint (OGVec3& _point, const std::string& _Alias);

    // Get active state
    virtual bool IsActive () const { return m_bActive; }

    // Set active state
    virtual void Activate (bool _bActive);

    // Set billboard basis vectors.
    void SetBillboardVectors (const OGVec3& _vLook, const OGVec3& _vUp, const OGVec3& _vRight);

protected:

    IOGEffect*              m_pRenderable;
    IOGPhysicalObject*      m_pPhysics;
    bool                    m_bActive;
    std::vector<IOGObb>     m_TransformedOBBs;
};

#endif
