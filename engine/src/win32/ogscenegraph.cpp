/*
 *  ogscenegraph.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "orangegrass.h"
#include "ogscenegraph.h"
#include "ogsgnode.h"
#include "IOGMath.h"
#include <algorithm>


COGSceneGraph::COGSceneGraph ()
{
}


COGSceneGraph::~COGSceneGraph ()
{
    std::vector<IOGSgNode*>::iterator iter = m_NodesList.begin();
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
	std::vector<IOGSgNode*>::iterator iter = std::find(m_NodesList.begin(), m_NodesList.end(), _pNode);
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

    std::vector<IOGSgNode*>::iterator iter = m_NodesList.begin();
    for (; iter != m_NodesList.end(); ++iter)
    {
        mModelView = (*iter)->GetWorldTransform();
        MatrixMultiply(mModelView, mModelView, _mView);
        (*iter)->GetRenderable()->Render(mModelView);
    }
}
