/*
 *  ogmodelskeleton.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGANIMATIONSET_H_
#define OGANIMATIONSET_H_

#include "IOGModelSkeleton.h"
#include "IOGAnimation.h"
#include "IOGRenderable.h"
#include "IOGMesh.h"


class COGModelSkeleton : public IOGModelSkeleton
{
public:
    COGModelSkeleton();
    virtual ~COGModelSkeleton();

    // Get node transofrmation matrix
    virtual void GetWorldMatrix(OGMatrix& _mOut, unsigned int _NodeId, unsigned int _Frame) const;

    // Get number of skeleton nodes
    virtual unsigned int GetNumNodes () const;

    // Get specified skeleton node
    virtual const OGModelNode* GetNode (unsigned int _NodeId) const;

public:
    void Clear();
    void SetNumFrames(unsigned int _NumFrames);
    OGModelNode* AddNode(int _Idx, int _IdxParent, const float* _pfAnimMatrix);
    OGModelNode* BuildSG ();

private:
    void AttachChild(OGModelNode* _pParent, OGModelNode* _pChild);

public:
    unsigned int                m_NumFrames;
    std::vector<OGModelNode*>   m_Nodes;
};

#endif
