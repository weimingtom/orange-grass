/*****************************************************************************
 *  Vector.cpp
 *  OrangeGrass
 *
 *  Copyright 2009-2012 Viacheslav Bogdanov. All rights reserved.
 *
 ****************************************************************************/
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Vector.h"


/*!***************************************************************************
 @Function      Vec3Lerp
 @Output        Output vector
 @Input         Input vector 1
 @Input         Input vector 2
 @Input         Input interpolator
 @Description   Linear interpolation of two Vec3s
 ****************************************************************************/
void Vec3Lerp(VECTOR3& vOut, const VECTOR3& v1, const VECTOR3& v2, float s)
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
float Vec3DotProduct(const VECTOR3& v1, const VECTOR3& v2)
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
void Vec3CrossProduct(VECTOR3& vOut, const VECTOR3& v1, const VECTOR3& v2)
{
    VECTOR3 result;

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
 @Description   Normalization of Vec3
 ****************************************************************************/
void Vec3Normalize(VECTOR3& vOut, const VECTOR3& vIn)
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
 @Description   Normalization of Vec4
 ****************************************************************************/
void Vec4Normalize(VECTOR4& vOut, const VECTOR4& vIn)
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
 @Description   Length of Vec3
 ****************************************************************************/
float Vec3Length(const VECTOR3& vIn)
{
    double temp;

    temp = (double)(vIn.x * vIn.x + vIn.y * vIn.y + vIn.z * vIn.z);
    return (float) sqrt(temp);
}
