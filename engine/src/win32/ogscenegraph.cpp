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
	TStaticNodesMap::iterator s_iter= m_StaticNodes.begin();
	for (; s_iter != m_StaticNodes.end(); ++s_iter)
	{
		ClearNodesList(s_iter->second);
	}
}


// Create scene graph node
IOGSgNode* COGSceneGraph::CreateNode (IOGRenderable* _pRenderable)
{
    COGSgNode* pNode = new COGSgNode(_pRenderable);
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
        //(*iter)->Update();
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

	const MATRIX& mView = _pCamera->GetViewMatrix();
	m_pLandscapeNode->GetRenderable()->Render(mView);
}


// Render effects.
void COGSceneGraph::RenderEffects (IOGCamera* _pCamera)
{
	RenderNodesList(_pCamera, m_EffectNodesList);
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
	MATRIX mModelView;
	const MATRIX& mView = _pCamera->GetViewMatrix();

	float fCameraZ = _pCamera->GetPosition().z;
    TNodesList::iterator iter = _List.begin();
    for (; iter != _List.end(); ++iter)
    {
		IOGSgNode* pNode = (*iter);
		float fObjectZ = pNode->GetOBB().m_vCenter.z;

		if (fObjectZ <= fCameraZ)
		{
			if ((fCameraZ - fObjectZ) < 200.0f)
			{
				const MATRIX& mWorld = pNode->GetWorldTransform();
				MatrixMultiply(mModelView, mWorld, mView);
				pNode->GetRenderable()->Render(mModelView);
			}
		}
    }
}


// render whole nodes list
void COGSceneGraph::RenderWholeNodesList(IOGCamera* _pCamera, TNodesList& _List)
{
	MATRIX mModelView;
	const MATRIX& mView = _pCamera->GetViewMatrix();

    TNodesList::iterator iter = _List.begin();
    for (; iter != _List.end(); ++iter)
    {
        const MATRIX& mWorld = (*iter)->GetWorldTransform();
        MatrixMultiply(mModelView, mWorld, mView);
        (*iter)->GetRenderable()->Render(mModelView);
	}
}
