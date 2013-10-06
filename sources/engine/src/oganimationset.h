/*
 *  OGAnimation.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGANIMATION_H_
#define OGANIMATION_H_

#include "IOGAnimation.h"
#include "IOGRenderable.h"
#include "IOGMesh.h"


struct AnimationNode
{
    AnimationNode() 
        : pfAnimPosition(NULL)
        , pfAnimRotation(NULL)
        , pfAnimScale(NULL)
        , pfAnimMatrix(NULL)
        , nAnimFlags(0)
        , nIdx(-1)
        , nIdxParent(-1)
        , pParent(NULL)
    {
    }

    ~AnimationNode()
    {
        if (pfAnimPosition) free(pfAnimPosition);
        if (pfAnimRotation) free(pfAnimRotation);
        if (pfAnimScale) free(pfAnimScale);
        if (pfAnimMatrix) free(pfAnimMatrix);
    }

    int             nIdx;
    int             nIdxParent;
    unsigned int    nAnimFlags;
    OGVec3*         pfAnimPosition;
    OGQuat*         pfAnimRotation;
    float*          pfAnimScale;
    OGMatrix*       pfAnimMatrix;

    OGMatrix                    mTransform;
    AnimationNode*              pParent;
    std::vector<AnimationNode*> pChilds;
    void*                       pBody;
    SubMeshType                 BodyType;
};


enum OGAnimationDataTypes
{
    OGPositionAnimation = 0x01,
    OGRotationAnimation = 0x02,
    OGScaleAnimation    = 0x04,
    OGMatrixAnimation   = 0x08
};


class COGAnimationSet
{
public:
    COGAnimationSet();
    virtual ~COGAnimationSet();

    void Clear();
    void SetNumFrames(unsigned int _NumFrames);
    AnimationNode* AddNode(
        int _Idx, 
        int _IdxParent, 
        unsigned int _AnimFlags, 
        const float* _pfAnimPosition, 
        const float* _pfAnimRotation, 
        const float* _pfAnimScale, 
        const float* _pfAnimMatrix);
    AnimationNode* BuildSG ();
    void GetWorldMatrix(OGMatrix& mOut, unsigned int _NodeId, unsigned int _Frame, float _fBlend) const;
    void GetTransformationMatrix(OGMatrix& mOut, unsigned int _NodeId, unsigned int _Frame) const;
    void GetScalingMatrix(OGMatrix& mOut, unsigned int _NodeId, unsigned int _Frame, float _fBlend) const;
    void GetRotationMatrix(OGMatrix& mOut, unsigned int _NodeId, unsigned int _Frame, float _fBlend) const;
    void GetTranslationMatrix(OGMatrix& mOut, unsigned int _NodeId, unsigned int _Frame, float _fBlend) const;

    unsigned int                m_NumFrames;
    std::vector<AnimationNode*> m_Nodes;
};

#endif