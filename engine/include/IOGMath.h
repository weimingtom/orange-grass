#ifndef IOGMATH_H_
#define IOGMATH_H_

#include <math.h>
#include "Mathematics.h"

// floating point macros
#define FP_BITS(fp)			(*(unsigned long*)&(fp))
#define FP_ABS_BITS(fp)		(FP_BITS(fp)&0x7FFFFFFF)
#define FP_SIGN_BIT(fp)		(FP_BITS(fp)&0x80000000)
#define FP_ONE_BITS			0x3F800000
#define	FP_SIGN_BIT_SHIFT	31


// Get distance between two points
static float Dist ( int _x1, int _y1, int _x2, int _y2 )
{
	float xdiff = (float)(_x1 - _x2);
	float ydiff = (float)(_y1 - _y2);
	return sqrtf (xdiff*xdiff + ydiff*ydiff);
}


// Get distance between two points
static float Dist3D ( const Vec3& _p1, const Vec3& _p2 )
{
	float xdiff = (float)(_p1.x - _p2.x);
	float ydiff = (float)(_p1.y - _p2.y);
	float zdiff = (float)(_p1.z - _p2.z);
	return sqrtf (xdiff*xdiff + ydiff*ydiff + zdiff*zdiff);
}


// Calculate pick ray
static Vec3 GetPickRay1 (const MATRIX& _mView, const MATRIX& _mProj, int _XRes, int _YRes, int _MouseX, int _MouseY, int _MouseZ)
{
	// Get the inverse of the view matrix
	MATRIX mInv, mMul;
	MatrixMultiply (mMul, _mProj, _mView);
	MatrixInverseEx (mInv, mMul);

	// Compute the vector of the pick ray in screen space
    Vec4 v;
	v.x = ( ( ( 2.0f * _MouseX ) / _XRes ) - 1.0f );
	v.y = ( ( ( 2.0f * _MouseY ) / _YRes ) - 1.0f );
	v.z = 2.0f * _MouseZ - 1.0f;
	v.w = 1.0f;

	// Transform the screen space pick ray into 3D space
	VECTOR4 out;
	MatrixVec4Multiply (out, v, mInv);
	out.w = 1 / out.w;
	out.x *= out.w;
	out.y *= out.w;
	out.z *= out.w;
	return Vec3(out.x, out.y, out.z);
}


// Calculate pick ray
static Vec3 GetPickRay (int _MouseX, int _MouseY)
{
	GLdouble modelMatrix[16];
	GLdouble projMatrix[16];
	int viewport[4];
	glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
	glGetIntegerv(GL_VIEWPORT, viewport);
	double x0, y0, z0;
	gluUnProject(_MouseX, viewport[3] - _MouseY, 0, modelMatrix, projMatrix, viewport, &x0, &y0, &z0);
	return Vec3((float)x0, (float)y0, (float)z0);
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


static void WorldMatrixFromTransforms (MATRIX& _mWorld, const Vec3& _vPos, const Vec3& _vRot)
{
    MatrixTranslation(_mWorld, _vPos.x, _vPos.y, _vPos.z);
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


#endif