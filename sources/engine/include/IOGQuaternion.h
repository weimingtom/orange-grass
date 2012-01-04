/*****************************************************************************
 *  Quaternion.h
 *  OrangeGrass
 *
 *  Copyright 2009-2012 Viacheslav Bogdanov. All rights reserved.
 *
 ****************************************************************************/
#ifndef QUATERNION_H_
#define QUATERNION_H_

#include "IOGMatrix.h"


/*!***************************************************************************
** Quaternion implementation
*****************************************************************************/
typedef struct
{
	float x;	/*!< x coordinate */
	float y;	/*!< y coordinate */
	float z;	/*!< z coordinate */
	float w;	/*!< w coordinate */
} OGQuat;


/*!***************************************************************************
 @Function       QuaternionIdentity
 @Output         qOut resulting quaternion
 @Description    Set quaternion to identity value.
 ****************************************************************************/
void QuaternionIdentity(OGQuat& qOut);


/*!***************************************************************************
 @Function       QuaternionRotationAxis
 @Output         qOut resulting quaternion
 @Input          vAxis axis vector.
 @Input          fAngle angle in radians.
 @Description    Build quaternion from axis and angle.
 ****************************************************************************/
void QuaternionRotationAxis(
	OGQuat& qOut,
	const OGVec3& vAxis,
	float fAngle);


/*!***************************************************************************
 @Function       QuaternionToAxisAngle
 @Input          qIn resulting quaternion
 @Input          vAxis output axis vector.
 @Input          fAngle output angle in radians.
 @Description    Convert to axis and angle.
 ****************************************************************************/
void QuaternionToAxisAngle(
	const OGQuat& qIn,
	OGVec3& vAxis,
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
	OGQuat& qOut,
	const OGQuat& qA,
	const OGQuat& qB,
	float t);


/*!***************************************************************************
 @Function       QuaternionNormalize
 @Output         quat resulting quaternion
 @Description    Normalize quaternion.
 ****************************************************************************/
void QuaternionNormalize(OGQuat &quat);


/*!***************************************************************************
 @Function       QuaternionToRotationMatrix
 @Output         mOut rotation matrix output
 @Input          quat quaternion
 @Description    Create rotation matrix from quaternion.
 ****************************************************************************/
void QuaternionToRotationMatrix(OGMatrix& mOut, const OGQuat& quat);


/*!***************************************************************************
 @Function       QuaternionMultiply
 @Output         qOut resulting quaternion
 @Input          q a quaternion to multiply by
 @Description    quaternions multiplication
 ****************************************************************************/
void QuaternionMultiply(
	OGQuat& qOut,
	const OGQuat& qA,
	const OGQuat& qB);


#endif
