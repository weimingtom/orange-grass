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

#include "Mathematics.h"
#include "IOGSgNode.h"
#include "IOGAnimationController.h"
#include "IOGTerrain.h"


class COGSgLandscapeNode : public IOGSgNode
{
	COGSgLandscapeNode ();

public:
	COGSgLandscapeNode (IOGTerrain* _pRenderable);
	virtual ~COGSgLandscapeNode ();

	// get world transform.
	virtual const MATRIX& GetWorldTransform () const;

	// Get OBB
	virtual const IOGObb& GetOBB () const;

	// render.
	virtual void Render ();

	// render all nodes.
	void RenderAll ();

	// update transform.
	virtual void Update (unsigned long _ElapsedTime);

	// get physics.
	virtual IOGPhysicalObject* GetPhysics ();

	// Get type of the renderable.
    virtual RenderableType GetRenderableType () const {return OG_RENDERABLE_TERRAIN;}

	// get animation controller.
    virtual IOGAnimationController* GetAnimator () { return NULL; }

	// start animation.
    virtual void StartAnimation (const std::string& _Alias);

	// Get active point
    virtual bool GetActivePoint (Vec3& _point, const std::string& _Alias);

	// Get active state
	virtual bool IsActive () const { return m_bActive; }

	// Set active state
	virtual void Activate (bool _bActive);

protected:

    bool					m_bActive;
    IOGTerrain*             m_pRenderable;
    IOGObb                  m_OBB;
    MATRIX                  m_World;
};

#endif
