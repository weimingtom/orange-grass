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
#include "Game.h"
#include "ogsgnode.h"
#include "ogbakedanimation.h"
#include "ogprocedureanimation.h"


COGSgNode::COGSgNode (IOGModel* _pRenderable, IOGPhysicalObject* _pPhysics) 
    : m_pRenderable(_pRenderable)
    , m_pPhysics(_pPhysics)
    , m_pBakedAnimation(NULL)
    , m_pProcedureAnimation(NULL)
    , m_bActive(true)
{
    m_pBakedAnimation = new COGBakedAnimation();

    m_pSkeleton = m_pRenderable->GetModelSkeleton();
    if (m_pSkeleton)
    {
        unsigned int NumMeshNodes = m_pSkeleton->GetNumNodes();
        m_MeshNodes.reserve(NumMeshNodes);
        for (unsigned int i = 0; i < NumMeshNodes; ++i)
        {
            OGSgMeshNode node;
            node.pSkeletonNode = m_pSkeleton->GetNode(i);
            if (node.pSkeletonNode->BodyType == OG_SUBMESH_PROPELLER && !m_pProcedureAnimation)
            {
                m_pProcedureAnimation = new COGRotationAnimation();
                m_pProcedureAnimation->Start(NULL);
            }
            m_MeshNodes.push_back(node);
        }
    }
}


COGSgNode::~COGSgNode () 
{
    m_MeshNodes.clear();
    m_pRenderable = NULL;
    m_pSkeleton = NULL;
    m_pPhysics = NULL;
    OG_SAFE_DELETE(m_pBakedAnimation);
    OG_SAFE_DELETE(m_pProcedureAnimation);
}


// get world transform.
const OGMatrix& COGSgNode::GetWorldTransform () const
{
    return m_pPhysics->GetWorldTransform();
}


// Get OBB
const IOGObb& COGSgNode::GetOBB () const
{
    return m_pPhysics->GetOBB();
}


// update transform.
void COGSgNode::Update (unsigned long _ElapsedTime)
{
    if (!m_bActive)
        return;

    m_pBakedAnimation->Update(_ElapsedTime);
    unsigned int AnimFrame = (unsigned int)m_pBakedAnimation->GetProgress();

    OGMatrix mNodeWorld;
    const OGMatrix& mWorld = m_pPhysics->GetWorldTransform();
    unsigned int NumMeshNodes = m_MeshNodes.size();
    for (unsigned int i = 0; i < NumMeshNodes; ++i)
    {
        OGSgMeshNode& curNode = m_MeshNodes[i];
        m_pSkeleton->GetWorldMatrix(mNodeWorld, i, AnimFrame);

        if (curNode.pSkeletonNode->BodyType == OG_SUBMESH_PROPELLER)
        {
            if (m_pProcedureAnimation)
            {
                m_pProcedureAnimation->Update(_ElapsedTime, mNodeWorld, mNodeWorld);
            }
        }
        MatrixMultiply(curNode.mTransform, mNodeWorld, mWorld);

        if (curNode.pSkeletonNode->BodyType != OG_SUBMESH_DUMMY && curNode.pSkeletonNode->BodyType != OG_SUBMESH_ACTPOINT)
        {
            curNode.OBB.Create(((IOGMesh*)curNode.pSkeletonNode->pBody)->GetAABB());
            curNode.OBB.UpdateTransform(curNode.mTransform);
        }
        if (curNode.pSkeletonNode->BodyType == OG_SUBMESH_ACTPOINT)
        {
            if (curNode.pSkeletonNode->pBody)
            {
                IOGActivePoint* pPoint = (IOGActivePoint*)curNode.pSkeletonNode->pBody;
                MatrixVecMultiply(curNode.vCenter, pPoint->pos, mNodeWorld);
            }
        }
    }
}


// render.
void COGSgNode::Render (IOGCamera* _pCamera, OGRenderPass _Pass)
{
    if (!m_bActive)
        return;

    unsigned int NumMeshNodes = m_MeshNodes.size();
    for (unsigned int i = 0; i < NumMeshNodes; ++i)
    {
        OGSgMeshNode& curNode = m_MeshNodes[i];
        if (curNode.pSkeletonNode->BodyType != OG_SUBMESH_DUMMY && curNode.pSkeletonNode->BodyType != OG_SUBMESH_ACTPOINT)
        {
            bool bContributes = false;
            if (_Pass == OG_RENDERPASS_SHADOWMAP)
            {
                bContributes = curNode.pSkeletonNode->SceneProps & OG_SCENEPROP_SHADOWCASTER;
            }
            else
            {
                bContributes = true;
            }
            if (bContributes)
            {
                m_pRenderable->Render(curNode.mTransform, i, _Pass);
            }
        }
    }
}


// get physics.
IOGPhysicalObject* COGSgNode::GetPhysics ()
{
    return m_pPhysics;
}


// Get active point
bool COGSgNode::GetActivePoint (OGVec3& _point, const std::string& _Alias)
{
    unsigned int NumMeshNodes = m_MeshNodes.size();
    for (unsigned int i = 0; i < NumMeshNodes; ++i)
    {
        OGSgMeshNode& curNode = m_MeshNodes[i];
        if (curNode.pSkeletonNode->BodyType == OG_SUBMESH_ACTPOINT)
        {
            if (curNode.pSkeletonNode->pBody)
            {
                IOGActivePoint* pPoint = (IOGActivePoint*)curNode.pSkeletonNode->pBody;
                if ( pPoint->alias.compare(_Alias) == 0)
                {
                    _point = curNode.vCenter;
                    return true;
                }
            }
        }
    }

    return false;
}


// start animation.
void COGSgNode::StartAnimation (const std::string& _Alias)
{
    IOGAnimation* pAnim = m_pRenderable->GetAnimation(_Alias);
    m_pBakedAnimation->Start(pAnim);
}


// Set active state
void COGSgNode::Activate (bool _bActive)
{
    m_bActive = _bActive;
}
