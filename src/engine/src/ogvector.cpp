/*****************************************************************************
 *  ogvector.cpp
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
#include "IOGVector.h"


/*!***************************************************************************
 @Function      Vec3Lerp
 @Output        Output vector
 @Input         Input vector 1
 @Input         Input vector 2
 @Input         Input interpolator
 @Description   Linear interpolation of two Vec3s
 ****************************************************************************/
void Vec3Lerp(OGVec3& vOut, const OGVec3& v1, const OGVec3& v2, float s)
{
	vOut.x = v1.x + s * (v2.x - v1.x);
	vOut.y = v1.y + s * (v2.y - v1.y);
	vOut.z = v1.z + s * (v2.z - v1.z);
}


/*!***************************************************************************
 @Function      Vec3DotProduct
 @Input         Input vector 1
 @Input         Input vector 2
 @Returns		scalar product
 @Description   Dot product of two Vec3s
 ****************************************************************************/
float Vec3DotProduct(const OGVec3& v1, const OGVec3& v2)
{
    return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}


/*!***************************************************************************
 @Function      Vec3CrossProduct
 @Output        Output vector
 @Input         Input vector 1
 @Input         Input vector 2
 @Description   Cross product of two Vec3s
 ****************************************************************************/
void Vec3CrossProduct(OGVec3& vOut, const OGVec3& v1, const OGVec3& v2)
{
    OGVec3 result;

    /* Perform calculation on a dummy VECTOR (result) */
    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;

    /* Copy result in pOut */
    vOut = result;
}


/*!***************************************************************************
 @Function      Vec3Normalize
 @Output        Output vector
 @Input         Input vector
 @Description   Normalization of OGVec3
 ****************************************************************************/
void Vec3Normalize(OGVec3& vOut, const OGVec3& vIn)
{
    float	f;
    double temp;

    temp = (double)(vIn.x * vIn.x + vIn.y * vIn.y + vIn.z * vIn.z);
    temp = 1.0 / sqrt(temp);
    f = (float)temp;

    vOut.x = vIn.x * f;
    vOut.y = vIn.y * f;
    vOut.z = vIn.z * f;
}


/*!***************************************************************************
 @Function      Vec4Normalize
 @Output        Output vector
 @Input         Input vector
 @Description   Normalization of OGVec4
 ****************************************************************************/
void Vec4Normalize(OGVec4& vOut, const OGVec4& vIn)
{
    float	f;
    double temp;

    temp = (double)(vIn.x * vIn.x + vIn.y * vIn.y + vIn.z * vIn.z);
    temp = 1.0 / sqrt(temp);
    f = (float)temp;

    vOut.x = vIn.x * f;
    vOut.y = vIn.y * f;
    vOut.z = vIn.z * f;
    vOut.w = vIn.w * f;
}


/*!***************************************************************************
 @Function      Vec3DotProduct
 @Input         Input vector
 @Returns		length
 @Description   Length of OGVec3
 ****************************************************************************/
float Vec3Length(const OGVec3& vIn)
{
    double temp;

    temp = (double)(vIn.x * vIn.x + vIn.y * vIn.y + vIn.z * vIn.z);
    return (float) sqrt(temp);
}
