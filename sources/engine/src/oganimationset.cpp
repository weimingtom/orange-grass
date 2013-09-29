/*
*  oganimationset.cpp
*  OrangeGrass
*
*  Created by Viacheslav Bogdanov on 08.11.09.
*  Copyright 2009 __MyCompanyName__. All rights reserved.
*
*/

#include "OrangeGrass.h"
#include "oganimationset.h"


COGAnimationSet::COGAnimationSet()
    : m_NumFrames (0)
{
}


COGAnimationSet::~COGAnimationSet()
{
    Clear();
}


void COGAnimationSet::Clear()
{
    m_NumFrames = 0;
    std::for_each(m_Nodes.begin(), m_Nodes.end(), [](AnimationNode* m) { OG_SAFE_DELETE(m); });
    m_Nodes.clear();
}


void COGAnimationSet::SetNumFrames(unsigned int _NumFrames)
{
    m_NumFrames = _NumFrames;
}


void COGAnimationSet::AddNode(
    int _Idx, 
    int _IdxParent, 
    unsigned int _AnimFlags, 
    const float* _pfAnimPosition, 
    const float* _pfAnimRotation, 
    const float* _pfAnimScale, 
    const float* _pfAnimMatrix)
{
    AnimationNode* pNode = new AnimationNode();
    pNode->nAnimFlags = _AnimFlags;
    pNode->nIdxParent = _IdxParent;
    pNode->nIdx = _Idx;
    if (m_NumFrames > 0)
    {
        if (pNode->nAnimFlags & OGMatrixAnimation)
        {
            size_t numBytes = m_NumFrames * sizeof(float) * 16;
            pNode->pfAnimMatrix = (float*)malloc(numBytes);
            memcpy(pNode->pfAnimMatrix, _pfAnimMatrix, numBytes);
        }
        if (pNode->nAnimFlags & OGPositionAnimation)
        {
            size_t numBytes = m_NumFrames * sizeof(float) * 3;
            pNode->pfAnimPosition = (float*)malloc(numBytes);
            memcpy(pNode->pfAnimPosition, _pfAnimPosition, numBytes);
        }
        if (pNode->nAnimFlags & OGRotationAnimation)
        {
            size_t numBytes = m_NumFrames * sizeof(float) * 4;
            pNode->pfAnimRotation = (float*)malloc(numBytes);
            memcpy(pNode->pfAnimRotation, _pfAnimRotation, numBytes);
        }
        if (pNode->nAnimFlags & OGScaleAnimation)
        {
            size_t numBytes = m_NumFrames * sizeof(float) * 7;
            pNode->pfAnimScale = (float*)malloc(numBytes);
            memcpy(pNode->pfAnimScale, _pfAnimScale, numBytes);
        }
    }
    else
    {
        size_t numBytes = sizeof(float) * 16;
        pNode->pfAnimMatrix = (float*)malloc(numBytes);
        memcpy(pNode->pfAnimMatrix, _pfAnimMatrix, numBytes);
    }
    m_Nodes.push_back(pNode);
}


void COGAnimationSet::GetWorldMatrix(OGMatrix &mOut, unsigned int _NodeId, unsigned int _Frame, float _fBlend) const
{
    AnimationNode* pNode = m_Nodes[_NodeId];
    OGMatrix mTmp;
    if(pNode->pfAnimMatrix)
    {
        GetTransformationMatrix(mOut, _NodeId, _Frame);
    }
    else
    {
        GetScalingMatrix(mOut, _NodeId, _Frame, _fBlend);

        GetRotationMatrix(mTmp, _NodeId, _Frame, _fBlend);
        MatrixMultiply(mOut, mOut, mTmp);

        GetTranslationMatrix(mTmp, _NodeId, _Frame, _fBlend);
        MatrixMultiply(mOut, mOut, mTmp);
    }

    if(pNode->nIdxParent < 0)
        return;

    GetWorldMatrix(mTmp, pNode->nIdxParent, _Frame, _fBlend);
    MatrixMultiply(mOut, mOut, mTmp);
}


void COGAnimationSet::GetTransformationMatrix(OGMatrix &mOut, unsigned int _NodeId, unsigned int _Frame) const
{
    AnimationNode* pNode = m_Nodes[_NodeId];
    if(pNode->pfAnimMatrix)
    {
        if(pNode->nAnimFlags & OGMatrixAnimation)
        {
            mOut = *((OGMatrix*) &pNode->pfAnimMatrix[16*_Frame]);
        }
        else
        {
            mOut = *((OGMatrix*) pNode->pfAnimMatrix);
        }
    }
    else
    {
        MatrixIdentity(mOut);
    }
}


void COGAnimationSet::GetScalingMatrix(OGMatrix &mOut, unsigned int _NodeId, unsigned int _Frame, float _fBlend) const
{
    AnimationNode* pNode = m_Nodes[_NodeId];
    if(pNode->pfAnimScale)
    {
        if(pNode->nAnimFlags & OGScaleAnimation)
        {
            OGVec3 v;
            Vec3Lerp(v, (OGVec3&)pNode->pfAnimScale[7*(_Frame+0)], (OGVec3&)pNode->pfAnimScale[7*(_Frame+1)], _fBlend);
            MatrixScaling(mOut, v.x, v.y, v.z);
        }
        else
        {
            MatrixScaling(mOut, pNode->pfAnimScale[0], pNode->pfAnimScale[1], pNode->pfAnimScale[2]);
        }
    }
    else
    {
        MatrixIdentity(mOut);
    }
}


void COGAnimationSet::GetRotationMatrix(OGMatrix &mOut, unsigned int _NodeId, unsigned int _Frame, float _fBlend) const
{
    AnimationNode* pNode = m_Nodes[_NodeId];
    if(pNode->pfAnimRotation)
    {
        if(pNode->nAnimFlags & OGRotationAnimation)
        {
            OGQuat q;
            QuaternionSlerp(q, (OGQuat&)pNode->pfAnimRotation[4*_Frame],
                (OGQuat&)pNode->pfAnimRotation[4*(_Frame+1)], _fBlend);
            QuaternionToRotationMatrix(mOut, q);
        }
        else
        {
            QuaternionToRotationMatrix(mOut, *(OGQuat*)pNode->pfAnimRotation);
        }
    }
    else
    {
        MatrixIdentity(mOut);
    }
}


void COGAnimationSet::GetTranslationMatrix(OGMatrix &mOut, unsigned int _NodeId, unsigned int _Frame, float _fBlend) const
{
    AnimationNode* pNode = m_Nodes[_NodeId];
    if(pNode->pfAnimPosition)
    {
        if(pNode->nAnimFlags & OGPositionAnimation)
        {
            OGVec3 v;
            Vec3Lerp(v,
                (OGVec3&)pNode->pfAnimPosition[3*(_Frame+0)],
                (OGVec3&)pNode->pfAnimPosition[3*(_Frame+1)], _fBlend);
            MatrixTranslation(mOut, v.x, v.y, v.z);
        }
        else
        {
            MatrixTranslation(mOut, pNode->pfAnimPosition[0], pNode->pfAnimPosition[1], pNode->pfAnimPosition[2]);
        }
    }
    else
    {
        MatrixIdentity(mOut);
    }
}
