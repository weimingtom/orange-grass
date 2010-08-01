/*
 *  IOGAabb.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 14.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGAABB_H_
#define IOGAABB_H_

#include "IOGMath.h"


class IOGAabb
{
public:

	// Constructor
	IOGAabb ()
	{
	}

	// Construct AABB using minimum and maximum
	IOGAabb (const Vec3& _vMin, const Vec3& _vMax)
	{
		SetMinMax (_vMin, _vMax);
	}

	// Set minimum and maximum of AABB
	void SetMinMax (const Vec3& _vMin, const Vec3& _vMax)
	{
		m_vMin = m_vOriginalMin = _vMin;
		m_vMax = m_vOriginalMax = _vMax;
		m_vCenter = m_vOriginalCenter = (m_vMax + m_vMin) / 2.0f;
		m_fBoundingRadius = (m_vMax - m_vMin).length () / 2;
	}

	// Get AABB minimum
	const Vec3& GetMin () const { return m_vMin; }

	// Get AABB maximum
	const Vec3& GetMax () const { return m_vMax; }

	// Get AABB maximum
	const Vec3& GetCenter () const { return m_vCenter; }

	// Get non-transformed AABB minimum
	const Vec3& GetOriginalMin () const { return m_vOriginalMin; }

	// Get non-transformed AABB maximum
	const Vec3& GetOriginalMax () const { return m_vOriginalMax; }

	// Get non-transformed AABB center
	const Vec3& GetOriginalCenter () const { return m_vOriginalCenter; }

	// Get transformation matrix
	const MATRIX& GetTransform () const { return m_mTransform; }

	// Get bounding radius
	float GetRadius () const { return m_fBoundingRadius; }

	// Update AABB transformation
	void UpdateTransform (const MATRIX& _mTransform)
	{
		m_mTransform = _mTransform;
		m_vOriginalMin = m_vMin;
		m_vOriginalMax = m_vMax;
		m_vOriginalCenter = m_vCenter;

		VECTOR4 v_in, v_out;
		v_in.x = m_vMin.x; v_in.y = m_vMin.y; v_in.z = m_vMin.z; v_in.w = 1.0f;
		MatrixVec4Multiply(v_out, v_in, _mTransform);
		m_vMin.x = v_out.x; m_vMin.y = v_out.y; m_vMin.z = v_out.z;

		v_in.x = m_vMax.x; v_in.y = m_vMax.y; v_in.z = m_vMax.z; v_in.w = 1.0f;
		MatrixVec4Multiply(v_out, v_in, _mTransform);
		m_vMax.x = v_out.x; m_vMax.y = v_out.y; m_vMax.z = v_out.z;

		m_vCenter = (m_vMax + m_vMin) / 2.0f;
		m_fBoundingRadius = (m_vMax - m_vMin).length () / 2;
	}

    // Check AABB-line intersection
    bool CheckIntersection ( 
        const Vec3& _LineStart, 
        const Vec3& _LineEnd ) const
    {
        Vec3 vStart = _LineStart;
        Vec3 vEnd = _LineEnd;
        for ( int Axis = 0; Axis < 3; ++Axis )
        {
            int Res = ClipAxialLine ( vStart, vEnd, -1, Axis, -m_vMin [ Axis ] );
            if ( -1 == Res )
                return false;

            Res = ClipAxialLine ( vStart, vEnd, 1, Axis, m_vMax [ Axis ] );
            if ( -1 == Res )
                return false;
        }

        return true;
    }

private:

	Vec3	m_vMin;
	Vec3	m_vMax;
	Vec3	m_vCenter;
	Vec3	m_vOriginalMin;
	Vec3	m_vOriginalMax;
	Vec3	m_vOriginalCenter;
	MATRIX	m_mTransform;
	float	m_fBoundingRadius;
};

#endif