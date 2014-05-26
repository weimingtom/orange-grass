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
#ifndef IOGMODELSKELETON_H_
#define IOGMODELSKELETON_H_

#include "IOGMesh.h"
#include "IOGRenderable.h"


struct OGModelNode
{
    OGModelNode() 
        : nIdx(-1)
        , nIdxParent(-1)
        , pParent(NULL)
        , pBody(NULL)
        , SceneProps(0)
    {
    }

    ~OGModelNode()
    {
        mTransformList.clear();
    }

    int                         nIdx;
    int                         nIdxParent;
    OGModelNode*                pParent;
    std::vector<OGMatrix>       mTransformList;
    std::vector<OGModelNode*>   ChildNodes;
    void*                       pBody;
    SubMeshType                 BodyType;
    unsigned int                SceneProps;
};


class IOGModelSkeleton
{
public:
    virtual ~IOGModelSkeleton() {}

    // Get node transofrmation matrix
    virtual void GetWorldMatrix(OGMatrix& _mOut, unsigned int _NodeId, unsigned int _Frame) const = 0;

    // Get number of skeleton nodes
    virtual unsigned int GetNumNodes () const = 0;

    // Get specified skeleton node
    virtual const OGModelNode* GetNode (unsigned int _NodeId) const = 0;
};

#endif
