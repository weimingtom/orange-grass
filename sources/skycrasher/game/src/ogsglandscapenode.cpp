/*
 *  ogsglandscapenode.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "Game.h"
#include "ogsglandscapenode.h"


COGSgLandscapeNode::COGSgLandscapeNode ()
    : m_pRenderable(NULL)
    , m_bActive(false)
    , m_pSkeleton(NULL)
{
}


COGSgLandscapeNode::COGSgLandscapeNode (IOGModel* _pRenderable) 
    : m_pRenderable(_pRenderable)
    , m_bActive(true)
    , m_pSkeleton(NULL)
{
    m_OBB.Create(m_pRenderable->GetAABB());
    MatrixIdentity(m_World);

    m_pSkeleton = m_pRenderable->GetModelSkeleton();
    if (m_pSkeleton)
    {
        unsigned int NumMeshNodes = m_pSkeleton->GetNumNodes();
        m_MeshNodes.reserve(NumMeshNodes);
        for (unsigned int i = 0; i < NumMeshNodes; ++i)
        {
            OGSgMeshNode node;
            node.pSkeletonNode = m_pSkeleton->GetNode(i);
            m_MeshNodes.push_back(node);
        }
    }
}


COGSgLandscapeNode::~COGSgLandscapeNode () 
{
    m_MeshNodes.clear();
    m_pRenderable = NULL;
    m_pSkeleton = NULL;
}


// get world transform.
const OGMatrix& COGSgLandscapeNode::GetWorldTransform () const
{
    return m_World;
}


// Get OBB
const IOGObb& COGSgLandscapeNode::GetOBB () const
{
    return m_OBB;
}


// update transform.
void COGSgLandscapeNode::Update (unsigned long _ElapsedTime)
{
    OGMatrix mNodeWorld;
    unsigned int NumMeshNodes = m_MeshNodes.size();
    for (unsigned int i = 0; i < NumMeshNodes; ++i)
    {
        OGSgMeshNode& curNode = m_MeshNodes[i];
        m_pSkeleton->GetWorldMatrix(mNodeWorld, i, 0);
        MatrixMultiply(curNode.mTransform, mNodeWorld, m_World);
        if (curNode.pSkeletonNode->BodyType != OG_SUBMESH_DUMMY && curNode.pSkeletonNode->BodyType != OG_SUBMESH_ACTPOINT)
        {
            curNode.OBB.Create(((IOGMesh*)curNode.pSkeletonNode->pBody)->GetAABB());
            curNode.OBB.UpdateTransform(curNode.mTransform);
        }
    }
}


// render.
void COGSgLandscapeNode::Render (IOGCamera* _pCamera, OGRenderPass _Pass)
{
    if (!m_bActive)
        return;

    unsigned int NumMeshNodes = m_MeshNodes.size();
    for (unsigned int i = 0; i < NumMeshNodes; ++i)
    {
        OGSgMeshNode& curNode = m_MeshNodes[i];
        if (curNode.pSkeletonNode->BodyType != OG_SUBMESH_DUMMY && curNode.pSkeletonNode->BodyType != OG_SUBMESH_ACTPOINT)
        {
            if (_pCamera->GetFrustum().CheckObb(curNode.OBB))
                m_pRenderable->Render(curNode.mTransform, i, _Pass);
        }
    }
}


// get physics.
IOGPhysicalObject* COGSgLandscapeNode::GetPhysics ()
{
    return NULL;
}


// Get active point
bool COGSgLandscapeNode::GetActivePoint (OGVec3& _point, const std::string& _Alias)
{
    return false;
}


// start animation.
void COGSgLandscapeNode::StartAnimation (const std::string& _Alias)
{
}


// Set active state
void COGSgLandscapeNode::Activate (bool _bActive)
{
    m_bActive = _bActive;
}
