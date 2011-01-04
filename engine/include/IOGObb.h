/*
 *  IOGObb.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 14.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGOBB_H_
#define IOGOBB_H_

#include "IOGAabb.h"


class IOGObb
{
public:

	// Constructor
	IOGObb ()
	{
	}

	// Construct using AABB
	void Create (const IOGAabb& _Aabb)
	{
        m_Aabb = _Aabb;
	}

	// Update OBB transformation
	void UpdateTransform (const MATRIX& _mTransform)
	{
        m_vMin = m_Aabb.GetMin();
        m_vMax = m_Aabb.GetMax();
        
        MatrixGetOrg(m_vCenter, _mTransform);
        
        MatrixGetBasis(m_vAxis[0], m_vAxis[1], m_vAxis[2], _mTransform);

        for (int i = 0; i < 3; ++i)
        {
            float ScaleFactor = m_vAxis[i].length();
            m_vMin[i] *= ScaleFactor;
            m_vMax[i] *= ScaleFactor;
            m_vAxis[i] /= ScaleFactor;
        }
        m_TransformedAabb.SetMinMax(m_vMin, m_vMax);
	}

    // Check OBB-ray intersection
    bool CheckIntersection (
        const Vec3&	_vRayStart,
        const Vec3&	_vRayDir
        ) const
    {
        Vec3 vOrg = VectorConvertToLocal ( _vRayStart - m_vCenter );
        Vec3 vDirection = VectorConvertToLocal ( _vRayDir );
        return m_TransformedAabb.CheckIntersection (vOrg, vOrg + vDirection * 200000.f);
    }

    // Check OBB-line intersection
    bool CheckLineIntersection (
        const Vec3&	_vRayStart,
        const Vec3&	_vRayEnd
        ) const
    {
        Vec3 vOrg = VectorConvertToLocal ( _vRayStart - m_vCenter );
        Vec3 vDir = (_vRayEnd - _vRayStart);
        float fLen = vDir.length();
        Vec3 vDirection = VectorConvertToLocal ( vDir.normalized() );
        return m_TransformedAabb.CheckIntersection (vOrg, vOrg + vDirection * fLen);
    }

    // Convert point to world space
    Vec3 VectorConvertToWorld (const Vec3& _Vector) const
    {
        Vec3 RetVector;
        for ( int i = 0; i < 3; ++i )
            RetVector [i] = _Vector.dot ( m_vAxis [i] )  + m_vCenter [i];

        return RetVector;
    }

    // Convert point to local space
    Vec3 VectorConvertToLocal (const Vec3& _Vector) const
    {
        Vec3 RetVector;
        for ( int i = 0; i < 3; ++i )
            RetVector [i] = 
                m_vAxis [0][i] * _Vector.x +
                m_vAxis [1][i] * _Vector.y +
                m_vAxis [2][i] * _Vector.z;

        return RetVector;		
    }

public:

	Vec3	m_vMin;
	Vec3	m_vMax;
	Vec3	m_vCenter;
	Vec3	m_vAxis[3];
    IOGAabb m_Aabb;
    IOGAabb m_TransformedAabb;
};

#endif