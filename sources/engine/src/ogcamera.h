/*
 *  ogcamera.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 14.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef COGCAMERA_H_
#define COGCAMERA_H_

#include "IOGCamera.h"


class COGCamera : public IOGCamera
{
public:
	COGCamera ();
	virtual ~COGCamera ();
	
	// setup camera viewport.
	virtual void SetupViewport (const OGMatrix& _mProjection, float _fFOV);
	
	// setup camera.
	virtual void Setup (const OGVec3& _vPosition, const OGVec3& _vTarget, const OGVec3& _vUp);
	
	// get camera position.
	virtual const OGVec3& GetPosition () const { return m_Position; }
	
	// get camera direction.
	virtual const OGVec3& GetDirection () const { return m_Direction; }
	
	// get camera up.
	virtual const OGVec3& GetUp () const { return m_Up; }
	
	// get camera right.
	virtual const OGVec3& GetRight () const { return m_Right; }
	
	// get camera target.
	virtual const OGVec3& GetTarget () const { return m_Target; }

	// move camera in defined direction
	virtual void Strafe(float _fSpeed, const OGVec3& _vDir);

	// move camera forward/backward
	virtual void Move(float _fSpeed);
	
	// update camera.
	virtual void Update ();
	
	// get camera view matrix.
	virtual const OGMatrix& GetViewMatrix () const;

	// get viewing frustum.
	virtual const IOGFrustum& GetFrustum () const { return m_Frustum; }

	// get left and right edges.
	virtual void GetEdges (OGVec3& _vLeft, OGVec3& _vRight, float _fFOV, float _fDist);

private:
	
	OGMatrix		m_View;
	OGMatrix		m_Projection;
	OGMatrix		m_ViewProj;
	OGVec3		m_Position;
	OGVec3		m_Direction;
	OGVec3		m_Target;
	OGVec3		m_Up;
	OGVec3		m_Right;
	float		m_fFOV;
	bool		m_bDirty;
	IOGFrustum	m_Frustum;
};

#endif
