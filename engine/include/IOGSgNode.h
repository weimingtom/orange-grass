#ifndef IOGSGNODE_H_
#define IOGSGNODE_H_

#include "Mathematics.h"


class IOGSgNode
{
public:
	// destructor
	virtual ~IOGSgNode () {}

	// get world transform.
	virtual const MATRIX& GetWorldTransform () const = 0;

	// set world transform.
	virtual void SetWorldTransform (const MATRIX& _mT) = 0;

	// set world transform.
	virtual void SetWorldTransform (const Vec3& _vPos, const Vec3& _vRot) = 0;

	// get renderable.
	virtual IOGRenderable* GetRenderable () = 0;
};

#endif
