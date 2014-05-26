/*
 * OrangeGrass
 * Copyright (C) 2009-2012 Vyacheslav Bogdanov.
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
#ifndef MATRIX_H_
#define MATRIX_H_

#include "IOGVector.h"

#define MAT00 0
#define MAT01 1
#define MAT02 2
#define MAT03 3
#define MAT10 4
#define MAT11 5
#define MAT12 6
#define MAT13 7
#define MAT20 8
#define MAT21 9
#define MAT22 10
#define MAT23 11
#define MAT30 12
#define MAT31 13
#define MAT32 14
#define MAT33 15

#define MAT(m,r,c) (m)[(c)*4+(r)]

#define _11 0
#define _12 1
#define _13 2
#define _14 3
#define _21 4
#define _22 5
#define _23 6
#define _24 7
#define _31 8
#define _32 9
#define _33 10
#define _34 11
#define _41 12
#define _42 13
#define _43 14
#define _44 15


/*!***************************************************************************
** 4x4 floating point matrix
** The elements of the 4x4 matrix are stored in 
** column-major order:
**    _11, _21, _31, _41; 
**    _12, _22, _32, _42; 
**    _13, _23, _33, _43; 
**    _14, _24, _34, _44; 
****************************************************************************/
class OGMatrix
{
public:
    /*!***************************************************************************
     @Function       []
     @Input          Row
     @Returns        pointer to a row
     @Description    access to matrix elements using [row][column]
     ****************************************************************************/
    float* operator [] ( const int Row )
	{
		return &f[Row<<2];
	}

    float f[16];	/*!< Array of float */
};


/*!***************************************************************************
 @Function      MatrixIdentity
 @Output        mOut resulting matrix
 @Description   Reset matrix to identity
 ****************************************************************************/
void MatrixIdentity(OGMatrix &mOut);


/*!***************************************************************************
 @Function      MatrixGetOrg
 @Output        vOut vector
 @Input         mIn matrix
 @Description   Returns the zero-point
 ****************************************************************************/
void MatrixGetOrg(OGVec3& vOut, const OGMatrix& mIn);


/*!***************************************************************************
 @Function      MatrixGetBasis
 @Input         basis X axis
 @Input         basis Y axis
 @Input         basis Z axis
 @Input         mIn matrix
 @Description   Returns the basis vectors
 ****************************************************************************/
void MatrixGetBasis(
    OGVec3& vOutX, 
    OGVec3& vOutY, 
    OGVec3& vOutZ, 
    const OGMatrix& mIn);


/*!***************************************************************************
 @Function      MatrixMultiply
 @Output        mOut resulting matrix
 @Input         Matrix A
 @Input         Matrix B
 @Description   Multiply mA by mB and assign the result to matrix (mA * mB). 
 ****************************************************************************/
void MatrixMultiply(OGMatrix& mOut, const OGMatrix& mA, const OGMatrix& mB);


/*!***************************************************************************
 @Function      MatrixVec4Multiply
 @Output        vOut resulting vector
 @Input         Input vector
 @Input         Input matrix
 @Description   Multiply vector vIn by matrix. 
 ****************************************************************************/
void MatrixVec4Multiply(OGVec4& vOut, const OGVec4& vIn, const OGMatrix& mIn);


/*!***************************************************************************
 @Function      MatrixVecMultiply
 @Output        Output vector
 @Input         Input vector
 @Input         Input matrix
 @Description   Transform point represented using the matrix. 
 ****************************************************************************/
void MatrixVecMultiply(OGVec3& vOut, const OGVec3& vIn, const OGMatrix& mIn);


/*!***************************************************************************
 @Function      MatrixVec3Multiply
 @Output        Output vector
 @Input         Input vector
 @Input         Input matrix
 @Description   Transform vector vIn using the matrix. 
 ****************************************************************************/
void MatrixVec3Multiply(OGVec3& vOut, const OGVec3& vIn, const OGMatrix& mIn);


/*!***************************************************************************
 @Function      MatrixTranslation
 @Output        Output matrix
 @Input         Input vector X
 @Input         Input vector Y
 @Input         Input vector Z
 @Description   Build a translation matrix mOut using fX, fY and fZ. 
 ****************************************************************************/
void MatrixTranslation(OGMatrix& mOut, float fX, float fY, float fZ);
	

/*!***************************************************************************
 @Function      MatrixScaling
 @Output        Output matrix
 @Input         Input vector X
 @Input         Input vector Y
 @Input         Input vector Z
 @Description   Build a scale matrix mOut using fX, fY and fZ.
 ****************************************************************************/
void MatrixScaling(OGMatrix& mOut, float fX, float fY, float fZ);


/*!***************************************************************************
 @Function      MatrixRotationAxis
 @Output        Output matrix
 @Input         Input angle
 @Input         Input vector X
 @Input         Input vector Y
 @Input         Input vector Z
 @Description   Create an around-axis rotation matrix mOut.
 ****************************************************************************/
void MatrixRotationAxis(OGMatrix& mOut, float fAngle, float fX, float fY, float fZ);


/*!***************************************************************************
 @Function      MatrixRotationX
 @Output        Output matrix
 @Input         Input angle
 @Description   Create an X rotation matrix mOut.
 ****************************************************************************/
void MatrixRotationX(OGMatrix& mOut, float fAngle);


/*!***************************************************************************
 @Function      MatrixRotationY
 @Output        Output matrix
 @Input         Input angle
 @Description   Create an Y rotation matrix mOut.
 ****************************************************************************/
void MatrixRotationY(OGMatrix& mOut, float fAngle);


/*!***************************************************************************
 @Function      MatrixRotationZ
 @Output        Output matrix
 @Input         Input angle
 @Description   Create an Z rotation matrix mOut.
 ****************************************************************************/
void MatrixRotationZ(OGMatrix& mOut, float fAngle);


/*!***************************************************************************
 @Function      MatrixTranspose
 @Output        Output matrix
 @Input         Input matrix
 @Description   Compute the transpose matrix of mIn.
 ****************************************************************************/
void MatrixTranspose(OGMatrix& mOut, const OGMatrix &mIn);


/*!***************************************************************************
 @Function      MatrixInverse
 @Output        Output matrix
 @Input         Input matrix
 @Description   Compute the inverse matrix of mIn.
                The matrix must be of the form:
                 A 0
                 C 1
                Where A is a 3x3 matrix and C is a 1x3 matrix.
 ****************************************************************************/
void MatrixInverse(OGMatrix& mOut, const OGMatrix& mIn);


/*!***************************************************************************
 @Function      MatrixInverseEx
 @Output        Output matrix
 @Input         Input matrix
 @Description   Compute the inverse matrix of mIn.
                Uses a linear equation solver and the knowledge that M.M^-1=I.
                Use this fn to calculate the inverse of matrices that
                MatrixInverse() cannot.
 ****************************************************************************/
void MatrixInverseEx(OGMatrix& mOut, const OGMatrix& mIn);


/*!***************************************************************************
 @Function      MatrixInverseEx2
 @Output        Output matrix
 @Input         Input matrix
 @Description   Another one matrix inversion from MESA.
 ****************************************************************************/
bool MatrixInverseEx2(OGMatrix& mOut, const OGMatrix& mIn);


/*!***************************************************************************
 @Function      MatrixLookAtLH
 @Output        Output matrix
 @Input         eye point
 @Input         look at point
 @Input         up vector
 @Description   Create a left-handed look-at view matrix.
 ****************************************************************************/
void MatrixLookAtLH(
	OGMatrix& mOut,
	const OGVec3& vEye,
	const OGVec3& vAt,
	const OGVec3& vUp);


/*!***************************************************************************
 @Function      MatrixLookAtRH
 @Output        Output matrix
 @Input         eye point
 @Input         look at point
 @Input         up vector
 @Description   Create a right-handed look-at view matrix.
 ****************************************************************************/
void MatrixLookAtRH(
	OGMatrix& mOut,
	const OGVec3& vEye,
	const OGVec3& vAt,
	const OGVec3& vUp);


/*!***************************************************************************
 @Function      MatrixPerspectiveFovLH
 @Output        Output matrix
 @Input         field of view
 @Input         aspect ratio
 @Input         Z near
 @Input         Z far
 @Input         is view rotated
 @Description   Create a left-handed perspective projection matrix.
 ****************************************************************************/
void MatrixPerspectiveFovLH(
	OGMatrix& mOut,
	float fFOVy,
	float fAspect,
	float fNear,
	float fFar,
	bool bRotate = false);


/*!***************************************************************************
 @Function      MatrixPerspectiveFovRH
 @Output        Output matrix
 @Input         field of view
 @Input         aspect ratio
 @Input         Z near
 @Input         Z far
 @Input         is view rotated
 @Description   Create a right-handed perspective projection matrix.
 ****************************************************************************/
void MatrixPerspectiveFovRH(
	OGMatrix& mOut,
	float fFOVy,
	float fAspect,
	float fNear,
	float fFar,
	bool bRotate = false);


/*!***************************************************************************
 @Function      MatrixOrthoLH
 @Output        Output matrix
 @Input         view width
 @Input         view height
 @Input         Z near
 @Input         Z far
 @Input         is view rotated
 @Description   Create a left-handed orthographic projection matrix.
 ****************************************************************************/
void MatrixOrthoLH(
	OGMatrix& mOut,
	float w,
	float h,
	float zn,
	float zf,
	bool  bRotate = false);


/*!***************************************************************************
 @Function      MatrixOrthoRH
 @Output        Output matrix
 @Input         view width
 @Input         view height
 @Input         Z near
 @Input         Z far
 @Input         is view rotated
 @Description   Create a right-handed orthographic projection matrix.
 ****************************************************************************/
void MatrixOrthoRH(
	OGMatrix& mOut,
	float w,
	float h,
	float zn,
	float zf,
	bool  bRotate = false);

#endif
