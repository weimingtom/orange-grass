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
	virtual void SetWorldTransform (const Vec3& _vPos, const Vec3& _vRot, const Vec3& _vScale) = 0;

	// get position.
	virtual const Vec3& GetPosition () const = 0;

	// get rotation.
	virtual const Vec3& GetRotation () const = 0;

	// get scaling.
	virtual const Vec3& GetScaling () const = 0;

	// set position.
	virtual void SetPosition (const Vec3& _vPos) = 0;

	// set rotation.
	virtual void SetRotation (const Vec3& _vRot) = 0;

	// set scaling.
	virtual void SetScaling (const Vec3& _vScale) = 0;

	// Update transforms.
	virtual void Update (int _ElapsedTime) = 0;

	// Get transformed AABB
	virtual const IOGAabb& GetTransformedAABB () const = 0;

	// get renderable.
	virtual IOGRenderable* GetRenderable () = 0;
};

#endif
