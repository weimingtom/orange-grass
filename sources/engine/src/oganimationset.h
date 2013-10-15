/*
 *  oganimationset.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGANIMATIONSET_H_
#define OGANIMATIONSET_H_

#include "IOGAnimation.h"
#include "IOGRenderable.h"
#include "IOGMesh.h"


struct AnimationNode
{
    AnimationNode() 
        : nIdx(-1)
        , nIdxParent(-1)
        , pParent(NULL)
        , pBody(NULL)
    {
    }

    ~AnimationNode()
    {
        mTransformList.clear();
    }

    int                         nIdx;
    int                         nIdxParent;
    AnimationNode*              pParent;
    std::vector<OGMatrix>       mTransformList;
    std::vector<AnimationNode*> ChildNodes;
    void*                       pBody;
    SubMeshType                 BodyType;
};


class COGAnimationSet
{
public:
    COGAnimationSet();
    virtual ~COGAnimationSet();

    void Clear();
    void SetNumFrames(unsigned int _NumFrames);
    AnimationNode* AddNode(int _Idx, int _IdxParent, const float* _pfAnimMatrix);
    AnimationNode* BuildSG ();
    void GetWorldMatrix(OGMatrix& _mOut, unsigned int _NodeId, unsigned int _Frame, float _fBlend) const;

private:
    void AttachChild(AnimationNode* _pParent, AnimationNode* _pChild);

public:
    unsigned int                m_NumFrames;
    std::vector<AnimationNode*> m_Nodes;
};

#endif
