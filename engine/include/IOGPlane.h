/*
*  IOGPlane.h
*  OrangeGrass
*
*  Created by Viacheslav Bogdanov on 14.11.09.
*  Copyright 2009 __MyCompanyName__. All rights reserved.
*
*/
#ifndef IOGPLANE_H_
#define IOGPLANE_H_

#include "Mathematics.h"


class IOGPlane
{
public:

	// Default constructor.
	IOGPlane()
	{
	}

	// Initializing plane.
	IOGPlane(VERTTYPE x, VERTTYPE y, VERTTYPE z, VERTTYPE w)
	{
		Plane.x = x;
		Plane.y = y;
		Plane.z = z;
		Plane.w = w;
	}

	// Initializing plane.
	void Set(const VERTTYPE x, const VERTTYPE y, const VERTTYPE z, const VERTTYPE w)
	{
		Plane.x = x;
		Plane.y = y;
		Plane.z = z;
		Plane.w = w;
	}

	// Initializing plane.
	void Set(const VECTOR4& v)
	{
		Plane.x = v.x;
		Plane.y = v.y;
		Plane.z = v.z;
		Plane.w = v.w;
	}

	// gets the point on the plane nearest to the origin
	VECTOR3 GetPos() const
	{
		VECTOR3 v;
		v.x = Plane.x * Plane.w;
		v.y = Plane.y * Plane.w;
		v.z = Plane.z * Plane.w;
		return v;
	}

	// gets plane normal
	VECTOR3 GetNormal() const
	{			
		VECTOR3 v;
		v.x = Plane.x;
		v.y = Plane.y;
		v.z = Plane.z;
		return v;
	}

	// get plane vector.
	VECTOR4& GetPlane()
	{			
		return Plane;
	}

	// calculate the distance between a point and a plane
	inline VERTTYPE DistanceToPlane(const VECTOR3& point)
	{
		return MatrixVec3DotProduct((VECTOR3&)Plane, point) + Plane.w;
	}

	// normalize plane
	inline void NormalizePlane()
	{
		MatrixVec4Normalize(Plane, Plane);
	}

private:

	VECTOR4 Plane;
};

#endif
