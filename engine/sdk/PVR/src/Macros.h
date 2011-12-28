/*****************************************************************************
 *  Macros.h
 *  OrangeGrass
 *
 *  Copyright 2009-2012 Viacheslav Bogdanov. All rights reserved.
 *
 ****************************************************************************/
#ifndef MACROS_H_
#define MACROS_H_

#ifdef WIN32
#include <crtdbg.h>
#endif


#define PI			(3.1415926535f)
#define PIOVERTWO	(PI / 2.0f)
#define TWOPI		(PI * 2.0f)
#define ONE		    (1.0f)

#define OG_SUCCESS	1
#define OG_FAIL		0

#define _MIN(X,Y)               (((X)<(Y))? (X):(Y))
#define _MAX(X,Y)               (((X)>(Y))? (X):(Y))
#define _ABS(a)		            ((a) <= 0 ? -(a) : (a) )
#define CLAMP(X, lower, upper)  (_MIN(_MAX((X),(lower)), (upper)))
#define RGBA(r, g, b, a)        ((GLuint) (((a) << 24) | ((b) << 16) | ((g) << 8) | (r)))


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


/****************************************************************************
** Defines
****************************************************************************/

#define _CRT_WARN 0
#include <assert.h>

#ifndef _RPT0
#define _RPT0(a,b) printf(b)
#endif

#ifndef _RPT1
#define _RPT1(a,b,c) printf(b, c)
#endif

#ifndef _RPT2
#define _RPT2(a,b,c,d) printf(b,c,d)
#endif

#ifndef _RPT3
#define _RPT3(a,b,c,d,e) printf(b,c,d,e)
#endif

#ifndef _RPT4
#define _RPT4(a,b,c,d,e,f) printf(b,c,d,f)
#endif

#ifndef _ASSERT
#define _ASSERT(X) //
#endif

#endif
