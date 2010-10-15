/*
 *  ogscenegraph.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogscenegraph.h"
#include "ogsgnode.h"
#include "IOGMath.h"
#include <algorithm>


COGSceneGraph::COGSceneGraph () : m_pLandscapeNode(NULL)
{
	m_pGlobalVars = GetGlobalVars();
	m_fViewDistance = m_pGlobalVars->GetFVar("view_distance");
}


COGSceneGraph::~COGSceneGraph ()
{
	Clear();
}


// Clear scene graph
void COGSceneGraph::Clear ()
{
	OG_SAFE_DELETE(m_pLandscapeNode);
	ClearNodesList(m_NodesList);
	ClearNodesList(m_EffectNodesList);
	ClearNodesList(m_TransparentNodesList);
	TStaticNodesMap::iterator s_iter= m_StaticNodes.begin();
	for (; s_iter != m_StaticNodes.end(); ++s_iter)
	{
		ClearNodesList(s_iter->second);
	}
}


// Create scene graph node
IOGSgNode* COGSceneGraph::CreateNode (IOGRenderable* _pRenderable, IOGPhysicalObject* _pPhysics)
{
    COGSgNode* pNode = new COGSgNode(_pRenderable, _pPhysics);
    return pNode;
}


// Add scene graph node
void COGSceneGraph::AddNode (IOGSgNode* _pNode)
{
    m_NodesList.push_back(_pNode);
}


// Add static scene graph node
void COGSceneGraph::AddStaticNode (IOGSgNode* _pNode, IOGTexture* _pTexture)
{
	TStaticNodesMap::iterator entry = m_StaticNodes.find(_pTexture);
	if (entry != m_StaticNodes.end())
	{
		entry->second.push_back(_pNode);
	}
	else
	{
		m_StaticNodes[_pTexture].push_back(_pNode);
	}
}


// Add transparent scene graph node
void COGSceneGraph::AddTransparentNode (IOGSgNode* _pNode)
{
    m_TransparentNodesList.push_back(_pNode);
}


// Add landscape scene graph node
void COGSceneGraph::AddLandscapeNode (IOGSgNode* _pNode)
{
	m_pLandscapeNode = _pNode;
}


// Add effect scene graph node
void COGSceneGraph::AddEffectNode (IOGSgNode* _pNode)
{
    m_EffectNodesList.push_back(_pNode);
}


// Remove scene graph node
void COGSceneGraph::RemoveNode (IOGSgNode* _pNode)
{
    if (!_pNode)
        return;

    switch (_pNode->GetRenderable()->GetRenderableType())
    {
    case OG_RENDERABLE_MODEL:
        {
	        if (RemoveNodeFromList(_pNode, m_NodesList))
		        return;

            if (RemoveNodeFromList(_pNode, m_TransparentNodesList))
		        return;

	        TStaticNodesMap::iterator s_iter= m_StaticNodes.begin();
	        for (; s_iter != m_StaticNodes.end(); ++s_iter)
	        {
		        if (RemoveNodeFromList(_pNode, s_iter->second))
			        return;
	        }
        }
        break;

    case OG_RENDERABLE_TERRAIN:
        {
            OG_SAFE_DELETE(m_pLandscapeNode);
        }
        break;

    case OG_RENDERABLE_EFFECT:
        {
	        if (RemoveNodeFromList(_pNode, m_EffectNodesList))
		        return;
        }
        break;
    }
}


// Update scene graph.
void COGSceneGraph::Update (unsigned long _ElapsedTime)
{
    TNodesList::iterator iter = m_EffectNodesList.begin();
    for (; iter != m_EffectNodesList.end(); ++iter)
    {
		IOGSgNode* pNode = (*iter);
		const MATRIX& mT = pNode->GetWorldTransform();
		Vec3 vPos = Vec3(mT.f[12], mT.f[13], mT.f[14]);
		((IOGEffect*)pNode->GetRenderable())->UpdatePosition(vPos);
        (*iter)->Update(_ElapsedTime);
    }
}


// Render scene graph.
void COGSceneGraph::RenderScene (IOGCamera* _pCamera)
{
	RenderNodesList(_pCamera, m_NodesList);
	TStaticNodesMap::iterator s_iter= m_StaticNodes.begin();
	for (; s_iter != m_StaticNodes.end(); ++s_iter)
	{
		RenderNodesList(_pCamera, s_iter->second);
	}
}


// Render landscape.
void COGSceneGraph::RenderLandscape (IOGCamera* _pCamera)
{
	if (!m_pLandscapeNode)
	{
		return;
	}

	MATRIX mT;
    MatrixIdentity(mT);
	m_pLandscapeNode->GetRenderable()->Render(mT, 0);
}


// Render effects.
void COGSceneGraph::RenderEffects (IOGCamera* _pCamera)
{
	const MATRIX& mView = _pCamera->GetViewMatrix();

    Vec3 vUp, vRight, vLook;
	MatrixGetBasis(vRight, vUp, vLook, mView);
	vUp.normalize();
	vRight.normalize();

	OG_LOG_INFO("SG Up = [%f, %f, %f]", 
		vUp.x, vUp.y, vUp.z);

	float fCameraZ = _pCamera->GetPosition().z;
    TNodesList::iterator iter = m_EffectNodesList.begin();
    for (; iter != m_EffectNodesList.end(); ++iter)
    {
		IOGSgNode* pNode = (*iter);
		float fObjectZ = pNode->GetOBB().m_vCenter.z;

		//if (fObjectZ <= fCameraZ)
		{
			//if ((fCameraZ - fObjectZ) < m_fViewDistance)
			{
                ((IOGEffect*)pNode->GetRenderable())->SetBillboardVectors(vUp, vRight);
				pNode->Render();
			}
		}
    }
}


// Render transparent nodes.
void COGSceneGraph::RenderTransparentNodes (IOGCamera* _pCamera)
{
	RenderNodesList(_pCamera, m_TransparentNodesList);
}


// Render all effects.
void COGSceneGraph::RenderAllEffects (IOGCamera* _pCamera)
{
	const MATRIX& mView = _pCamera->GetViewMatrix();

    Vec3 vUp, vRight, vLook;
	MatrixGetBasis(vRight, vUp, vLook, mView);
	vUp.normalize();
	vRight.normalize();

    TNodesList::iterator iter = m_EffectNodesList.begin();
    for (; iter != m_EffectNodesList.end(); ++iter)
    {
		IOGSgNode* pNode = (*iter);
        ((IOGEffect*)pNode->GetRenderable())->SetBillboardVectors(vUp, vRight);
        pNode->Render();
    }
}


// Render the whole scene.
void COGSceneGraph::RenderAll (IOGCamera* _pCamera)
{
	RenderLandscape(_pCamera);
	RenderWholeNodesList(_pCamera, m_NodesList);
	TStaticNodesMap::iterator s_iter= m_StaticNodes.begin();
	for (; s_iter != m_StaticNodes.end(); ++s_iter)
	{
		RenderWholeNodesList(_pCamera, s_iter->second);
	}
	RenderWholeNodesList(_pCamera, m_TransparentNodesList);
}


// Remove node from list
bool COGSceneGraph::RemoveNodeFromList(IOGSgNode* _pNode, TNodesList& _List)
{
	TNodesList::iterator iter = std::find(_List.begin(), _List.end(), _pNode);
	if (iter != _List.end())
	{
		OG_SAFE_DELETE((*iter));
		_List.erase(iter);
		return true;
	}
	return false;
}


// clear nodes list
void COGSceneGraph::ClearNodesList(TNodesList& _List)
{
    TNodesList::iterator iter = _List.begin();
    for (; iter != _List.end(); ++iter)
    {
		OG_SAFE_DELETE((*iter));
	}
	_List.clear();
}


// render nodes list
void COGSceneGraph::RenderNodesList(IOGCamera* _pCamera, TNodesList& _List)
{
	float fCameraZ = _pCamera->GetPosition().z;
    TNodesList::iterator iter = _List.begin();
    for (; iter != _List.end(); ++iter)
    {
		IOGSgNode* pNode = (*iter);
		float fObjectZ = pNode->GetOBB().m_vCenter.z;

		if (fObjectZ <= fCameraZ)
		{
			if ((fCameraZ - fObjectZ) < m_fViewDistance)
			{
				pNode->Render();
			}
		}
    }
}


// render whole nodes list
void COGSceneGraph::RenderWholeNodesList(IOGCamera* _pCamera, TNodesList& _List)
{
    TNodesList::iterator iter = _List.begin();
    for (; iter != _List.end(); ++iter)
    {
        (*iter)->Render();
	}
}
