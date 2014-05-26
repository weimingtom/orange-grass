/*
 * OrangeGrass
 * Copyright (C) 2009 Vyacheslav Bogdanov.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/lgpl-3.0-standalone.html>.
 */
#ifndef IOGPLANE_H_
#define IOGPLANE_H_

#include "IOGMath.h"


class IOGPlane
{
public:

	// Default constructor.
	IOGPlane()
	{
	}

	// Initializing plane.
	IOGPlane(float x, float y, float z, float w)
	{
		Plane.x = x;
		Plane.y = y;
		Plane.z = z;
		Plane.w = w;
	}

	// Initializing plane.
	void Set(const float x, const float y, const float z, const float w)
	{
		Plane.x = x;
		Plane.y = y;
		Plane.z = z;
		Plane.w = w;
	}

	// Initializing plane.
	void Set(const OGVec4& v)
	{
		Plane.x = v.x;
		Plane.y = v.y;
		Plane.z = v.z;
		Plane.w = v.w;
	}

	// gets the point on the plane nearest to the origin
	OGVec3 GetPos() const
	{
		OGVec3 v;
		v.x = Plane.x * Plane.w;
		v.y = Plane.y * Plane.w;
		v.z = Plane.z * Plane.w;
		return v;
	}

	// gets plane normal
	OGVec3 GetNormal() const
	{			
		OGVec3 v;
		v.x = Plane.x;
		v.y = Plane.y;
		v.z = Plane.z;
		return v;
	}

	// get plane vector.
	OGVec4& GetPlane()
	{			
		return Plane;
	}

	// calculate the distance between a point and a plane
	inline float DistanceToPlane(const OGVec3& point) const
	{
		return Vec3DotProduct((const OGVec3&)Plane, point) + Plane.w;
	}

	// normalize plane
	inline void NormalizePlane()
	{
		Vec4Normalize(Plane, Plane);
	}

private:

	OGVec4 Plane;
};

#endif
