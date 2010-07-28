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
	virtual void SetWorldTransform (const MATRIX& _mT);

	// set world transform.
	virtual void SetWorldTransform (const Vec3& _vPos, const Vec3& _vRot);

	// get renderable.
	virtual IOGRenderable* GetRenderable ();

private:

    IOGRenderable*  m_pRenderable;
    MATRIX          m_mWorld;
};

#endif
