/*
 * OrangeGrass
 * Copyright (C) 2009 Vyacheslav Bogdanov.
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
#ifndef IOGCOREHELPERS_H_
#define IOGCOREHELPERS_H_

#ifdef WIN32
#include <crtdbg.h>
#endif
#include <cstddef>
#include <algorithm>
#include <iostream>
#include <cstddef>
#define _CRT_WARN 0
#include <assert.h>


// result values
#define OG_SUCCESS	    1
#define OG_FAIL		    0


// maximal path length
#define OG_MAX_PATH		2048


// Helpers to safely delete objects and arrays
#define OG_SAFE_DELETE(x)           {if(x){ delete x; x = 0; }}
#define OG_SAFE_DELETE_ARRAY(x)     {if(x){ delete[] x; x = 0; }}


// Min/max
#define OG_MAX(a, b)                (((a) >= (b)) ? (a) : (b))
#define OG_MIN(a, b)                (((a) <= (b)) ? (a) : (b))
#define OG_ABS(a)		            ((a) <= 0 ? -(a) : (a) )
#define OG_RGBA(r, g, b, a)         ((unsigned int) (((a) << 24) | ((b) << 16) | ((g) << 8) | (r)))


// Clamping value to the range
#define OG_CLAMP(a, min, max)       {if ((a) < (min)) { (a) = (min); } else if ((a) > (max)) { (a) = (max); }}


// Logging
#ifdef WIN32
    #define OG_LOG_INFO(STR, ...)		{FILE* pF = fopen("log.txt", "at"); if (pF) { fprintf(pF, "[INFO]: "); fprintf(pF, STR, ## __VA_ARGS__); fprintf(pF, "\n"); fclose(pF); }}
	#define OG_LOG_WARNING(STR, ...)	{FILE* pF = fopen("log.txt", "at"); if (pF) { fprintf(pF, "[WARNING]: "); fprintf(pF, STR, ## __VA_ARGS__); fprintf(pF, "\n"); fclose(pF); }}
	#define OG_LOG_ERROR(STR, ...)		{FILE* pF = fopen("log.txt", "at"); if (pF) { fprintf(pF, "[ERROR]: "); fprintf(pF, STR, ## __VA_ARGS__); fprintf(pF, "\n"); fclose(pF); }}
#else
#ifdef __APPLE__
    #define OG_LOG_INFO(STR, ...)       NSLog(@STR, ##__VA_ARGS__)
	#define OG_LOG_WARNING(STR, ...)    NSLog(@STR, ##__VA_ARGS__)
	#define OG_LOG_ERROR(STR, ...)      NSLog(@STR, ##__VA_ARGS__)
#else
    #include <jni.h>
    #include <android/log.h>
    #define OG_LOG_INFO(STR, ...)       __android_log_print(ANDROID_LOG_INFO, "liborangegrass", STR, ##__VA_ARGS__)
	#define OG_LOG_WARNING(STR, ...)    __android_log_print(ANDROID_LOG_INFO, "liborangegrass", STR, ##__VA_ARGS__)
	#define OG_LOG_ERROR(STR, ...)      __android_log_print(ANDROID_LOG_ERROR, "liborangegrass", STR, ##__VA_ARGS__)
#endif
#endif


// floating point macros
#define PI			        (3.1415926535f)
#define FP_BITS(fp)			(*(unsigned long*)&(fp))
#define FP_ABS_BITS(fp)		(FP_BITS(fp)&0x7FFFFFFF)
#define FP_SIGN_BIT(fp)		(FP_BITS(fp)&0x80000000)
#define FP_ONE_BITS			0x3F800000
#define	FP_SIGN_BIT_SHIFT	31


// radian-degree conversion
#define TO_RADIAN(degree)   ((degree) * (PI / 180.0f))
#define TO_DEGREE(radian)   ((radian) * (180.0f / PI))


// Define a 64-bit type for various platforms
#if defined(__int64) || defined(WIN32)
#define INT64BIT __int64
#else
#define INT64BIT long long int
#endif

#ifndef WIN32
typedef struct _LARGE_INTEGER
{
    union
    {
        struct
        {
            unsigned long LowPart;
            long HighPart;
        };
        INT64BIT QuadPart;
    };
} LARGE_INTEGER, *PLARGE_INTEGER;
#endif


/*!***************************************************************************
 @Function		IsLittleEndian
 @Returns		True if the platform the code is ran on is little endian
 @Description	Returns true if the platform the code is ran on is little endian
 *****************************************************************************/
inline bool IsLittleEndian()
{
	static bool bLittleEndian;
	static bool bIsInit = false;
	
	if(!bIsInit)
	{
		short int word = 0x0001;
		char *byte = (char*) &word;
		bLittleEndian = byte[0] ? true : false;
		bIsInit = true;
	}
	
	return bLittleEndian;
}


#ifndef _ASSERT
#define _ASSERT(X) //
#endif


template <typename T>
T *reallocEM(T *array, size_t old_size, size_t new_size)
{
    T *temp = new T[new_size];
    delete [] array;
    return std::copy(array, array + old_size, temp);
}


template <typename T>
bool SafeAlloc(T* &ptr, size_t cnt)
{
    _ASSERT(!ptr);
    if(cnt)
    {
        ptr = new T[cnt * sizeof(T)];
        _ASSERT(ptr);
        if(!ptr)
            return false;
    }
    memset(ptr, 0, cnt *sizeof(T));
    return true;
}


template <typename T>
void SafeRealloc(T* &ptr, size_t cnt)
{
    T *temp = new T[cnt * sizeof(T)];
    size_t old_size = sizeof(*ptr);
    delete [] ptr;
    std::copy(ptr, ptr + old_size, temp);
    _ASSERT(ptr);
}


#endif
