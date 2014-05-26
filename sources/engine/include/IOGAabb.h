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
	IOGAabb (const OGVec3& _vMin, const OGVec3& _vMax)
	{
		SetMinMax (_vMin, _vMax);
	}

	// Set minimum and maximum of AABB
	void SetMinMax (const OGVec3& _vMin, const OGVec3& _vMax)
	{
		m_vMin = _vMin;
		m_vMax = _vMax;
		m_vCenter = (m_vMax + m_vMin) / 2.0f;
		m_fBoundingRadius = (m_vMax - m_vMin).length () / 2;
	}

	// Embrace AABB
	void EmbraceAABB (const IOGAabb& _aabb)
	{
		const OGVec3& vNewMin = _aabb.GetMin();
		const OGVec3& vNewMax = _aabb.GetMax();

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
	const OGVec3& GetMin () const { return m_vMin; }

	// Get AABB maximum
	const OGVec3& GetMax () const { return m_vMax; }

	// Get AABB maximum
	const OGVec3& GetCenter () const { return m_vCenter; }

	// Get size x
	float GetSizeX () const { return m_vMax.x - m_vMin.x; }

	// Get size y
	float GetSizeY () const { return m_vMax.y - m_vMin.y; }

	// Get size z
	float GetSizeZ () const { return m_vMax.z - m_vMin.z; }

	// Get bounding radius
	float GetRadius () const { return m_fBoundingRadius; }

    // Check AABB-line intersection
    bool CheckIntersection ( 
        const OGVec3& _LineStart, 
        const OGVec3& _LineEnd ) const
    {
        OGVec3 vStart = _LineStart;
        OGVec3 vEnd = _LineEnd;
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

	OGVec3	m_vMin;
	OGVec3	m_vMax;
	OGVec3	m_vCenter;
	float	m_fBoundingRadius;
};

#endif