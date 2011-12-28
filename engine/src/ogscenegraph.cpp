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
#include "ogsgeffectnode.h"
#include "ogsglandscapenode.h"
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
IOGSgNode* COGSceneGraph::CreateNode (IOGModel* _pRenderable, IOGPhysicalObject* _pPhysics)
{
    COGSgNode* pNode = new COGSgNode(_pRenderable, _pPhysics);
    return pNode;
}


// Create scene graph effect node
IOGSgNode* COGSceneGraph::CreateEffectNode (IOGEffect* _pRenderable, IOGPhysicalObject* _pPhysics)
{
    COGSgEffectNode* pNode = new COGSgEffectNode(_pRenderable, _pPhysics);
    return pNode;
}


// Create scene graph landscape node
IOGSgNode* COGSceneGraph::CreateLandscapeNode (IOGTerrain* _pRenderable)
{
    COGSgLandscapeNode* pNode = new COGSgLandscapeNode(_pRenderable);
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
    OG_SAFE_DELETE(m_pLandscapeNode);
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

    switch (_pNode->GetRenderableType())
    {
    case OG_RENDERABLE_MODEL:
        {
	        RemoveNodeFromList(_pNode, m_NodesList);
            RemoveNodeFromList(_pNode, m_TransparentNodesList);

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
        pNode->Update(_ElapsedTime);
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
	if (m_pLandscapeNode)
	{
        m_pLandscapeNode->Render();
	}
}


// Render effects.
void COGSceneGraph::RenderEffects (IOGCamera* _pCamera)
{
	const OGMatrix& mView = _pCamera->GetViewMatrix();

    OGVec3 vUp, vRight, vLook;
	MatrixGetBasis(vRight, vUp, vLook, mView);
	vUp.normalize();
	vRight.normalize();
	vLook.normalize();

    TNodesList::iterator iter = m_EffectNodesList.begin();
    for (; iter != m_EffectNodesList.end(); ++iter)
    {
		COGSgEffectNode* pNode = (COGSgEffectNode*)(*iter);
		if (IsVisible(_pCamera, pNode))
		{
			pNode->SetBillboardVectors(vLook, vUp, vRight);
			pNode->Render();
		}
    }
}


// Render transparent nodes.
void COGSceneGraph::RenderTransparentNodes (IOGCamera* _pCamera)
{
    TNodesList::iterator iter = m_TransparentNodesList.begin();
    for (; iter != m_TransparentNodesList.end(); ++iter)
    {
		COGSgNode* pNode = (COGSgNode*)(*iter);
		if (IsVisible(_pCamera, pNode))
		{
			pNode->RenderTransparent();
		}
    }
}


// Render all effects.
void COGSceneGraph::RenderAllEffects (IOGCamera* _pCamera)
{
	const OGMatrix& mView = _pCamera->GetViewMatrix();

    OGVec3 vUp, vRight, vLook;
	MatrixGetBasis(vRight, vUp, vLook, mView);
	vUp.normalize();
	vRight.normalize();
	vLook.normalize();

    TNodesList::iterator iter = m_EffectNodesList.begin();
    for (; iter != m_EffectNodesList.end(); ++iter)
    {
		COGSgEffectNode* pNode = (COGSgEffectNode*)(*iter);
        pNode->SetBillboardVectors(vLook, vUp, vRight);
        pNode->Render();
    }
}


// Render the whole scene.
void COGSceneGraph::RenderAll (IOGCamera* _pCamera)
{
	if (m_pLandscapeNode)
	{
		((COGSgLandscapeNode*)m_pLandscapeNode)->RenderAll();
	}

	RenderWholeNodesList(_pCamera, m_NodesList);
	TStaticNodesMap::iterator s_iter= m_StaticNodes.begin();
	for (; s_iter != m_StaticNodes.end(); ++s_iter)
	{
		RenderWholeNodesList(_pCamera, s_iter->second);
	}

	TNodesList::iterator iter = m_TransparentNodesList.begin();
    for (; iter != m_TransparentNodesList.end(); ++iter)
    {
        ((COGSgNode*)(*iter))->RenderTransparent();
	}
}


// Remove node from list
bool COGSceneGraph::RemoveNodeFromList(IOGSgNode* _pNode, TNodesList& _List)
{
	TNodesList::iterator iter = std::find(_List.begin(), _List.end(), _pNode);
	if (iter != _List.end())
	{
		_List.erase(iter);
		return true;
	}
	return false;
}


// clear nodes list
void COGSceneGraph::ClearNodesList(TNodesList& _List)
{
	_List.clear();
}


// render nodes list
void COGSceneGraph::RenderNodesList(IOGCamera* _pCamera, TNodesList& _List)
{
    TNodesList::iterator iter = _List.begin();
    for (; iter != _List.end(); ++iter)
    {
		IOGSgNode* pNode = (*iter);
		if (IsVisible(_pCamera, pNode))
		{
			pNode->Render();
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


// check object visibility
bool COGSceneGraph::IsVisible(const IOGCamera* _pCamera, const IOGSgNode* _pNode) const
{
	if (!_pNode->GetOBB().m_bTransformed)
		return true;

	return _pCamera->GetFrustum().CheckObb(_pNode->GetOBB());
}
