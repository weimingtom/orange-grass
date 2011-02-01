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

#include "Mathematics.h"
#include "IOGSgNode.h"
#include "IOGAnimationController.h"


class COGSgNode : public IOGSgNode
{
	COGSgNode ();

public:
	COGSgNode (IOGModel* _pRenderable, IOGPhysicalObject* _pPhysics);
	virtual ~COGSgNode ();

	// get world transform.
	virtual const MATRIX& GetWorldTransform () const;

	// Get OBB
	virtual const IOGObb& GetOBB () const;

	// Get transformed OBBs list
	virtual const std::vector<IOGObb>& GetTransformedOBBs () const {return m_TransformedOBBs;}

	// render.
	virtual void Render ();

	// render.
	virtual void RenderTransparent ();

	// update transform.
	virtual void Update (unsigned long _ElapsedTime);

	// get physics.
	virtual IOGPhysicalObject* GetPhysics ();

	// Get type of the renderable.
    virtual RenderableType GetRenderableType () const {return OG_RENDERABLE_MODEL;}

	// get animation controller.
    virtual IOGAnimationController* GetAnimator () { return m_pAnimator;}

	// start animation.
    virtual void StartAnimation (const std::string& _Alias);

	// Get active point
    virtual bool GetActivePoint (Vec3& _point, const std::string& _Alias);

	// Get active state
	virtual bool IsActive () const { return m_bActive; }

	// Set active state
	virtual void Activate (bool _bActive);

protected:

    IOGModel*               m_pRenderable;
    IOGPhysicalObject*      m_pPhysics;
    IOGAnimationController* m_pAnimator;
    bool					m_bActive;
    unsigned int            m_AnimFrame;
	float					m_fSpin;
	std::vector<IOGObb>		m_TransformedOBBs;
};

#endif
