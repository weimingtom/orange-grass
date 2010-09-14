/*
 *  IOGCamera.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 14.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGCAMERA_H_
#define IOGCAMERA_H_

#include "Mathematics.h"


class IOGCamera
{
public:
	virtual ~IOGCamera () {}
	
	// setup camera.
	virtual void Setup (const Vec3& _vPosition, const Vec3& _vDirection, const Vec3& _vUp) = 0;
	
	// get camera position.
	virtual const Vec3& GetPosition () const = 0;
	
	// get camera direction.
	virtual const Vec3& GetDirection () const = 0;
	
	// rotate view.
	virtual void RotateView (float _fAngle, const Vec3& _vAxis) = 0;
	
	// move camera in defined direction
	virtual void Strafe(float _fSpeed, const Vec3& _vDir) = 0;
	
	// move camera forward/backward
	virtual void Move(float _fSpeed) = 0;
	
	// update camera.
	virtual void Update () = 0;
	
	// get camera view matrix.
	virtual const MATRIX& GetViewMatrix () const = 0;

	// get left and right edges.
	virtual void GetEdges (Vec3& _vLeft, Vec3& _vRight, float _fFOV, float _fDist) = 0;
};

#endif

