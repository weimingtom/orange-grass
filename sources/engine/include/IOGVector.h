/*****************************************************************************
 *  IOGVector.h
 *  OrangeGrass
 *
 *  Copyright 2009-2012 Viacheslav Bogdanov. All rights reserved.
 *
 ****************************************************************************/
#ifndef OGVECTOR_H_
#define OGVECTOR_H_

#ifdef __APPLE__
#include <OpenGLES/ES2/gl.h>
#endif
#include <math.h>


/*!***************************************************************************
 ** OGVec2 2 component vector
 *****************************************************************************/
struct OGVec2
{
    float x;	/*!< x coordinate */
    float y;	/*!< y coordinate */

    /*!***************************************************************************
 	 @Function			OGVec2
	 @Description		Blank constructor.
	 *****************************************************************************/
    OGVec2() {x = y = 0;}

    /*!***************************************************************************
     @Function			OGVec2
     @Input				fX	X component of vector
     @Input				fY	Y component of vector
     @Description		Simple constructor from 2 values.
     *****************************************************************************/
	OGVec2(float fX, float fY) { x = fX; y = fY; }
	
    /*!***************************************************************************
 	 @Function			OGVec2
 	 @Input				fValue	a component value
	 @Description		Constructor from a single value.
	 *****************************************************************************/
	OGVec2(float fValue) { x = fValue; y = fValue; }
	
    /*!***************************************************************************
	 @Function			OGVec2
	 @Input				pVec	an array
	 @Description		Constructor from an array
	 *****************************************************************************/
	OGVec2(const float* pVec) { x = pVec[0]; y = pVec[1]; }
	
	/*!***************************************************************************
     @Function			+
     @Input				rhs another OGVec2
     @Returns			result of addition
     @Description		componentwise addition operator for two Vec2s
     *****************************************************************************/
	OGVec2 operator+(const OGVec2& rhs) const
	{
		OGVec2 out(*this);
		return out += rhs;
	}

    /*!***************************************************************************
     @Function			-
     @Input				rhs another OGVec2
     @Returns			result of subtraction
     @Description		componentwise subtraction operator for two Vec2s
     ****************************************************************************/
    OGVec2 operator-(const OGVec2& rhs) const
    {
        OGVec2 out(*this);
        return out -= rhs;
    }

    /*!***************************************************************************
     @Function			+=
     @Input				rhs another OGVec2
     @Returns			result of addition
     @Description		componentwise addition and assignment operator for two Vec2s
     ****************************************************************************/
    OGVec2& operator+=(const OGVec2& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    /*!***************************************************************************
     @Function			-=
     @Input				rhs another OGVec2
     @Returns			result of subtraction
     @Description		componentwise subtraction and assignment operator for two Vec2s
     ****************************************************************************/
    OGVec2& operator-=(const OGVec2& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    /*!***************************************************************************
     @Function			-
     @Input				rhs another OGVec2
     @Returns			result of negation
     @Description		negation operator for a OGVec2
     ****************************************************************************/
    friend OGVec2 operator- (const OGVec2& rhs) { return OGVec2(-rhs.x, -rhs.y); }

    /*!***************************************************************************
     @Function			*
     @Input				lhs scalar
     @Input				rhs a OGVec2
     @Returns			result of negation
     @Description		negation operator for a OGVec2
     ****************************************************************************/
    friend OGVec2 operator*(const float lhs, const OGVec2&  rhs)
    {
        OGVec2 out(lhs);
        return out *= rhs;
    }

    /*!***************************************************************************
     @Function			/
     @Input				lhs scalar
     @Input				rhs a OGVec2
     @Returns			result of division
     @Description		division operator for scalar and OGVec2
     ****************************************************************************/
    friend OGVec2 operator/(const float lhs, const OGVec2&  rhs)
    {
        OGVec2 out(lhs);
        return out /= rhs;
    }

    /*!***************************************************************************
     @Function			*
     @Input				rhs a scalar
     @Returns			result of multiplication
     @Description		componentwise multiplication by scalar for OGVec2
     ****************************************************************************/
    OGVec2 operator*(const float& rhs) const
    {
        OGVec2 out(*this);
        return out *= rhs;
    }

    /*!***************************************************************************
     @Function			*=
     @Input				rhs a scalar
     @Returns			result of multiplication and assignment
     @Description		componentwise multiplication and assignment by scalar for OGVec2
     ****************************************************************************/
    OGVec2& operator*=(const float& rhs)
    {
        x = x * rhs;
        y = y * rhs;
        return *this;
    }

    /*!***************************************************************************
     @Function			*=
     @Input				rhs a OGVec2
     @Returns			result of multiplication and assignment
     @Description		componentwise multiplication and assignment by OGVec2 for OGVec2
     ****************************************************************************/
    OGVec2& operator*=(const OGVec2& rhs)
    {
        x = x * rhs.x;
        y = y * rhs.y;
        return *this;
    }

    /*!***************************************************************************
     @Function			/
     @Input				rhs a scalar
     @Returns			result of division
     @Description		componentwise division by scalar for OGVec2
     ****************************************************************************/
    OGVec2 operator/(const float& rhs) const
    {
        OGVec2 out(*this);
        return out /= rhs;
    }

    /*!***************************************************************************
     @Function			/=
     @Input				rhs a scalar
     @Returns			result of division and assignment
     @Description		componentwise division and assignment by scalar for OGVec2
     ****************************************************************************/
    OGVec2& operator/=(const float& rhs)
    {
        x = x / rhs;
        y = y / rhs;
        return *this;
    }

    /*!***************************************************************************
     @Function			/=
     @Input				rhs a OGVec2
     @Returns			result of division and assignment
     @Description		componentwise division and assignment by OGVec2 for OGVec2
     ****************************************************************************/
    OGVec2& operator/=(const OGVec2& rhs)
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
    OGVec2 normalize()
    {
        return *this /= length();
    }

    /*!***************************************************************************
     @Function			normalized
     @Returns			returns the normalized value of the vector
     @Description		returns a normalized vector of the same direction as this
                        vector
     ****************************************************************************/
    OGVec2 normalized() const
    {
        OGVec2 out(*this);
        return out.normalize();
    }

    /*!***************************************************************************
     @Function			rotated90
     @Returns			returns the vector rotated 90ﾰ
     @Description		returns the vector rotated 90ﾰ
     ****************************************************************************/
    OGVec2 rotated90() const
    {
        return OGVec2(-y, x);
    }

    /*!***************************************************************************
     @Function			dot
     @Input				rhs a single value
     @Returns			scalar product
     @Description		calculate the scalar product of two Vec3s
     ****************************************************************************/
    float dot(const OGVec2& rhs)
    {
        return x * rhs.x + y * rhs.y;
    }

    /*!***************************************************************************
     @Function			ptr
     @Returns			pointer
     @Description		returns a pointer to memory containing the values of the
                        OGVec3
     ****************************************************************************/
    float *ptr() { return (float*)this; }
};


/*!***************************************************************************
 ** OGVec3 3 component vector
 ****************************************************************************/
struct OGVec3
{
    float x;	/*!< x coordinate */
    float y;	/*!< y coordinate */
    float z;	/*!< z coordinate */

    /*!***************************************************************************
    @Function			OGVec3
    @Description		Blank constructor.
    *****************************************************************************/
    OGVec3() { x = y = z = 0; }

    /*!***************************************************************************
    @Function			OGVec3
    @Input				fX	X component of vector
    @Input				fY	Y component of vector
    @Input				fZ	Z component of vector
    @Description		Simple constructor from 3 values.
    *****************************************************************************/
    OGVec3(float fX, float fY, float fZ)
    {
        x = fX;	y = fY;	z = fZ;
    }

    /*!***************************************************************************
    @Function			OGVec3
    @Input				fValue	a component value
    @Description		Constructor from a single value.
    *****************************************************************************/
    OGVec3(const float fValue)
    {
        x = fValue; y = fValue; z = fValue;
    }

    /*!***************************************************************************
    @Function			OGVec3
    @Input				pVec	an array
    @Description		Constructor from an array
    *****************************************************************************/
    OGVec3(const float* pVec)
    {
        x = (*pVec++); y = (*pVec++); z = *pVec;
    }

    /*!***************************************************************************
    @Function			+
    @Input				rhs another OGVec3
    @Returns			result of addition
    @Description		componentwise addition operator for two VECTOR3s
    *****************************************************************************/
	OGVec3 operator+(const OGVec3& rhs) const
	{
		OGVec3 out;
		out.x = x+rhs.x;
		out.y = y+rhs.y;
		out.z = z+rhs.z;
		return out;
	}

    /*!***************************************************************************
    @Function			-
    @Input				rhs another OGVec3
    @Returns			result of subtraction
    @Description		componentwise subtraction operator for two VECTOR3s
    ****************************************************************************/
    OGVec3 operator-(const OGVec3& rhs) const
    {
        OGVec3 out;
        out.x = x-rhs.x;
        out.y = y-rhs.y;
        out.z = z-rhs.z;
        return out;
    }

    /*!***************************************************************************
    @Function			+=
    @Input				rhs another OGVec3
    @Returns			result of addition
    @Description		componentwise addition and assignement operator for two 
                        VECTOR3s
    ****************************************************************************/
    OGVec3& operator+=(const OGVec3& rhs)
    {
        x +=rhs.x;
        y +=rhs.y;
        z +=rhs.z;
        return *this;
    }

    /*!***************************************************************************
    @Function			-=
    @Input				rhs another OGVec3
    @Returns			result of subtraction
    @Description		componentwise subtraction and assignement operator for two 
                        VECTOR3s
    ****************************************************************************/
    OGVec3& operator-=(const OGVec3& rhs)
    {
        x -=rhs.x;
        y -=rhs.y;
        z -=rhs.z;
        return *this;
    }

    /*!***************************************************************************
    @Function			-
    @Input				rhs another OGVec3
    @Returns			result of negation
    @Description		negation operator for a OGVec3
    ****************************************************************************/
    friend OGVec3 operator - (const OGVec3& rhs) { return OGVec3(rhs) *= -1; }

    /*!***************************************************************************
    @Function			*
    @Input				lhs single value
    @Input				rhs a OGVec3
    @Returns			result of negation
    @Description		negation operator for a OGVec3
    ****************************************************************************/
    friend OGVec3 operator*(const float lhs, const OGVec3&  rhs)
    {
        OGVec3 out;
        out.x = lhs * rhs.x;
        out.y = lhs * rhs.y;
        out.z = lhs * rhs.z;
        return out;
    }

    /*!***************************************************************************
    @Function			*
    @Input				lhs single value
    @Input				rhs a OGVec3
    @Returns			result of negation
    @Description		negation operator for a OGVec3
    ****************************************************************************/
    friend OGVec3 operator/(const float lhs, const OGVec3&  rhs)
    {
        OGVec3 out;
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
                        OGVec3
    ****************************************************************************/
    OGVec3 operator*(const float& rhs) const
    {
        OGVec3 out;
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
                        dimension value	for OGVec3
    ****************************************************************************/
    OGVec3& operator*=(const float& rhs)
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
                        dimension value	for OGVec3
    ****************************************************************************/
    OGVec3 operator/(const float& rhs) const
    {
        OGVec3 out;
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
                        dimension value	for OGVec3
    ****************************************************************************/
    OGVec3& operator/=(const float& rhs)
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
    bool operator==(const OGVec3& rhs)
    {
        return (x==rhs.x && y==rhs.y && z==rhs.z);
    }

    /*!***************************************************************************
    @Function			!=
    @Input				rhs a vector
    @Returns			result of comparison
    @Description		componentwise comparison
    ****************************************************************************/
    bool operator!=(const OGVec3& rhs)
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
    OGVec3 normalize()
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
    OGVec3 normalized() const
    {
        OGVec3 out;
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
    float dot(const OGVec3& rhs) const
    {
        return x*rhs.x + y*rhs.y + z*rhs.z;
    }

    /*!***************************************************************************
    @Function			dot
    @Returns			scalar product
    @Description		calculate the scalar product of two VECTOR3s
    ****************************************************************************/
    OGVec3 cross(const OGVec3& rhs) const
    {
        OGVec3 out;
        out.x = y*rhs.z - z*rhs.y;
        out.y = z*rhs.x - x*rhs.z;
        out.z = x*rhs.y - y*rhs.x;
        return out;
    }

    /*!***************************************************************************
    @Function			ptr
    @Returns			pointer
    @Description		returns a pointer to memory containing the values of the
                        OGVec3
    ****************************************************************************/
    float *ptr() { return (float*)this; }
};


/*!***************************************************************************
** OGVec4 4 component vector
*****************************************************************************/
struct OGVec4
{
    float x;	/*!< x coordinate */
    float y;	/*!< y coordinate */
    float z;	/*!< z coordinate */
    float w;	/*!< w coordinate */

    /*!***************************************************************************
    @Function			OGVec4
    @Description		Blank constructor.
    *****************************************************************************/
    OGVec4(){x = y = z = w = 0;}

    /*!***************************************************************************
    @Function			OGVec3
    @Description		Blank constructor.
    *****************************************************************************/
    OGVec4(const float vec)
    {
        x = vec; y = vec; z = vec; w = vec;
    }

    /*!***************************************************************************
    @Function			multiple value constructor
    @Input				fX value of x component
    @Input				fY value of y component
    @Input				fZ value of z component
    @Input				fW value of w component
    @Description		Constructs a OGVec4 from 4 separate values
    ****************************************************************************/
    OGVec4(float fX, float fY, float fZ, float fW)
    {
        x = fX;	y = fY;	z = fZ;	w = fW;
    }

    /*!***************************************************************************
    @Function			constructor from OGVec3
    @Input				vec3 a OGVec3
    @Input				fW value of w component
    @Description		Constructs a OGVec4 from a vec3 and a w component
    ****************************************************************************/
    OGVec4(const OGVec3& vec3, float fW)
    {
        x = vec3.x;	y = vec3.y;	z = vec3.z;	w = fW;
    }

    /*!***************************************************************************
    @Function			constructor from OGVec3
    @Input				fX value of x component
    @Input				vec3 a OGVec3
    @Description		Constructs a vec4 from a vec3 and a w component
    ****************************************************************************/
    OGVec4(float fX, const OGVec3& vec3)
    {
        x = fX;	y = vec3.x;	z = vec3.y;	w = vec3.z;
    }

    /*!***************************************************************************
    @Function			constructor from array
    @Input				pVec a pointer to an array of four values
    @Description		Constructs a OGVec4 from a pointer to an array of four values
    ****************************************************************************/
    OGVec4(const float* pVec)
    {
        x = (*pVec++); y = (*pVec++); z= (*pVec++); w = *pVec;
    }

    /*!***************************************************************************
    @Function			+
    @Input				rhs another OGVec4
    @Returns			result of addition
    @Description		Addition operator for OGVec4
    ****************************************************************************/
    OGVec4 operator+(const OGVec4& rhs) const
    {
        OGVec4 out;
        out.x = x+rhs.x;
        out.y = y+rhs.y;
        out.z = z+rhs.z;
        out.w = w+rhs.w;
        return out;
    }

    /*!***************************************************************************
    @Function			-
    @Input				rhs another OGVec4
    @Returns			result of subtraction
    @Description		Subtraction operator for OGVec4
    ****************************************************************************/
    OGVec4 operator-(const OGVec4& rhs) const
    {
        OGVec4 out;
        out.x = x-rhs.x;
        out.y = y-rhs.y;
        out.z = z-rhs.z;
        out.w = w-rhs.w;
        return out;
    }

    /*!***************************************************************************
    @Function			+=
    @Input				rhs another OGVec4
    @Returns			result of addition and assignment
    @Description		Addition and assignment operator for OGVec4
    ****************************************************************************/
    OGVec4& operator+=(const OGVec4& rhs)
    {
        x +=rhs.x;
        y +=rhs.y;
        z +=rhs.z;
        w +=rhs.w;
        return *this;
    }

    /*!***************************************************************************
    @Function			-=
    @Input				rhs another OGVec4
    @Returns			result of subtraction and assignment
    @Description		Subtraction and assignment operator for OGVec4
    ****************************************************************************/
    OGVec4& operator-=(const OGVec4& rhs)
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
    @Description		componentwise multiplication of a OGVec4 by a single value
    ****************************************************************************/
    OGVec4 operator*(const float& rhs) const
    {
        OGVec4 out;
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
    @Description		componentwise multiplication and assignment of a OGVec4 by
                        a single value
    ****************************************************************************/
    OGVec4& operator*=(const float& rhs)
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
    @Description		componentwise division of a OGVec4 by a single value
    ****************************************************************************/
    OGVec4 operator/(const float& rhs) const
    {
        OGVec4 out;
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
    @Description		componentwise division and assignment of a OGVec4 by
                        a single value
    ****************************************************************************/
    OGVec4& operator/=(const float& rhs)
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
    @Input				rhs a OGVec4
    @Returns			result of muliplication
    @Description		componentwise multiplication of a OGVec4 by
                        a single value
    ****************************************************************************/
    friend OGVec4 operator*(const float lhs, const OGVec4&  rhs)
    {
        OGVec4 out;
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
    @Description		calculates the normalized value of a OGVec4
    ****************************************************************************/
    OGVec4 normalize()
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
    OGVec4 normalized() const
    {
        OGVec4 out;
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
    float dot(const OGVec4& rhs)
    {
        return x*rhs.x + y*rhs.y + z*rhs.z + w*rhs.w;
    }

    /*!***************************************************************************
    @Function			ptr
    @Returns			pointer to vector values
    @Description		returns a pointer to memory containing the values of the
                        OGVec3
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
void Vec3Lerp(OGVec3& vOut, const OGVec3& v1, const OGVec3& v2, float s);


/*!***************************************************************************
 @Function      Vec3DotProduct
 @Input         Input vector 1
 @Input         Input vector 2
 @Returns		scalar product
 @Description   Dot product of two Vec3s
 ****************************************************************************/
float Vec3DotProduct(const OGVec3& v1, const OGVec3& v2);


/*!***************************************************************************
 @Function      Vec3CrossProduct
 @Output        Output vector
 @Input         Input vector 1
 @Input         Input vector 2
 @Description   Cross product of two Vec3s
 ****************************************************************************/
void Vec3CrossProduct(OGVec3& vOut, const OGVec3& v1, const OGVec3& v2);


/*!***************************************************************************
 @Function      Vec3Normalize
 @Output        Output vector
 @Input         Input vector
 @Description   Normalization of OGVec3
 ****************************************************************************/
void Vec3Normalize(OGVec3& vOut, const OGVec3& vIn);


/*!***************************************************************************
 @Function      Vec4Normalize
 @Output        Output vector
 @Input         Input vector
 @Description   Normalization of OGVec4
 ****************************************************************************/
void Vec4Normalize(OGVec4& vOut, const OGVec4& vIn);


/*!***************************************************************************
 @Function      Vec3DotProduct
 @Input         Input vector
 @Returns		length
 @Description   Length of OGVec3
 ****************************************************************************/
float Vec3Length(const OGVec3& vIn);


#endif
