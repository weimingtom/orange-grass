/*****************************************************************************
 *  Quaternion.h
 *  OrangeGrass
 *
 *  Copyright 2009-2012 Viacheslav Bogdanov. All rights reserved.
 *
 ****************************************************************************/
#ifndef QUATERNION_H_
#define QUATERNION_H_

#include "Matrix.h"


/*!***************************************************************************
** Quaternion implementation
*****************************************************************************/
typedef struct
{
	float x;	/*!< x coordinate */
	float y;	/*!< y coordinate */
	float z;	/*!< z coordinate */
	float w;	/*!< w coordinate */
} QUATERNION;


/*!***************************************************************************
 @Function       QuaternionIdentity
 @Output         qOut resulting quaternion
 @Description    Set quaternion to identity value.
 ****************************************************************************/
void QuaternionIdentity(QUATERNION& qOut);


/*!***************************************************************************
 @Function       QuaternionRotationAxis
 @Output         qOut resulting quaternion
 @Input          vAxis axis vector.
 @Input          fAngle angle in radians.
 @Description    Build quaternion from axis and angle.
 ****************************************************************************/
void QuaternionRotationAxis(
	QUATERNION& qOut,
	const VECTOR3& vAxis,
	float fAngle);


/*!***************************************************************************
 @Function       QuaternionToAxisAngle
 @Input          qIn resulting quaternion
 @Input          vAxis output axis vector.
 @Input          fAngle output angle in radians.
 @Description    Convert to axis and angle.
 ****************************************************************************/
void QuaternionToAxisAngle(
	const QUATERNION& qIn,
	VECTOR3& vAxis,
	float& fAngle);


/*!***************************************************************************
 @Function       QuaternionSlerp
 @Output         qOut resulting quaternion
 @Input          qA 1st quaternion.
 @Input          qB 2nd quaternion.
 @Input          t interpolation factor.
 @Description    Spherical linear interpolation.
 ****************************************************************************/
void QuaternionSlerp(
	QUATERNION& qOut,
	const QUATERNION& qA,
	const QUATERNION& qB,
	float t);


/*!***************************************************************************
 @Function       QuaternionNormalize
 @Output         quat resulting quaternion
 @Description    Normalize quaternion.
 ****************************************************************************/
void QuaternionNormalize(QUATERNION &quat);


/*!***************************************************************************
 @Function       QuaternionToRotationMatrix
 @Output         mOut rotation matrix output
 @Input          quat quaternion
 @Description    Create rotation matrix from quaternion.
 ****************************************************************************/
void QuaternionToRotationMatrix(MATRIX& mOut, const QUATERNION& quat);


/*!***************************************************************************
 @Function       QuaternionMultiply
 @Output         qOut resulting quaternion
 @Input          q a quaternion to multiply by
 @Description    quaternions multiplication
 ****************************************************************************/
void QuaternionMultiply(
	QUATERNION& qOut,
	const QUATERNION& qA,
	const QUATERNION& qB);


#endif
