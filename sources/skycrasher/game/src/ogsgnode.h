/*
*  ogsgnode.h
*  OrangeGrass
*
*  Created by Viacheslav Bogdanov on 12.11.09.
*  Copyright 2009 __MyCompanyName__. All rights reserved.
*
*/
#ifndef OGSGNODE_H_
#define OGSGNODE_H_

#include "IOGMath.h"
#include "IOGSgNode.h"
#include "IOGAnimation.h"


class COGSgNode : public IOGSgNode
{
    COGSgNode ();

public:
    COGSgNode (IOGModel* _pRenderable, IOGPhysicalObject* _pPhysics);
    virtual ~COGSgNode ();

    // get world transform.
    virtual const OGMatrix& GetWorldTransform () const;

    // Get OBB
    virtual const IOGObb& GetOBB () const;

    // render.
    virtual void Render ();

    // update transform.
    virtual void Update (unsigned long _ElapsedTime);

    // get physics.
    virtual IOGPhysicalObject* GetPhysics ();

    // Get type of the renderable.
    virtual RenderableType GetRenderableType () const {return OG_RENDERABLE_MODEL;}

    // start animation.
    virtual void StartAnimation (const std::string& _Alias);

    // Get active point
    virtual bool GetActivePoint (OGVec3& _point, const std::string& _Alias);

    // Get active state
    virtual bool IsActive () const { return m_bActive; }

    // Set active state
    virtual void Activate (bool _bActive);

protected:

    IOGModel*                   m_pRenderable;
    IOGModelSkeleton*           m_pSkeleton;
    IOGPhysicalObject*          m_pPhysics;
    bool                        m_bActive;

    IOGAnim*                    m_pBakedAnimation;
    IOGAnim*                    m_pProcedureAnimation;

    std::vector<OGSgMeshNode>   m_MeshNodes;
};

#endif
