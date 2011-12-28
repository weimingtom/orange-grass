/*
 *  IOGCoreHelpers.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
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
#define OG_CLAMP(a, min, max)   {if ((a) < (min)) { (a) = (min); } else if ((a) > (max)) { (a) = (max); }}


// Logging
#ifdef WIN32
	#define OG_LOG_INFO(STR, ...)		{FILE* pF = fopen("log.txt", "at"); if (pF) { fprintf(pF, "[INFO]: "); fprintf(pF, STR, ## __VA_ARGS__); fprintf(pF, "\n"); fclose(pF); }}
	#define OG_LOG_WARNING(STR, ...)	{FILE* pF = fopen("log.txt", "at"); if (pF) { fprintf(pF, "[WARNING]: "); fprintf(pF, STR, ## __VA_ARGS__); fprintf(pF, "\n"); fclose(pF); }}
	#define OG_LOG_ERROR(STR, ...)		{FILE* pF = fopen("log.txt", "at"); if (pF) { fprintf(pF, "[ERROR]: "); fprintf(pF, STR, ## __VA_ARGS__); fprintf(pF, "\n"); fclose(pF); }}
#else
	#define OG_LOG_INFO(STR, ...)
	#define OG_LOG_WARNING(STR, ...)
	#define OG_LOG_ERROR(STR, ...)
#endif


#define PI			(3.1415926535f)
#define PIOVERTWO	(PI / 2.0f)
#define TWOPI		(PI * 2.0f)
#define ONE		    (1.0f)

#define OG_SUCCESS	1
#define OG_FAIL		0


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


#define _CRT_WARN 0
#include <assert.h>

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
