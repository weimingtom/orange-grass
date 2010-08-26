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
#include "ogcamera.h"
#include "oglight.h"
#include "IOGMath.h"
#include <algorithm>


COGSceneGraph::COGSceneGraph () :	m_pCamera(NULL),
									m_pLight(NULL)
{
	m_pCamera = new COGCamera ();
	m_pLight = new COGLight ();
}


COGSceneGraph::~COGSceneGraph ()
{
	OG_SAFE_DELETE(m_pCamera);
	OG_SAFE_DELETE(m_pLight);

	Clear();
}


// Clear scene graph
void COGSceneGraph::Clear ()
{
    std::list<IOGSgNode*>::iterator iter = m_NodesList.begin();
    for (; iter != m_NodesList.end(); ++iter)
    {
		OG_SAFE_DELETE((*iter));
	}
	m_NodesList.clear();
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


// Remove scene graph node
void COGSceneGraph::RemoveNode (IOGSgNode* _pNode)
{
	std::list<IOGSgNode*>::iterator iter = std::find(m_NodesList.begin(), m_NodesList.end(), _pNode);
	if (iter != m_NodesList.end())
	{
		OG_SAFE_DELETE((*iter));
		m_NodesList.erase(iter);
	}
}


// Render.
void COGSceneGraph::Render (const MATRIX& _mView)
{
	MATRIX mModelView;

	float fCameraZ = m_pCamera->GetPosition().z;
    std::list<IOGSgNode*>::iterator iter = m_NodesList.begin();
    for (; iter != m_NodesList.end(); ++iter)
    {
		IOGSgNode* pNode = (*iter);
		float fObjectZ = pNode->GetOBB().m_vCenter.z;

		if (fObjectZ <= fCameraZ)
		{
			if ((fCameraZ - fObjectZ) < 300.0f)
			{
				const MATRIX& mWorld = pNode->GetWorldTransform();
				MatrixMultiply(mModelView, mWorld, _mView);
				pNode->GetRenderable()->Render(mModelView);
			}
		}
    }
}


// Render the whole scene.
void COGSceneGraph::RenderAll (const MATRIX& _mView)
{
	MATRIX mModelView;

    std::list<IOGSgNode*>::iterator iter = m_NodesList.begin();
    for (; iter != m_NodesList.end(); ++iter)
    {
        const MATRIX& mWorld = (*iter)->GetWorldTransform();
        MatrixMultiply(mModelView, mWorld, _mView);
        (*iter)->GetRenderable()->Render(mModelView);
    }
}


// Get scene camera.
IOGCamera* COGSceneGraph::GetCamera ()
{
	return m_pCamera;
}


// Get scene light.
IOGLight* COGSceneGraph::GetLight ()
{
	return m_pLight;
}
