/*
 *  IOGMath.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGMATH_H_
#define IOGMATH_H_

#include <math.h>
#include "Mathematics.h"
#include "IOGCoreHelpers.h"

// floating point macros
#define FP_BITS(fp)			(*(unsigned long*)&(fp))
#define FP_ABS_BITS(fp)		(FP_BITS(fp)&0x7FFFFFFF)
#define FP_SIGN_BIT(fp)		(FP_BITS(fp)&0x80000000)
#define FP_ONE_BITS			0x3F800000
#define	FP_SIGN_BIT_SHIFT	31

#define TO_RADIAN(degree)   ((degree) * (PI / 180.0f))
#define TO_DEGREE(radian)   ((radian) * (180.0f / PI))


// Get distance between two points
static float Dist ( int _x1, int _y1, int _x2, int _y2 )
{
	float xdiff = (float)(_x1 - _x2);
	float ydiff = (float)(_y1 - _y2);
	return sqrtf (xdiff*xdiff + ydiff*ydiff);
}


// Get distance between two points (2D)
static float Dist2D ( const Vec3& _p1, const Vec3& _p2 )
{
	float xdiff = _p1.x - _p2.x;
	float zdiff = _p1.z - _p2.z;
	return sqrtf (xdiff*xdiff + zdiff*zdiff);
}


// Get square distance between two points (2D)
static float Dist2DSq ( const Vec3& _p1, const Vec3& _p2 )
{
	float xdiff = _p1.x - _p2.x;
	float zdiff = _p1.z - _p2.z;
	return (xdiff*xdiff + zdiff*zdiff);
}


// Get distance between two points
static float Dist3D ( const Vec3& _p1, const Vec3& _p2 )
{
	float xdiff = _p1.x - _p2.x;
	float ydiff = _p1.y - _p2.y;
	float zdiff = _p1.z - _p2.z;
	return sqrtf (xdiff*xdiff + ydiff*ydiff + zdiff*zdiff);
}


// Get square distance between two points
static float Dist3DSq ( const Vec3& _p1, const Vec3& _p2 )
{
	float xdiff = _p1.x - _p2.x;
	float ydiff = _p1.y - _p2.y;
	float zdiff = _p1.z - _p2.z;
	return (xdiff*xdiff + ydiff*ydiff + zdiff*zdiff);
}


// Check ray intersection with the triangle
static bool CheckTriangleIntersection (	const Vec3& _orig, const Vec3& _dir, 
										const Vec3& _p0, const Vec3& _p1, const Vec3& _p2,
										float* _fT, float* _fU, float* _fV)
{
	static const float CTI_Epsilon = 0.0001f;
	Vec3 edge1, edge2, tvec, pvec, qvec;
	float det, inv_det;

	edge1 = _p1 - _p0;
	edge2 = _p2 - _p0;

	MatrixVec3CrossProduct(pvec, _dir, edge2);
	det = MatrixVec3DotProduct(edge1, pvec);

	if (det > -CTI_Epsilon && det < CTI_Epsilon)
		return false;
	inv_det = 1.0f / det;

	tvec = _orig - _p0;

	*_fU = MatrixVec3DotProduct(tvec, pvec) * inv_det;
	if (*_fU < 0.0f || *_fU > 1.0f)
		return false;

	MatrixVec3CrossProduct(qvec, tvec, edge1);

	*_fV = MatrixVec3DotProduct(_dir, qvec) * inv_det;
	if (*_fV < 0.0f || *_fU + *_fV > 1.0f)
		return false;

	*_fT = MatrixVec3DotProduct(edge2, qvec) * inv_det;
	return true;
}


// Converting barycentric coords. to world coords.
static Vec3 Barycentric2World (float _fU, float _fV,
							   const Vec3& _p0, const Vec3& _p1, const Vec3& _p2)
{
	float w = 1.0f - ( _fU + _fV);
	float x = w * _p0.x + _fU * _p1.x + _fV * _p2.x;
	float y = w * _p0.y + _fU * _p1.y + _fV * _p2.y;
	float z = w * _p0.z + _fU * _p1.z + _fV * _p2.z;
	return Vec3(x, y, z);
}


// Converting barycentric coords. to world coords.
static Vec3 Vec3Lerp (float _fFactor, const Vec3& _p0, const Vec3& _p1)
{
	Vec3 out;
	out.x = _p0.x + _fFactor * (_p1.x - _p0.x);
	out.y = _p0.y + _fFactor * (_p1.y - _p0.y);
	out.z = _p0.z + _fFactor * (_p1.z - _p0.z);
	return out;
}


static void WorldMatrixFromTransforms (MATRIX& _mWorld, const Vec3& _vPos, const Vec3& _vRot, const Vec3& _vScale)
{
    MATRIX mX, mY, mZ, mS, mT;
    MatrixTranslation(mT, _vPos.x, _vPos.y, _vPos.z);
    MatrixRotationX(mX, _vRot.x);
    MatrixRotationY(mY, _vRot.y);
    MatrixRotationZ(mZ, _vRot.z);
    MatrixScaling(mS, _vScale.x, _vScale.y, _vScale.z);
    MatrixMultiply(_mWorld, mS, mY);
    MatrixMultiply(_mWorld, _mWorld, mZ);
    MatrixMultiply(_mWorld, _mWorld, mX);
    MatrixMultiply(_mWorld, _mWorld, mT);
}


// Clips the segment by the given axis
// Returns  negative value if no intersection
//			0 if front-side intersection
//			1 if rear-side intersection
inline int ClipAxialLine ( 
                          Vec3& _Vec0, 
                          Vec3& _Vec1, 
                          int	_Sign,
                          int	_Axis,
                          float	_BoxCoordValue
                          )
{
    // calculate the distance to the point
    float d0 = _Vec0[ _Axis ] * _Sign - _BoxCoordValue;
    float d1 = _Vec1[ _Axis ] * _Sign - _BoxCoordValue;

    // get the sign
    unsigned long sign0 = FP_SIGN_BIT ( d0 );
    unsigned long sign1 = FP_SIGN_BIT ( d1 );

    // on the same side
    if ( sign0 == sign1 )
    {
        return - ( (int) ( sign0 >> FP_SIGN_BIT_SHIFT ) + 1 );
    }

    // on the different sides
    sign0 >>= FP_SIGN_BIT_SHIFT;
    if (sign0 == 0)
        _Vec0 = Vec3Lerp ( d0 / ( d0 - d1 ), _Vec0, _Vec1 );
    else
        _Vec1 = Vec3Lerp ( d0 / ( d0 - d1 ), _Vec0, _Vec1 );

    return sign0;	
}


// Find intersection with plane
static Vec3 FindIntersectionWithPlane ( 
    float _fHeight,
    const Vec3& _vRayOrig,
    const Vec3& _vRayDir
    )
{
    Vec3 vIntersectionPoint;
    float fFactorLine = (float)( ( _fHeight - _vRayOrig.y ) / _vRayDir.y );
    vIntersectionPoint.x = _vRayDir.x * fFactorLine + _vRayOrig.x;
    vIntersectionPoint.y = _vRayDir.y * fFactorLine + _vRayOrig.y;
    vIntersectionPoint.z = _vRayDir.z * fFactorLine + _vRayOrig.z;
    return vIntersectionPoint;
}


// CW or CCW
static bool IsCCW (const Vec2& _vV1, const Vec2& _vV2)
{
    return (_vV1.x * _vV2.y - _vV1.y * _vV2.x > 0.0f);
}


// Get angle between two vectors
static float GetAngle (const Vec3& _vV1, const Vec3& _vV2)
{
    float fDot = _vV2.dot(_vV1) / (_vV1.length() * _vV2.length());
    OG_CLAMP(fDot, -1.0f, 1.0f);
    float fAngle = acosf( fDot );
    if ( fAngle < 0 )
        return -PI;
    bool bSign = IsCCW (Vec2(_vV2.x, _vV2.z), Vec2(_vV1.x, _vV1.z));
    return bSign ? fAngle : -fAngle;
}


// Rotate 2D point
static void Rotate2DPoint ( float& _X, float& _Y, float _Angle, float _CenterX, float _CenterY )
{
    float sin = sinf ( _Angle );
    float cos = cosf ( _Angle );

    float RotX = _X - _CenterX;
    float RotY = _Y - _CenterY;

    float RetX = RotX * cos - RotY * sin;
    float RetY = RotX * sin + RotY * cos;

    _X = RetX + _CenterX;
    _Y = RetY + _CenterY;
}


// get random number in range
static int GetRandomRange (int _Min, int _Max)
{
	return _Min + abs ( rand() % _Max );
}


#endif