/*
 *  IOGModelSkeleton.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
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
