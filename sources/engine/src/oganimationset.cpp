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


AnimationNode* COGAnimationSet::AddNode(
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
            pNode->pfAnimMatrix = (OGMatrix*)malloc(numBytes);
            memcpy(pNode->pfAnimMatrix, _pfAnimMatrix, numBytes);
        }
        if (pNode->nAnimFlags & OGPositionAnimation)
        {
            size_t numBytes = m_NumFrames * sizeof(float) * 3;
            pNode->pfAnimPosition = (OGVec3*)malloc(numBytes);
            memcpy(pNode->pfAnimPosition, _pfAnimPosition, numBytes);
        }
        if (pNode->nAnimFlags & OGRotationAnimation)
        {
            size_t numBytes = m_NumFrames * sizeof(float) * 4;
            pNode->pfAnimRotation = (OGQuat*)malloc(numBytes);
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
        pNode->pfAnimMatrix = (OGMatrix*)malloc(numBytes);
        memcpy(pNode->pfAnimMatrix, _pfAnimMatrix, numBytes);
    }
    m_Nodes.push_back(pNode);
    return pNode;
}


AnimationNode* COGAnimationSet::BuildSG ()
{
    bool bRootCreated = false;
    AnimationNode* pRoot = NULL;
    size_t n = m_Nodes.size();
    for (size_t i = 0; i < n; ++i)
    {
        AnimationNode* pCurNode = m_Nodes[i];
        int curParent = pCurNode->nIdxParent;
        if (curParent == -1)
        {
            if (pRoot != NULL)
            {
                if (bRootCreated)
                {
                    pCurNode->pParent = pRoot;
                    pRoot->pChilds.push_back(pCurNode);
                }
                else
                {
                    AnimationNode* pSingleRootNode = new AnimationNode();
                    pSingleRootNode->pfAnimMatrix = (OGMatrix*)malloc(sizeof(OGMatrix));
                    MatrixIdentity(*pSingleRootNode->pfAnimMatrix);
                    pSingleRootNode->mTransform = *pSingleRootNode->pfAnimMatrix;
                    pSingleRootNode->BodyType = OG_SUBMESH_DUMMY;
                    pSingleRootNode->nAnimFlags = OGMatrixAnimation;
                    pSingleRootNode->nIdx = n;
                    pSingleRootNode->nIdxParent = -1;
                    pCurNode->pParent = pSingleRootNode;
                    pSingleRootNode->pChilds.push_back(pCurNode);
                    pRoot->pParent = pSingleRootNode;
                    pSingleRootNode->pChilds.push_back(pRoot);
                    pRoot = pSingleRootNode;
                    m_Nodes.push_back(pSingleRootNode);
                    bRootCreated = true;
                }
            }
            else
            {
                pRoot = pCurNode;
            }
        }
        else
        {
            AnimationNode* pNodeParent = m_Nodes[curParent];
            pNodeParent->pChilds.push_back(pCurNode);
            pCurNode->pParent = pNodeParent;
        }
    }
    return pRoot;
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
            mOut = pNode->pfAnimMatrix[_Frame];
        }
        else
        {
            mOut = pNode->pfAnimMatrix[0];
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
            QuaternionSlerp(q, pNode->pfAnimRotation[_Frame], pNode->pfAnimRotation[_Frame+1], _fBlend);
            QuaternionToRotationMatrix(mOut, q);
        }
        else
        {
            QuaternionToRotationMatrix(mOut, pNode->pfAnimRotation[0]);
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
            Vec3Lerp(v, pNode->pfAnimPosition[_Frame+0], pNode->pfAnimPosition[_Frame+1], _fBlend);
            MatrixTranslation(mOut, v.x, v.y, v.z);
        }
        else
        {
            MatrixTranslation(mOut, pNode->pfAnimPosition[0].x, pNode->pfAnimPosition[0].y, pNode->pfAnimPosition[0].z);
        }
    }
    else
    {
        MatrixIdentity(mOut);
    }
}
