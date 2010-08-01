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


// Helpers to safely delete objects and arrays
#define OG_SAFE_DELETE(x)       {if(x){ delete x; x = 0; }}
#define OG_SAFE_DELETE_ARRAY(x) {if(x){ delete[] x; x = 0; }}


// Min/max
#define OG_MAX(a, b)            (((a) >= (b)) ? (a) : (b))
#define OG_MIN(a, b)            (((a) <= (b)) ? (a) : (b))


// Clamping value to the range
#define OG_CLAMP(a, min, max)   {if ((a) < (min)) { (a) = (min); } else if ((a) > (max)) { (a) = (max); }}


#endif