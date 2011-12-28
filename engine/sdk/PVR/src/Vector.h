/*****************************************************************************
 *  Vector.h
 *  OrangeGrass
 *
 *  Copyright 2009-2012 Viacheslav Bogdanov. All rights reserved.
 *
 ****************************************************************************/
#ifndef VECTOR_H_
#define VECTOR_H_

#ifdef __APPLE__
#include <OpenGLES/ES2/gl.h>
#endif
#include <math.h>
#include "Macros.h"


/*!***************************************************************************
 2D floating point vector
 *****************************************************************************/
typedef struct
{
    float x;	/*!< x coordinate */
    float y;	/*!< y coordinate */
} VECTOR2;


/*!***************************************************************************
 3D floating point vector
 *****************************************************************************/
typedef struct
{
    float x;	/*!< x coordinate */
    float y;	/*!< y coordinate */
    float z;	/*!< z coordinate */
} VECTOR3;


/*!***************************************************************************
 4D floating point vector
 *****************************************************************************/
typedef struct
{
    float x;	/*!< x coordinate */
    float y;	/*!< y coordinate */
    float z;	/*!< z coordinate */
    float w;	/*!< w coordinate */
} VECTOR4;


/*!***************************************************************************
 ** Vec2 2 component vector
 *****************************************************************************/
struct Vec2 : public VECTOR2
{
    /*!***************************************************************************
 	 @Function			Vec2
	 @Description		Blank constructor.
	 *****************************************************************************/
    Vec2() {x = y = 0;}

    /*!***************************************************************************
     @Function			Vec2
     @Input				fX	X component of vector
     @Input				fY	Y component of vector
     @Description		Simple constructor from 2 values.
     *****************************************************************************/
	Vec2(float fX, float fY) { x = fX; y = fY; }
	
    /*!***************************************************************************
 	 @Function			Vec2
 	 @Input				fValue	a component value
	 @Description		Constructor from a single value.
	 *****************************************************************************/
	Vec2(float fValue) { x = fValue; y = fValue; }
	
    /*!***************************************************************************
	 @Function			Vec2
	 @Input				pVec	an array
	 @Description		Constructor from an array
	 *****************************************************************************/
	Vec2(const float* pVec) { x = pVec[0]; y = pVec[1]; }
	
	/*!***************************************************************************
     @Function			+
     @Input				rhs another Vec2
     @Returns			result of addition
     @Description		componentwise addition operator for two Vec2s
     *****************************************************************************/
	Vec2 operator+(const Vec2& rhs) const
	{
		Vec2 out(*this);
		return out += rhs;
	}

    /*!***************************************************************************
     @Function			-
     @Input				rhs another Vec2
     @Returns			result of subtraction
     @Description		componentwise subtraction operator for two Vec2s
     ****************************************************************************/
    Vec2 operator-(const Vec2& rhs) const
    {
        Vec2 out(*this);
        return out -= rhs;
    }

    /*!***************************************************************************
     @Function			+=
     @Input				rhs another Vec2
     @Returns			result of addition
     @Description		componentwise addition and assignment operator for two Vec2s
     ****************************************************************************/
    Vec2& operator+=(const Vec2& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    /*!***************************************************************************
     @Function			-=
     @Input				rhs another Vec2
     @Returns			result of subtraction
     @Description		componentwise subtraction and assignment operator for two Vec2s
     ****************************************************************************/
    Vec2& operator-=(const Vec2& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    /*!***************************************************************************
     @Function			-
     @Input				rhs another Vec2
     @Returns			result of negation
     @Description		negation operator for a Vec2
     ****************************************************************************/
    friend Vec2 operator- (const Vec2& rhs) { return Vec2(-rhs.x, -rhs.y); }

    /*!***************************************************************************
     @Function			*
     @Input				lhs scalar
     @Input				rhs a Vec2
     @Returns			result of negation
     @Description		negation operator for a Vec2
     ****************************************************************************/
    friend Vec2 operator*(const float lhs, const Vec2&  rhs)
    {
        Vec2 out(lhs);
        return out *= rhs;
    }

    /*!***************************************************************************
     @Function			/
     @Input				lhs scalar
     @Input				rhs a Vec2
     @Returns			result of division
     @Description		division operator for scalar and Vec2
     ****************************************************************************/
    friend Vec2 operator/(const float lhs, const Vec2&  rhs)
    {
        Vec2 out(lhs);
        return out /= rhs;
    }

    /*!***************************************************************************
     @Function			*
     @Input				rhs a scalar
     @Returns			result of multiplication
     @Description		componentwise multiplication by scalar for Vec2
     ****************************************************************************/
    Vec2 operator*(const float& rhs) const
    {
        Vec2 out(*this);
        return out *= rhs;
    }

    /*!***************************************************************************
     @Function			*=
     @Input				rhs a scalar
     @Returns			result of multiplication and assignment
     @Description		componentwise multiplication and assignment by scalar for Vec2
     ****************************************************************************/
    Vec2& operator*=(const float& rhs)
    {
        x = x * rhs;
        y = y * rhs;
        return *this;
    }

    /*!***************************************************************************
     @Function			*=
     @Input				rhs a Vec2
     @Returns			result of multiplication and assignment
     @Description		componentwise multiplication and assignment by Vec2 for Vec2
     ****************************************************************************/
    Vec2& operator*=(const Vec2& rhs)
    {
        x = x * rhs.x;
        y = y * rhs.y;
        return *this;
    }

    /*!***************************************************************************
     @Function			/
     @Input				rhs a scalar
     @Returns			result of division
     @Description		componentwise division by scalar for Vec2
     ****************************************************************************/
    Vec2 operator/(const float& rhs) const
    {
        Vec2 out(*this);
        return out /= rhs;
    }

    /*!***************************************************************************
     @Function			/=
     @Input				rhs a scalar
     @Returns			result of division and assignment
     @Description		componentwise division and assignment by scalar for Vec2
     ****************************************************************************/
    Vec2& operator/=(const float& rhs)
    {
        x = x / rhs;
        y = y / rhs;
        return *this;
    }

    /*!***************************************************************************
     @Function			/=
     @Input				rhs a Vec2
     @Returns			result of division and assignment
     @Description		componentwise division and assignment by Vec2 for Vec2
     ****************************************************************************/
    Vec2& operator/=(const Vec2& rhs)
    {
        x = x / rhs.x;
        y = y / rhs.y;
        return *this;
    }	

    /*!***************************************************************************
     @Function			lenSqr
     @Returns			the square of the magnitude of the vector
     @Description		calculates the square of the magnitude of the vector
     ****************************************************************************/
    float lenSqr() const
    {
        return x*x + y*y;
    }

    /*!***************************************************************************
     @Function			length
     @Returns			the of the magnitude of the vector
     @Description		calculates the magnitude of the vector
     ****************************************************************************/
    float length() const
    {
        return sqrtf(x*x + y*y);
    }

    /*!***************************************************************************
     @Function			normalize
     @Returns			the normalized value of the vector
     @Description		normalizes the vector
     ****************************************************************************/
    Vec2 normalize()
    {
        return *this /= length();
    }

    /*!***************************************************************************
     @Function			normalized
     @Returns			returns the normalized value of the vector
     @Description		returns a normalized vector of the same direction as this
                        vector
     ****************************************************************************/
    Vec2 normalized() const
    {
        Vec2 out(*this);
        return out.normalize();
    }

    /*!***************************************************************************
     @Function			rotated90
     @Returns			returns the vector rotated 90ﾰ
     @Description		returns the vector rotated 90ﾰ
     ****************************************************************************/
    Vec2 rotated90() const
    {
        return Vec2(-y, x);
    }

    /*!***************************************************************************
     @Function			dot
     @Input				rhs a single value
     @Returns			scalar product
     @Description		calculate the scalar product of two Vec3s
     ****************************************************************************/
    float dot(const Vec2& rhs)
    {
        return x * rhs.x + y * rhs.y;
    }

    /*!***************************************************************************
     @Function			ptr
     @Returns			pointer
     @Description		returns a pointer to memory containing the values of the
                        Vec3
     ****************************************************************************/
    float *ptr() { return (float*)this; }
};


/*!***************************************************************************
 ** Vec3 3 component vector
 ****************************************************************************/
struct Vec3 : public VECTOR3
{
    /*!***************************************************************************
    @Function			Vec3
    @Description		Blank constructor.
    *****************************************************************************/
    Vec3() { x = y = z = 0; }

    /*!***************************************************************************
    @Function			Vec3
    @Input				fX	X component of vector
    @Input				fY	Y component of vector
    @Input				fZ	Z component of vector
    @Description		Simple constructor from 3 values.
    *****************************************************************************/
    Vec3(float fX, float fY, float fZ)
    {
        x = fX;	y = fY;	z = fZ;
    }

    /*!***************************************************************************
    @Function			Vec3
    @Input				fValue	a component value
    @Description		Constructor from a single value.
    *****************************************************************************/
    Vec3(const float fValue)
    {
        x = fValue; y = fValue; z = fValue;
    }

    /*!***************************************************************************
    @Function			Vec3
    @Input				pVec	an array
    @Description		Constructor from an array
    *****************************************************************************/
    Vec3(const float* pVec)
    {
        x = (*pVec++); y = (*pVec++); z = *pVec;
    }

    /*!***************************************************************************
    @Function			+
    @Input				rhs another Vec3
    @Returns			result of addition
    @Description		componentwise addition operator for two VECTOR3s
    *****************************************************************************/
	Vec3 operator+(const Vec3& rhs) const
	{
		Vec3 out;
		out.x = x+rhs.x;
		out.y = y+rhs.y;
		out.z = z+rhs.z;
		return out;
	}

    /*!***************************************************************************
    @Function			-
    @Input				rhs another Vec3
    @Returns			result of subtraction
    @Description		componentwise subtraction operator for two VECTOR3s
    ****************************************************************************/
    Vec3 operator-(const Vec3& rhs) const
    {
        Vec3 out;
        out.x = x-rhs.x;
        out.y = y-rhs.y;
        out.z = z-rhs.z;
        return out;
    }

    /*!***************************************************************************
    @Function			+=
    @Input				rhs another Vec3
    @Returns			result of addition
    @Description		componentwise addition and assignement operator for two 
                        VECTOR3s
    ****************************************************************************/
    Vec3& operator+=(const Vec3& rhs)
    {
        x +=rhs.x;
        y +=rhs.y;
        z +=rhs.z;
        return *this;
    }

    /*!***************************************************************************
    @Function			-=
    @Input				rhs another Vec3
    @Returns			result of subtraction
    @Description		componentwise subtraction and assignement operator for two 
                        VECTOR3s
    ****************************************************************************/
    Vec3& operator-=(const Vec3& rhs)
    {
        x -=rhs.x;
        y -=rhs.y;
        z -=rhs.z;
        return *this;
    }

    /*!***************************************************************************
    @Function			-
    @Input				rhs another Vec3
    @Returns			result of negation
    @Description		negation operator for a Vec3
    ****************************************************************************/
    friend Vec3 operator - (const Vec3& rhs) { return Vec3(rhs) *= -1; }

    /*!***************************************************************************
    @Function			*
    @Input				lhs single value
    @Input				rhs a Vec3
    @Returns			result of negation
    @Description		negation operator for a Vec3
    ****************************************************************************/
    friend Vec3 operator*(const float lhs, const Vec3&  rhs)
    {
        Vec3 out;
        out.x = lhs * rhs.x;
        out.y = lhs * rhs.y;
        out.z = lhs * rhs.z;
        return out;
    }

    /*!***************************************************************************
    @Function			*
    @Input				lhs single value
    @Input				rhs a Vec3
    @Returns			result of negation
    @Description		negation operator for a Vec3
    ****************************************************************************/
    friend Vec3 operator/(const float lhs, const Vec3&  rhs)
    {
        Vec3 out;
        out.x = lhs / rhs.x;
        out.y = lhs / rhs.y;
        out.z = lhs / rhs.z;
        return out;
    }

    /*!***************************************************************************
    @Function			*
    @Input				rhs a single value
    @Returns			result of multiplication
    @Description		componentwise multiplication by single dimension value for 
                        Vec3
    ****************************************************************************/
    Vec3 operator*(const float& rhs) const
    {
        Vec3 out;
        out.x = x * rhs;
        out.y = y * rhs;
        out.z = z * rhs;
        return out;
    }

    /*!***************************************************************************
    @Function			*
    @Input				rhs a single value
    @Returns			result of multiplication and assignment
    @Description		componentwise multiplication and assignement by single
                        dimension value	for Vec3
    ****************************************************************************/
    Vec3& operator*=(const float& rhs)
    {
        x = x * rhs;
        y = y * rhs;
        z = z * rhs;
        return *this;
    }

    /*!***************************************************************************
    @Function			/
    @Input				rhs a single value
    @Returns			result of division
    @Description		componentwise division by single
                        dimension value	for Vec3
    ****************************************************************************/
    Vec3 operator/(const float& rhs) const
    {
        Vec3 out;
        out.x = x / rhs;
        out.y = y / rhs;
        out.z = z / rhs;
        return out;
    }

    /*!***************************************************************************
    @Function			/=
    @Input				rhs a single value
    @Returns			result of division and assignment
    @Description		componentwise division and assignement by single
                        dimension value	for Vec3
    ****************************************************************************/
    Vec3& operator/=(const float& rhs)
    {
        x = x / rhs;
        y = y / rhs;
        z = z / rhs;
        return *this;
    }

    /*!***************************************************************************
    @Function			==
    @Input				rhs a vector
    @Returns			result of comparison
    @Description		componentwise comparison
    ****************************************************************************/
    bool operator==(const Vec3& rhs)
    {
        return (x==rhs.x && y==rhs.y && z==rhs.z);
    }

    /*!***************************************************************************
    @Function			!=
    @Input				rhs a vector
    @Returns			result of comparison
    @Description		componentwise comparison
    ****************************************************************************/
    bool operator!=(const Vec3& rhs)
    {
        return (x!=rhs.x || y!=rhs.y || z!=rhs.z);
    }

    /*!***************************************************************************
    @Function			[] - r/o
    @Input				index
    @Returns			component value
    @Description		Get components by index
    ****************************************************************************/
    float operator [] ( int _ComponentIndex ) const
    {
        return ( (float *)this) [ _ComponentIndex ];
    }

    /*!***************************************************************************
    @Function			[] - w
    @Input				index
    @Returns			component value
    @Description		Set components by index
    ****************************************************************************/
    float& operator [] ( int _ComponentIndex )
    {
        return ( (float *)this) [ _ComponentIndex ];
    }

    /*!***************************************************************************
    @Function			lenSqr
    @Returns			the square of the magnitude of the vector
    @Description		calculates the square of the magnitude of the vector
    ****************************************************************************/
    float lenSqr() const
    {
        return x*x + y*y + z*z;
    }

    /*!***************************************************************************
    @Function			length
    @Returns			the of the magnitude of the vector
    @Description		calculates the magnitude of the vector
    ****************************************************************************/
    float length() const
    {
        return sqrtf(x*x + y*y + z*z);
    }

    /*!***************************************************************************
    @Function			normalize
    @Returns			the normalized value of the vector
    @Description		normalizes the vector
    ****************************************************************************/
    Vec3 normalize()
    {
        float len = length();
        x = x / len;
        y = y / len;
        z = z / len;
        return *this;
    }

    /*!***************************************************************************
    @Function			normalized
    @Returns			returns the normalized value of the vector
    @Description		returns a normalized vector of the same direction as this
                        vector
    ****************************************************************************/
    Vec3 normalized() const
    {
        Vec3 out;
        float len = length();
        out.x = x / len;
        out.y = y / len;
        out.z = z / len;
        return out;
    }

    /*!***************************************************************************
    @Function			dot
    @Input				rhs a single value
    @Returns			scalar product
    @Description		calculate the scalar product of two VECTOR3s
    ****************************************************************************/
    float dot(const Vec3& rhs) const
    {
        return x*rhs.x + y*rhs.y + z*rhs.z;
    }

    /*!***************************************************************************
    @Function			dot
    @Returns			scalar product
    @Description		calculate the scalar product of two VECTOR3s
    ****************************************************************************/
    Vec3 cross(const Vec3& rhs) const
    {
        Vec3 out;
        out.x = y*rhs.z - z*rhs.y;
        out.y = z*rhs.x - x*rhs.z;
        out.z = x*rhs.y - y*rhs.x;
        return out;
    }

    /*!***************************************************************************
    @Function			ptr
    @Returns			pointer
    @Description		returns a pointer to memory containing the values of the
                        Vec3
    ****************************************************************************/
    float *ptr() { return (float*)this; }
};


/*!***************************************************************************
** Vec4 4 component vector
*****************************************************************************/
struct Vec4 : public VECTOR4
{
    /*!***************************************************************************
    @Function			Vec4
    @Description		Blank constructor.
    *****************************************************************************/
    Vec4(){x = y = z = w = 0;}

    /*!***************************************************************************
    @Function			Vec3
    @Description		Blank constructor.
    *****************************************************************************/
    Vec4(const float vec)
    {
        x = vec; y = vec; z = vec; w = vec;
    }

    /*!***************************************************************************
    @Function			multiple value constructor
    @Input				fX value of x component
    @Input				fY value of y component
    @Input				fZ value of z component
    @Input				fW value of w component
    @Description		Constructs a Vec4 from 4 separate values
    ****************************************************************************/
    Vec4(float fX, float fY, float fZ, float fW)
    {
        x = fX;	y = fY;	z = fZ;	w = fW;
    }

    /*!***************************************************************************
    @Function			constructor from Vec3
    @Input				vec3 a Vec3
    @Input				fW value of w component
    @Description		Constructs a Vec4 from a vec3 and a w component
    ****************************************************************************/
    Vec4(const Vec3& vec3, float fW)
    {
        x = vec3.x;	y = vec3.y;	z = vec3.z;	w = fW;
    }

    /*!***************************************************************************
    @Function			constructor from Vec3
    @Input				fX value of x component
    @Input				vec3 a Vec3
    @Description		Constructs a vec4 from a vec3 and a w component
    ****************************************************************************/
    Vec4(float fX, const Vec3& vec3)
    {
        x = fX;	y = vec3.x;	z = vec3.y;	w = vec3.z;
    }

    /*!***************************************************************************
    @Function			constructor from array
    @Input				pVec a pointer to an array of four values
    @Description		Constructs a Vec4 from a pointer to an array of four values
    ****************************************************************************/
    Vec4(const float* pVec)
    {
        x = (*pVec++); y = (*pVec++); z= (*pVec++); w = *pVec;
    }

    /*!***************************************************************************
    @Function			+
    @Input				rhs another Vec4
    @Returns			result of addition
    @Description		Addition operator for Vec4
    ****************************************************************************/
    Vec4 operator+(const Vec4& rhs) const
    {
        Vec4 out;
        out.x = x+rhs.x;
        out.y = y+rhs.y;
        out.z = z+rhs.z;
        out.w = w+rhs.w;
        return out;
    }

    /*!***************************************************************************
    @Function			-
    @Input				rhs another Vec4
    @Returns			result of subtraction
    @Description		Subtraction operator for Vec4
    ****************************************************************************/
    Vec4 operator-(const Vec4& rhs) const
    {
        Vec4 out;
        out.x = x-rhs.x;
        out.y = y-rhs.y;
        out.z = z-rhs.z;
        out.w = w-rhs.w;
        return out;
    }

    /*!***************************************************************************
    @Function			+=
    @Input				rhs another Vec4
    @Returns			result of addition and assignment
    @Description		Addition and assignment operator for Vec4
    ****************************************************************************/
    Vec4& operator+=(const Vec4& rhs)
    {
        x +=rhs.x;
        y +=rhs.y;
        z +=rhs.z;
        w +=rhs.w;
        return *this;
    }

    /*!***************************************************************************
    @Function			-=
    @Input				rhs another Vec4
    @Returns			result of subtraction and assignment
    @Description		Subtraction and assignment operator for Vec4
    ****************************************************************************/
    Vec4& operator-=(const Vec4& rhs)
    {
        x -=rhs.x;
        y -=rhs.y;
        z -=rhs.z;
        w -=rhs.w;
        return *this;
    }

    /*!***************************************************************************
    @Function			*
    @Input				rhs a single dimension value
    @Returns			result of multiplication
    @Description		componentwise multiplication of a Vec4 by a single value
    ****************************************************************************/
    Vec4 operator*(const float& rhs) const
    {
        Vec4 out;
        out.x = x*rhs;
        out.y = y*rhs;
        out.z = z*rhs;
        out.w = w*rhs;
        return out;
    }

    /*!***************************************************************************
    @Function			*=
    @Input				rhs a single dimension value
    @Returns			result of multiplication and assignment
    @Description		componentwise multiplication and assignment of a Vec4 by
                        a single value
    ****************************************************************************/
    Vec4& operator*=(const float& rhs)
    {
        x = x*rhs;
        y = y*rhs;
        z = z*rhs;
        w = w*rhs;
        return *this;
    }

    /*!***************************************************************************
    @Function			/
    @Input				rhs a single dimension value
    @Returns			result of division
    @Description		componentwise division of a Vec4 by a single value
    ****************************************************************************/
    Vec4 operator/(const float& rhs) const
    {
        Vec4 out;
        out.x = x/rhs;
        out.y = y/rhs;
        out.z = z/rhs;
        out.w = w/rhs;
        return out;
    }

    /*!***************************************************************************
    @Function			/=
    @Input				rhs a single dimension value
    @Returns			result of division and assignment
    @Description		componentwise division and assignment of a Vec4 by
                        a single value
    ****************************************************************************/
    Vec4& operator/=(const float& rhs)
    {
        x = x/rhs;
        y = y/rhs;
        z = z/rhs;
        w = w/rhs;
        return *this;
    }

    /*!***************************************************************************
    @Function			*
    @Input				lhs a single dimension value
    @Input				rhs a Vec4
    @Returns			result of muliplication
    @Description		componentwise multiplication of a Vec4 by
                        a single value
    ****************************************************************************/
    friend Vec4 operator*(const float lhs, const Vec4&  rhs)
    {
        Vec4 out;
        out.x = lhs*rhs.x;
        out.y = lhs*rhs.y;
        out.z = lhs*rhs.z;
        out.w = lhs*rhs.w;
        return out;
    }

    /*!***************************************************************************
    @Function			lenSqr
    @Returns			square of the magnitude of the vector
    @Description		calculates the square of the magnitude of the vector
    ****************************************************************************/
    float lenSqr() const
    {
        return x*x + y*y + z*z + w*w;
    }

    /*!***************************************************************************
    @Function			length
    @Returns			the magnitude of the vector
    @Description		calculates the magnitude of the vector
    ****************************************************************************/
    float length() const
    {
        return sqrtf(x*x + y*y + z*z + w*w);
    }

    /*!***************************************************************************
    @Function			normalize
    @Returns			normalized vector
    @Description		calculates the normalized value of a Vec4
    ****************************************************************************/
    Vec4 normalize()
    {
        float len = length();
        x = x/len;
        y = y/len;
        z = z/len;
        w = w/len;
        return *this;
    }

    /*!***************************************************************************
    @Function			normalized
    @Returns			normalized vector
    @Description		returns a normalized vector of the same direction as this
                        vector
    ****************************************************************************/
    Vec4 normalized() const
    {
        Vec4 out;
        float len = length();
        out.x = x/len;
        out.y = y/len;
        out.z = z/len;
        out.w = w/len;
        return out;
    }

    /*!***************************************************************************
    @Function			dot
    @Returns			scalar product
    @Description		returns a normalized vector of the same direction as this
                        vector
    ****************************************************************************/
    float dot(const Vec4& rhs)
    {
        return x*rhs.x + y*rhs.y + z*rhs.z + w*rhs.w;
    }

    /*!***************************************************************************
    @Function			ptr
    @Returns			pointer to vector values
    @Description		returns a pointer to memory containing the values of the
                        Vec3
    ****************************************************************************/
    float *ptr() { return (float*)this; }
};


/*!***************************************************************************
 @Function      Vec3Lerp
 @Output        Output vector
 @Input         Input vector 1
 @Input         Input vector 2
 @Input         Input interpolator
 @Description   Linear interpolation of two Vec3s
 ****************************************************************************/
void Vec3Lerp(VECTOR3& vOut, const VECTOR3& v1, const VECTOR3& v2, float s);


/*!***************************************************************************
 @Function      Vec3DotProduct
 @Input         Input vector 1
 @Input         Input vector 2
 @Returns		scalar product
 @Description   Dot product of two Vec3s
 ****************************************************************************/
float Vec3DotProduct(const VECTOR3& v1, const VECTOR3& v2);


/*!***************************************************************************
 @Function      Vec3CrossProduct
 @Output        Output vector
 @Input         Input vector 1
 @Input         Input vector 2
 @Description   Cross product of two Vec3s
 ****************************************************************************/
void Vec3CrossProduct(VECTOR3& vOut, const VECTOR3& v1, const VECTOR3& v2);


/*!***************************************************************************
 @Function      Vec3Normalize
 @Output        Output vector
 @Input         Input vector
 @Description   Normalization of Vec3
 ****************************************************************************/
void Vec3Normalize(VECTOR3& vOut, const VECTOR3& vIn);


/*!***************************************************************************
 @Function      Vec4Normalize
 @Output        Output vector
 @Input         Input vector
 @Description   Normalization of Vec4
 ****************************************************************************/
void Vec4Normalize(VECTOR4& vOut, const VECTOR4& vIn);


/*!***************************************************************************
 @Function      Vec3DotProduct
 @Input         Input vector
 @Returns		length
 @Description   Length of Vec3
 ****************************************************************************/
float Vec3Length(const VECTOR3& vIn);


#endif
