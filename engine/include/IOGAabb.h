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
		m_vMin = _vMin;
		m_vMax = _vMax;
		m_vCenter = (m_vMax + m_vMin) / 2.0f;
		m_fBoundingRadius = (m_vMax - m_vMin).length () / 2;
	}

	// Embrace AABB
	void EmbraceAABB (const IOGAabb& _aabb)
	{
		const Vec3& vNewMin = _aabb.GetMin();
		const Vec3& vNewMax = _aabb.GetMax();

		if (vNewMin.x < m_vMin.x) m_vMin.x = vNewMin.x;
		if (vNewMin.y < m_vMin.y) m_vMin.y = vNewMin.y;
		if (vNewMin.z < m_vMin.z) m_vMin.z = vNewMin.z;
		if (vNewMax.x > m_vMax.x) m_vMax.x = vNewMax.x;
		if (vNewMax.y > m_vMax.y) m_vMax.y = vNewMax.y;
		if (vNewMax.z > m_vMax.z) m_vMax.z = vNewMax.z;

		m_vCenter = (m_vMax + m_vMin) / 2.0f;
		m_fBoundingRadius = (m_vMax - m_vMin).length () / 2;
	}

	// Get AABB minimum
	const Vec3& GetMin () const { return m_vMin; }

	// Get AABB maximum
	const Vec3& GetMax () const { return m_vMax; }

	// Get AABB maximum
	const Vec3& GetCenter () const { return m_vCenter; }

	// Get bounding radius
	float GetRadius () const { return m_fBoundingRadius; }

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
	float	m_fBoundingRadius;
};

#endif