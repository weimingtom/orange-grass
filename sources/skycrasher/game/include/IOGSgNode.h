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
#ifndef IOGSGNODE_H_
#define IOGSGNODE_H_

#include "IOGMath.h"
#include "IOGPhysicalObject.h"
#include "IOGRenderable.h"


struct OGSgMeshNode
{
    IOGObb              OBB;
    OGMatrix            mTransform;
    const OGModelNode*  pSkeletonNode;
    OGVec3              vCenter;
};


class IOGSgNode
{
public:
    // destructor
    virtual ~IOGSgNode () {}

    // update transform.
    virtual void Update (unsigned long _ElapsedTime) = 0;

    // render.
    virtual void Render (IOGCamera* _pCamera, OGRenderPass _Pass) = 0;

    // get world transform.
    virtual const OGMatrix& GetWorldTransform () const = 0;

    // Get OBB
    virtual const IOGObb& GetOBB () const = 0;

    // get physics.
    virtual IOGPhysicalObject* GetPhysics () = 0;

    // Get type of the renderable.
    virtual RenderableType GetRenderableType () const = 0;

    // start animation.
    virtual void StartAnimation (const std::string& _Alias) = 0;

    // Get active point
    virtual bool GetActivePoint (OGVec3& _point, const std::string& _Alias) = 0;

    // Get active state
    virtual bool IsActive () const = 0;

    // Set active state
    virtual void Activate (bool _bActive) = 0;
};

#endif
