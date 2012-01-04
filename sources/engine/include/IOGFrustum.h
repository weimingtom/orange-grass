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

#include "IOGMath.h"
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
	void Update(const OGMatrix& comboMatrix)
	{
		Plane[0].Set(comboMatrix.f[ 3] - comboMatrix.f[ 0], comboMatrix.f[ 7] - comboMatrix.f[ 4], comboMatrix.f[11] - comboMatrix.f[ 8], comboMatrix.f[15] - comboMatrix.f[12]);
		Plane[1].Set(comboMatrix.f[ 3] + comboMatrix.f[ 0], comboMatrix.f[ 7] + comboMatrix.f[ 4], comboMatrix.f[11] + comboMatrix.f[ 8], comboMatrix.f[15] + comboMatrix.f[12]);
		Plane[2].Set(comboMatrix.f[ 3] + comboMatrix.f[ 1], comboMatrix.f[ 7] + comboMatrix.f[ 5], comboMatrix.f[11] + comboMatrix.f[ 9], comboMatrix.f[15] + comboMatrix.f[13]);
		Plane[3].Set(comboMatrix.f[ 3] - comboMatrix.f[ 1], comboMatrix.f[ 7] - comboMatrix.f[ 5], comboMatrix.f[11] - comboMatrix.f[ 9], comboMatrix.f[15] - comboMatrix.f[13]);
		Plane[4].Set(comboMatrix.f[ 3] - comboMatrix.f[ 2], comboMatrix.f[ 7] - comboMatrix.f[ 6], comboMatrix.f[11] - comboMatrix.f[10], comboMatrix.f[15] - comboMatrix.f[14]);
		Plane[5].Set(comboMatrix.f[ 3] + comboMatrix.f[ 2], comboMatrix.f[ 7] + comboMatrix.f[ 6], comboMatrix.f[11] + comboMatrix.f[10], comboMatrix.f[15] + comboMatrix.f[14]);

		Plane[0].NormalizePlane(); 
		Plane[1].NormalizePlane(); 
		Plane[2].NormalizePlane(); 
		Plane[3].NormalizePlane(); 
		Plane[4].NormalizePlane(); 
		Plane[5].NormalizePlane(); 
	}

	// Check if point inside frustum.
	bool CheckPoint ( const OGVec3& _vPoint ) const
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
			if ( Plane[i].DistanceToPlane(OGVec3( _Aabb.GetMin ().x, _Aabb.GetMin ().y, _Aabb.GetMin ().z ) ) >= 0.0f )
				continue;
			if ( Plane[i].DistanceToPlane(OGVec3( _Aabb.GetMin ().x, _Aabb.GetMin ().y + ySize, _Aabb.GetMin().z ) ) >= 0.0f )
				continue;
			if ( Plane[i].DistanceToPlane(OGVec3( _Aabb.GetMin ().x, _Aabb.GetMin ().y, _Aabb.GetMin().z + zSize) ) >= 0.0f )
				continue;
			if ( Plane[i].DistanceToPlane(OGVec3( _Aabb.GetMin ().x, _Aabb.GetMin ().y + ySize, _Aabb.GetMin().z + zSize ) ) >= 0.0f )
				continue;
			if ( Plane[i].DistanceToPlane(OGVec3( _Aabb.GetMin ().x + xSize, _Aabb.GetMin ().y, _Aabb.GetMin().z ) ) >= 0.0f )
				continue;
			if ( Plane[i].DistanceToPlane(OGVec3( _Aabb.GetMin ().x + xSize, _Aabb.GetMin ().y+ySize, _Aabb.GetMin().z ) ) >= 0.0f )
				continue;
			if ( Plane[i].DistanceToPlane(OGVec3( _Aabb.GetMin ().x + xSize, _Aabb.GetMin ().y, _Aabb.GetMin().z + zSize ) ) >= 0.0f )
				continue;
			if ( Plane[i].DistanceToPlane(OGVec3( _Aabb.GetMax ().x, _Aabb.GetMax ().y, _Aabb.GetMax ().z ) ) >= 0.0f )
				continue;

			return false;
		}

		return true;
	}

	// Check if OBB inside frustum.
	bool CheckObb ( const IOGObb& _Obb ) const
	{
		OGVec3 vMin = _Obb.m_vMin;
		OGVec3 vMax = _Obb.m_vMax;

		OGVec3 vA = _Obb.VectorConvertToWorld ( OGVec3 ( vMin.x, vMin.y, vMin.z) );
		OGVec3 vB = _Obb.VectorConvertToWorld ( OGVec3 ( vMin.x, vMin.y, vMax.z) );
		OGVec3 vC = _Obb.VectorConvertToWorld ( OGVec3 ( vMax.x, vMin.y, vMax.z) );
		OGVec3 vD = _Obb.VectorConvertToWorld ( OGVec3 ( vMax.x, vMin.y, vMin.z) );
		OGVec3 vE = _Obb.VectorConvertToWorld ( OGVec3 ( vMin.x, vMax.y, vMin.z) );
		OGVec3 vF = _Obb.VectorConvertToWorld ( OGVec3 ( vMin.x, vMax.y, vMax.z) );
		OGVec3 vG = _Obb.VectorConvertToWorld ( OGVec3 ( vMax.x, vMax.y, vMax.z) );
		OGVec3 vH = _Obb.VectorConvertToWorld ( OGVec3 ( vMax.x, vMax.y, vMin.z) );
	
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
