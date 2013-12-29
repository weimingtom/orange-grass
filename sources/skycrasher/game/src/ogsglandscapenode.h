/*
*  ogsglandscapenode.h
*  OrangeGrass
*
*  Created by Viacheslav Bogdanov on 12.11.09.
*  Copyright 2009 __MyCompanyName__. All rights reserved.
*
*/
#ifndef OGSGLANDSCAPENODE_H_
#define OGSGLANDSCAPENODE_H_

#include "IOGMath.h"
#include "IOGSgNode.h"
#include "IOGModel.h"


class COGSgLandscapeNode : public IOGSgNode
{
    COGSgLandscapeNode ();

public:
    COGSgLandscapeNode (IOGModel* _pRenderable);
    virtual ~COGSgLandscapeNode ();

    // get world transform.
    virtual const OGMatrix& GetWorldTransform () const;

    // Get OBB
    virtual const IOGObb& GetOBB () const;

    // render.
    virtual void Render (IOGCamera* _pCamera, OGRenderPass _Pass);

    // update transform.
    virtual void Update (unsigned long _ElapsedTime);

    // get physics.
    virtual IOGPhysicalObject* GetPhysics ();

    // Get type of the renderable.
    virtual RenderableType GetRenderableType () const {return OG_RENDERABLE_TERRAIN;}

    // start animation.
    virtual void StartAnimation (const std::string& _Alias);

    // Get active point
    virtual bool GetActivePoint (OGVec3& _point, const std::string& _Alias);

    // Get active state
    virtual bool IsActive () const { return m_bActive; }

    // Set active state
    virtual void Activate (bool _bActive);

protected:

    IOGModel*               m_pRenderable;
    bool                    m_bActive;
    IOGObb                  m_OBB;
    OGMatrix                m_World;
    IOGModelSkeleton*       m_pSkeleton;
    std::vector<OGSgMeshNode>   m_MeshNodes;
};

#endif
