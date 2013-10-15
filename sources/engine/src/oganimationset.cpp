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


AnimationNode* COGAnimationSet::AddNode(int _Idx, int _IdxParent, const float* _pfAnimMatrix)
{
    AnimationNode* pNode = new AnimationNode();
    pNode->nIdxParent = _IdxParent;
    pNode->nIdx = _Idx;
    const OGMatrix* pSrcMatrixArr = (const OGMatrix*)_pfAnimMatrix;
    if (m_NumFrames > 0)
    {
        pNode->mTransformList.reserve(m_NumFrames);
        for (unsigned int i = 0; i < m_NumFrames; ++i)
        {
            OGMatrix m;
            memcpy(m.f, &pSrcMatrixArr[i], sizeof(float) * 16);
            pNode->mTransformList.push_back(m);
        }
    }
    else
    {
        OGMatrix m;
        memcpy(m.f, pSrcMatrixArr, sizeof(float) * 16);
        pNode->mTransformList.push_back(m);
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
        pCurNode->nIdx = i;
        int curParent = pCurNode->nIdxParent;
        if (curParent == -1)
        {
            if (pRoot != NULL)
            {
                if (bRootCreated)
                {
                    AttachChild(pRoot, pCurNode);
                }
                else
                {
                    AnimationNode* pSingleRootNode = new AnimationNode();
                    OGMatrix mIdentity;
                    MatrixIdentity(mIdentity);
                    pSingleRootNode->mTransformList.push_back(mIdentity);
                    pSingleRootNode->BodyType = OG_SUBMESH_DUMMY;
                    pSingleRootNode->nIdx = n;
                    pSingleRootNode->nIdxParent = -1;
                    AttachChild(pSingleRootNode, pCurNode);
                    AttachChild(pSingleRootNode, pRoot);
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
            pNodeParent->nIdx = curParent;
            AttachChild(pNodeParent, pCurNode);
        }
    }
    return pRoot;
}


void COGAnimationSet::GetWorldMatrix(OGMatrix& _mOut, unsigned int _NodeId, unsigned int _Frame, float _fBlend) const
{
    AnimationNode* pNode = m_Nodes[_NodeId];
    if (pNode->mTransformList.size() > _Frame)
        _mOut = pNode->mTransformList[_Frame];
    else
        _mOut = pNode->mTransformList[0];

    if(pNode->nIdxParent < 0)
        return;

    OGMatrix mTmp;
    GetWorldMatrix(mTmp, pNode->nIdxParent, _Frame, _fBlend);
    MatrixMultiply(_mOut, _mOut, mTmp);
}


void COGAnimationSet::AttachChild(AnimationNode* _pParent, AnimationNode* _pChild)
{
    _pChild->pParent = _pParent;
    _pChild->nIdxParent = _pParent->nIdx;
    _pParent->ChildNodes.push_back(_pChild);
}
