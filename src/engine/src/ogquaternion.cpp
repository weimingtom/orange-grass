/*****************************************************************************
 *  Quaternion.cpp
 *  OrangeGrass
 *
 *  Copyright 2009-2012 Viacheslav Bogdanov. All rights reserved.
 *
 ****************************************************************************/
#include "IOGCoreHelpers.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "IOGQuaternion.h"


/*!***************************************************************************
 @Function       QuaternionIdentity
 @Output         qOut resulting quaternion
 @Description    Set quaternion to identity value.
 ****************************************************************************/
void QuaternionIdentity(OGQuat& qOut)
{
    qOut.x = 0;
    qOut.y = 0;
    qOut.z = 0;
    qOut.w = 1;
}


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
    float fAngle)
{
    float fSin, fCos;

    fSin = sinf(fAngle * 0.5f);
    fCos = cosf(fAngle * 0.5f);

    /* Create quaternion */
    qOut.x = vAxis.x * fSin;
    qOut.y = vAxis.y * fSin;
    qOut.z = vAxis.z * fSin;
    qOut.w = fCos;

    /* Normalise it */
    QuaternionNormalize(qOut);
}


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
    float& fAngle)
{
    float	fCosAngle, fSinAngle;
    float	temp;

    /* Compute some values */
    fCosAngle	= qIn.w;
    temp		= 1.0f - fCosAngle*fCosAngle;
    fAngle		= acosf(fCosAngle)*2.0f;
    fSinAngle	= sqrtf(temp);

    /* This is to avoid a division by zero */
    if (fabsf(fSinAngle)<0.0005f)
        fSinAngle = 1.0f;

    /* Get axis vector */
    vAxis.x = qIn.x / fSinAngle;
    vAxis.y = qIn.y / fSinAngle;
    vAxis.z = qIn.z / fSinAngle;
}


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
    float t)
{
    float fCosine, fAngle, A, B;

    /* Parameter checking */
    if (t<0.0f || t>1.0f)
    {
        OG_LOG_WARNING("QuaternionSlerp: Bad parameters");
        qOut.x = 0;
        qOut.y = 0;
        qOut.z = 0;
        qOut.w = 1;
        return;
    }

    /* Find sine of Angle between Quaternion A and B (dot product between quaternion A and B) */
    fCosine = qA.w*qB.w + qA.x*qB.x + qA.y*qB.y + qA.z*qB.z;

    if (fCosine < 0)
    {
        OGQuat qi;
        qi.x = -qB.x;
        qi.y = -qB.y;
        qi.z = -qB.z;
        qi.w = -qB.w;

        QuaternionSlerp(qOut, qA, qi, t);
        return;
    }

    fCosine = OG_MIN(fCosine, 1.0f);
    fAngle = acosf(fCosine);

    /* Avoid a division by zero */
    if (fAngle==0.0f)
    {
        qOut = qA;
        return;
    }

    /* Precompute some values */
    A = sinf((1.0f-t)*fAngle) / sinf(fAngle);
    B = sinf(t*fAngle) / sinf(fAngle);

    /* Compute resulting quaternion */
    qOut.x = A * qA.x + B * qB.x;
    qOut.y = A * qA.y + B * qB.y;
    qOut.z = A * qA.z + B * qB.z;
    qOut.w = A * qA.w + B * qB.w;

    /* Normalise result */
    QuaternionNormalize(qOut);
}


/*!***************************************************************************
 @Function       QuaternionNormalize
 @Output         quat resulting quaternion
 @Description    Normalize quaternion.
 ****************************************************************************/
void QuaternionNormalize(OGQuat& quat)
{
    float	fMagnitude;
    float	temp;

    /* Compute quaternion magnitude */
    temp = quat.w*quat.w + quat.x*quat.x + quat.y*quat.y + quat.z*quat.z;
    fMagnitude = sqrtf(temp);

    /* Divide each quaternion component by this magnitude */
    if (fMagnitude!=0.0f)
    {
        fMagnitude = 1.0f / fMagnitude;
        quat.x *= fMagnitude;
        quat.y *= fMagnitude;
        quat.z *= fMagnitude;
        quat.w *= fMagnitude;
    }
}


/*!***************************************************************************
 @Function       QuaternionToRotationMatrix
 @Output         mOut rotation matrix output
 @Input          quat quaternion
 @Description    Create rotation matrix from quaternion.
 ****************************************************************************/
void QuaternionToRotationMatrix(OGMatrix& mOut, const OGQuat& quat)
{
    const OGQuat *pQ;
    pQ = &quat;

    /* Fill matrix members */
    mOut.f[0] = 1.0f - 2.0f*pQ->y*pQ->y - 2.0f*pQ->z*pQ->z;
    mOut.f[1] = 2.0f*pQ->x*pQ->y - 2.0f*pQ->z*pQ->w;
    mOut.f[2] = 2.0f*pQ->x*pQ->z + 2.0f*pQ->y*pQ->w;
    mOut.f[3] = 0.0f;

    mOut.f[4] = 2.0f*pQ->x*pQ->y + 2.0f*pQ->z*pQ->w;
    mOut.f[5] = 1.0f - 2.0f*pQ->x*pQ->x - 2.0f*pQ->z*pQ->z;
    mOut.f[6] = 2.0f*pQ->y*pQ->z - 2.0f*pQ->x*pQ->w;
    mOut.f[7] = 0.0f;

    mOut.f[8] = 2.0f*pQ->x*pQ->z - 2*pQ->y*pQ->w;
    mOut.f[9] = 2.0f*pQ->y*pQ->z + 2.0f*pQ->x*pQ->w;
    mOut.f[10] = 1.0f - 2.0f*pQ->x*pQ->x - 2*pQ->y*pQ->y;
    mOut.f[11] = 0.0f;

    mOut.f[12] = 0.0f;
    mOut.f[13] = 0.0f;
    mOut.f[14] = 0.0f;
    mOut.f[15] = 1.0f;
}


/*!***************************************************************************
 @Function       QuaternionMultiply
 @Output         qOut resulting quaternion
 @Input          q a quaternion to multiply by
 @Description    quaternions multiplication
 ****************************************************************************/
void QuaternionMultiply(
    OGQuat& qOut,
    const OGQuat& qA,
    const OGQuat& qB)
{
    OGVec3	CrossProduct;

    /* Compute scalar component */
    qOut.w = (qA.w*qB.w) - (qA.x*qB.x + qA.y*qB.y + qA.z*qB.z);

    /* Compute cross product */
    CrossProduct.x = qA.y*qB.z - qA.z*qB.y;
    CrossProduct.y = qA.z*qB.x - qA.x*qB.z;
    CrossProduct.z = qA.x*qB.y - qA.y*qB.x;

    /* Compute result vector */
    qOut.x = (qA.w * qB.x) + (qB.w * qA.x) + CrossProduct.x;
    qOut.y = (qA.w * qB.y) + (qB.w * qA.y) + CrossProduct.y;
    qOut.z = (qA.w * qB.z) + (qB.w * qA.z) + CrossProduct.z;

    /* Normalize resulting quaternion */
    QuaternionNormalize(qOut);
}
