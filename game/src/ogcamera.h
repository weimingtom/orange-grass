/*
 *  camera.h
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
	
	// setup camera.
	virtual void Setup (const Vec3& _vPosition, const Vec3& _vDirection, const Vec3& _vUp);
	
	// get camera position.
	virtual const Vec3& GetPosition () const { return m_Position; }
	
	// get camera direction.
	virtual const Vec3& GetDirection () const { return m_Direction; }
	
	// rotate view.
	virtual void RotateView (float _fAngle, const Vec3& _vAxis);

	// move camera in defined direction
	virtual void Strafe(float _fSpeed, const Vec3& _vDir);

	// move camera forward/backward
	virtual void Move(float _fSpeed);
	
	// update camera.
	virtual const MATRIX& Update ();

private:
	
	MATRIX		m_View;
	Vec3		m_Position;
	Vec3		m_Direction;
	Vec3		m_Up;
};

#endif
