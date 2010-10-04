/*
 *  IOGGrUtility.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGGRUTILITY_H_
#define OGGRUTILITY_H_
#include <stdlib.h>
#include <memory.h>


/*
* Transform a point (column vector) by a 4x4 matrix.  I.e.  out = m * in
* Input:  m - the 4x4 matrix
*         in - the 4x1 vector
* Output:  out - the resulting 4x1 vector.
*/
void transform_point(float out[4], const float m[16], const float in[4]);

/*
* Perform a 4x4 matrix multiplication  (product = a x b).
* Input:  a, b - matrices to multiply
* Output:  product - product of a and b
*/
void matmul(float * product, const float * a, const float * b);


/*
* Compute inverse of 4x4 transformation matrix.
* Code contributed by Jacques Leroy jle@star.be
* Return true for success, false for failure (singular matrix)
*/
bool invert_matrix(const float * m, float * out);


/* Project point in world coords (objx,objy,obz) to screen coords. (winx,winy,winz) */
bool Project(float objx, float objy, float objz,
			 const float model[16], const float proj[16],
			 const int viewport[4],
			 float * winx, float * winy, float * winz);


/* Transform point from screen coords. (winx,winy,winz) to world coords. */
bool UnProject(float winx, float winy, float winz,
			   const float model[16], const float proj[16],
			   const int viewport[4],
			   float * objx, float * objy, float * objz);

/* Transform point from screen coords. (winx,winy,winz) to world coords. */
bool UnProject(float winx, float winy, float winz,
			   const float model[16], const float proj[16],
			   int ViewWidth, int ViewHeight,
			   float * objx, float * objy, float * objz);

#endif