#ifndef OGSGNODE_H_
#define OGSGNODE_H_

#include "Mathematics.h"
#include "IOGSgNode.h"


class COGSgNode : public IOGSgNode
{
	COGSgNode ();

public:
	COGSgNode (IOGRenderable* _pRenderable);
	virtual ~COGSgNode ();

	// get world transform.
	virtual const MATRIX& GetWorldTransform () const;

	// set world transform.
	virtual void SetWorldTransform (const Vec3& _vPos, const Vec3& _vRot, const Vec3& _vScale);

	// get position.
	virtual const Vec3& GetPosition () const;

	// get rotation.
	virtual const Vec3& GetRotation () const;

	// get scaling.
	virtual const Vec3& GetScaling () const;

	// set position.
	virtual void SetPosition (const Vec3& _vPos);

	// set rotation.
	virtual void SetRotation (const Vec3& _vRot);

	// set scaling.
	virtual void SetScaling (const Vec3& _vScale);

	// Update transforms.
	virtual void Update (int _ElapsedTime);

	// Get transformed AABB
	virtual const IOGAabb& GetTransformedAABB () const;

	// get renderable.
	virtual IOGRenderable* GetRenderable ();

private:

    IOGRenderable*  m_pRenderable;
    MATRIX          m_mWorld;
    Vec3            m_vPosition;
    Vec3            m_vRotation;
    Vec3            m_vScaling;
	IOGAabb			m_TransformedAabb;
};

#endif
