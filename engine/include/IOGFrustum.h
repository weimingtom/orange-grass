/*
 *  IOGFrustum.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 14.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGFRUSTUM_H_
#define IOGFRUSTUM_H_

#include "Mathematics.h"
#include "IOGPlane.h"
#include "IOGObb.h"


class IOGFrustum
{
public:
	// get near plane.
	IOGPlane& GetNearPlane() { return Plane[4]; }

	// get far plane.
	IOGPlane& GetFarPlane()	{ return Plane[5]; }	
	
	// get top plane.
	IOGPlane& GetTopPlane() { return Plane[2]; }	
	
	// get bottom plane.
	IOGPlane& GetBottomPlane() { return Plane[3]; }	
	
	// get left plane.
	IOGPlane& GetLeftPlane() { return Plane[0]; }	
	
	// get right plane.
	IOGPlane& GetRightPlane() { return Plane[1]; }	
		
	// update viewing frustum.
	void Update(const MATRIX& comboMatrix, bool normalize)
	{
		VECTOR4 TempPlane;

		// Left clipping plane
		TempPlane.x = comboMatrix.f[_41] + comboMatrix.f[_11]; 
		TempPlane.y = comboMatrix.f[_42] + comboMatrix.f[_12]; 
		TempPlane.z = comboMatrix.f[_43] + comboMatrix.f[_13]; 
		TempPlane.w = comboMatrix.f[_44] + comboMatrix.f[_14]; 
		Plane[0].Set(TempPlane);

		// Right clipping plane 
		TempPlane.x = comboMatrix.f[_41] - comboMatrix.f[_11]; 
		TempPlane.y = comboMatrix.f[_42] - comboMatrix.f[_12]; 
		TempPlane.z = comboMatrix.f[_43] - comboMatrix.f[_13]; 
		TempPlane.w = comboMatrix.f[_44] - comboMatrix.f[_14]; 
		Plane[1].Set(TempPlane);

		// Top clipping plane 
		TempPlane.x = comboMatrix.f[_41] - comboMatrix.f[_21]; 
		TempPlane.y = comboMatrix.f[_42] - comboMatrix.f[_22]; 
		TempPlane.z = comboMatrix.f[_43] - comboMatrix.f[_23]; 
		TempPlane.w = comboMatrix.f[_44] - comboMatrix.f[_24]; 
		Plane[2].Set(TempPlane);

		// Bottom clipping plane 
		TempPlane.x = comboMatrix.f[_41] + comboMatrix.f[_21]; 
		TempPlane.y = comboMatrix.f[_42] + comboMatrix.f[_22]; 
		TempPlane.z = comboMatrix.f[_43] + comboMatrix.f[_23]; 
		TempPlane.w = comboMatrix.f[_44] + comboMatrix.f[_24]; 
		Plane[3].Set(TempPlane);

		// Near clipping plane 
		TempPlane.x = comboMatrix.f[_41] + comboMatrix.f[_31]; 
		TempPlane.y = comboMatrix.f[_42] + comboMatrix.f[_32]; 
		TempPlane.z = comboMatrix.f[_43] + comboMatrix.f[_33]; 
		TempPlane.w = comboMatrix.f[_44] + comboMatrix.f[_34]; 
		Plane[4].Set(TempPlane);

		// Far clipping plane 
		TempPlane.x = comboMatrix.f[_41] - comboMatrix.f[_31]; 
		TempPlane.y = comboMatrix.f[_42] - comboMatrix.f[_32]; 
		TempPlane.z = comboMatrix.f[_43] - comboMatrix.f[_33]; 
		TempPlane.w = comboMatrix.f[_44] - comboMatrix.f[_34]; 
		Plane[5].Set(TempPlane);

		// Normalize the plane equations, if requested 
		if (normalize == true) 
		{ 
			Plane[0].NormalizePlane(); 
			Plane[1].NormalizePlane(); 
			Plane[2].NormalizePlane(); 
			Plane[3].NormalizePlane(); 
			Plane[4].NormalizePlane(); 
			Plane[5].NormalizePlane(); 
		} 
	}

	// Check if point inside frustum.
	bool CheckPoint ( const VECTOR3& _vPoint )
	{
		// Make sure point is in frustum
		for ( int i = 0; i < 6; ++i ) 
		{
			if (Plane[i].DistanceToPlane(_vPoint) < 0.0f)
				return false;
		}

		return true;
	}

	// Check if AABB inside frustum.
	bool CheckAabb ( const IOGAabb& _Aabb ) const
	{
		float xSize = _Aabb.GetSizeX ();
		float ySize = _Aabb.GetSizeY ();
		float zSize = _Aabb.GetSizeZ ();
	
		// Make sure at least one point is completely in frustum
		for ( int i = 0; i < 6; ++i ) 
		{
			if ( Plane[i].DistanceToPlane(Vec3( _Aabb.GetMin ().x, _Aabb.GetMin ().y, _Aabb.GetMin ().z ) ) >= 0.0f )
				continue;
			if ( Plane[i].DistanceToPlane(Vec3( _Aabb.GetMin ().x, _Aabb.GetMin ().y + ySize, _Aabb.GetMin().z ) ) >= 0.0f )
				continue;
			if ( Plane[i].DistanceToPlane(Vec3( _Aabb.GetMin ().x, _Aabb.GetMin ().y, _Aabb.GetMin().z + zSize) ) >= 0.0f )
				continue;
			if ( Plane[i].DistanceToPlane(Vec3( _Aabb.GetMin ().x, _Aabb.GetMin ().y + ySize, _Aabb.GetMin().z + zSize ) ) >= 0.0f )
				continue;
			if ( Plane[i].DistanceToPlane(Vec3( _Aabb.GetMin ().x + xSize, _Aabb.GetMin ().y, _Aabb.GetMin().z ) ) >= 0.0f )
				continue;
			if ( Plane[i].DistanceToPlane(Vec3( _Aabb.GetMin ().x + xSize, _Aabb.GetMin ().y+ySize, _Aabb.GetMin().z ) ) >= 0.0f )
				continue;
			if ( Plane[i].DistanceToPlane(Vec3( _Aabb.GetMin ().x + xSize, _Aabb.GetMin ().y, _Aabb.GetMin().z + zSize ) ) >= 0.0f )
				continue;
			if ( Plane[i].DistanceToPlane(Vec3( _Aabb.GetMax ().x, _Aabb.GetMax ().y, _Aabb.GetMax ().z ) ) >= 0.0f )
				continue;

			return false;
		}

		return true;
	}

	// Check if OBB inside frustum.
	bool CheckObb ( const IOGObb& _Obb ) const
	{
		Vec3 vMin = _Obb.m_vMin;
		Vec3 vMax = _Obb.m_vMax;

		Vec3 vA = _Obb.VectorConvertToWorld ( Vec3 ( vMin.x, vMin.y, vMin.z) );
		Vec3 vB = _Obb.VectorConvertToWorld ( Vec3 ( vMin.x, vMin.y, vMax.z) );
		Vec3 vC = _Obb.VectorConvertToWorld ( Vec3 ( vMax.x, vMin.y, vMax.z) );
		Vec3 vD = _Obb.VectorConvertToWorld ( Vec3 ( vMax.x, vMin.y, vMin.z) );
		Vec3 vE = _Obb.VectorConvertToWorld ( Vec3 ( vMin.x, vMax.y, vMin.z) );
		Vec3 vF = _Obb.VectorConvertToWorld ( Vec3 ( vMin.x, vMax.y, vMax.z) );
		Vec3 vG = _Obb.VectorConvertToWorld ( Vec3 ( vMax.x, vMax.y, vMax.z) );
		Vec3 vH = _Obb.VectorConvertToWorld ( Vec3 ( vMax.x, vMax.y, vMin.z) );
	
		// Make sure at least one point is completely in frustum
		for ( int i = 0; i < 6; ++i ) 
		{
			if ( Plane[i].DistanceToPlane(vA) >= 0.0f )
				continue;
			if ( Plane[i].DistanceToPlane(vB) >= 0.0f )
				continue;
			if ( Plane[i].DistanceToPlane(vC) >= 0.0f )
				continue;
			if ( Plane[i].DistanceToPlane(vD) >= 0.0f )
				continue;
			if ( Plane[i].DistanceToPlane(vE) >= 0.0f )
				continue;
			if ( Plane[i].DistanceToPlane(vF) >= 0.0f )
				continue;
			if ( Plane[i].DistanceToPlane(vG) >= 0.0f )
				continue;
			if ( Plane[i].DistanceToPlane(vH) >= 0.0f )
				continue;

			return false;
		}

		return true;
	}
	
private:

	IOGPlane Plane[6];
};

#endif
