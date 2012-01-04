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
#include "IOGAnimationController.h"
#include "IOGTerrain.h"


class COGSgLandscapeNode : public IOGSgNode
{
	COGSgLandscapeNode ();

public:
	COGSgLandscapeNode (IOGTerrain* _pRenderable);
	virtual ~COGSgLandscapeNode ();

	// get world transform.
	virtual const OGMatrix& GetWorldTransform () const;

	// Get OBB
	virtual const IOGObb& GetOBB () const;

	// Get transformed OBBs list
	virtual const std::vector<IOGObb>& GetTransformedOBBs () const {return m_TransformedOBBs;}

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
    virtual bool GetActivePoint (OGVec3& _point, const std::string& _Alias);

	// Get active state
	virtual bool IsActive () const { return m_bActive; }

	// Set active state
	virtual void Activate (bool _bActive);

protected:

    IOGTerrain*             m_pRenderable;
    bool					m_bActive;
    IOGObb                  m_OBB;
    OGMatrix                  m_World;
	std::vector<IOGObb>		m_TransformedOBBs;
};

#endif
