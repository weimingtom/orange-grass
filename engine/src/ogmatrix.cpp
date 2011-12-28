/*****************************************************************************
 *  Matrix.h
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
#include "IOGMatrix.h"


#ifdef __APPLE__
#include <TargetConditionals.h>
#if (TARGET_IPHONE_SIMULATOR == 0) && (TARGET_OS_IPHONE == 1)
#include "neonmath/neon_matrix_impl.h"
#endif
#endif


static const OGMatrix	c_mIdentity = {
	{
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
	}
};


/*!***************************************************************************
 @Function      MatrixIdentity
 @Output        mOut resulting matrix
 @Description   Reset matrix to identity
 ****************************************************************************/
void MatrixIdentity(OGMatrix &mOut)
{
	mOut.f[ 0]=1.0f;	mOut.f[ 4]=0.0f;	mOut.f[ 8]=0.0f;	mOut.f[12]=0.0f;
	mOut.f[ 1]=0.0f;	mOut.f[ 5]=1.0f;	mOut.f[ 9]=0.0f;	mOut.f[13]=0.0f;
	mOut.f[ 2]=0.0f;	mOut.f[ 6]=0.0f;	mOut.f[10]=1.0f;	mOut.f[14]=0.0f;
	mOut.f[ 3]=0.0f;	mOut.f[ 7]=0.0f;	mOut.f[11]=0.0f;	mOut.f[15]=1.0f;
}


/*!***************************************************************************
 @Function      MatrixGetOrg
 @Output        vOut vector
 @Input         mIn matrix
 @Description   Returns the zero-point
 ****************************************************************************/
void MatrixGetOrg(OGVec3& vOut, const OGMatrix& mIn)
{
    vOut.x = mIn.f[12];
    vOut.y = mIn.f[13];
    vOut.z = mIn.f[14];
}


/*!***************************************************************************
 @Function      MatrixGetBasis
 @Input         basis X axis
 @Input         basis Y axis
 @Input         basis Z axis
 @Input         mIn matrix
 @Description   Returns the basis vectors
 ****************************************************************************/
void MatrixGetBasis(
    OGVec3& vOutX, 
    OGVec3& vOutY, 
    OGVec3& vOutZ, 
    const OGMatrix& mIn)
{
    vOutX.x = mIn.f[_11];
    vOutX.y = mIn.f[_21];
    vOutX.z = mIn.f[_31];
    
    vOutY.x = mIn.f[_12];
    vOutY.y = mIn.f[_22];
    vOutY.z = mIn.f[_32];
    
    vOutZ.x = mIn.f[_13];
    vOutZ.y = mIn.f[_23];
    vOutZ.z = mIn.f[_33];
}


/*!***************************************************************************
 @Function      MatrixMultiply
 @Output        mOut resulting matrix
 @Input         Matrix A
 @Input         Matrix B
 @Description   Multiply mA by mB and assign the result to matrix (mA * mB). 
 ****************************************************************************/
void MatrixMultiply(OGMatrix& mOut, const OGMatrix& mA, const OGMatrix& mB)
{
#if (TARGET_IPHONE_SIMULATOR == 0) && (TARGET_OS_IPHONE == 1)
    NEON_Matrix4Mul( mA.f, mB.f, mOut.f );
#else	
	OGMatrix mRet;

	// Perform calculation on a dummy matrix (mRet)
	mRet.f[ 0] = mA.f[ 0]*mB.f[ 0] + mA.f[ 1]*mB.f[ 4] + mA.f[ 2]*mB.f[ 8] + mA.f[ 3]*mB.f[12];
	mRet.f[ 1] = mA.f[ 0]*mB.f[ 1] + mA.f[ 1]*mB.f[ 5] + mA.f[ 2]*mB.f[ 9] + mA.f[ 3]*mB.f[13];
	mRet.f[ 2] = mA.f[ 0]*mB.f[ 2] + mA.f[ 1]*mB.f[ 6] + mA.f[ 2]*mB.f[10] + mA.f[ 3]*mB.f[14];
	mRet.f[ 3] = mA.f[ 0]*mB.f[ 3] + mA.f[ 1]*mB.f[ 7] + mA.f[ 2]*mB.f[11] + mA.f[ 3]*mB.f[15];

	mRet.f[ 4] = mA.f[ 4]*mB.f[ 0] + mA.f[ 5]*mB.f[ 4] + mA.f[ 6]*mB.f[ 8] + mA.f[ 7]*mB.f[12];
	mRet.f[ 5] = mA.f[ 4]*mB.f[ 1] + mA.f[ 5]*mB.f[ 5] + mA.f[ 6]*mB.f[ 9] + mA.f[ 7]*mB.f[13];
	mRet.f[ 6] = mA.f[ 4]*mB.f[ 2] + mA.f[ 5]*mB.f[ 6] + mA.f[ 6]*mB.f[10] + mA.f[ 7]*mB.f[14];
	mRet.f[ 7] = mA.f[ 4]*mB.f[ 3] + mA.f[ 5]*mB.f[ 7] + mA.f[ 6]*mB.f[11] + mA.f[ 7]*mB.f[15];

	mRet.f[ 8] = mA.f[ 8]*mB.f[ 0] + mA.f[ 9]*mB.f[ 4] + mA.f[10]*mB.f[ 8] + mA.f[11]*mB.f[12];
	mRet.f[ 9] = mA.f[ 8]*mB.f[ 1] + mA.f[ 9]*mB.f[ 5] + mA.f[10]*mB.f[ 9] + mA.f[11]*mB.f[13];
	mRet.f[10] = mA.f[ 8]*mB.f[ 2] + mA.f[ 9]*mB.f[ 6] + mA.f[10]*mB.f[10] + mA.f[11]*mB.f[14];
	mRet.f[11] = mA.f[ 8]*mB.f[ 3] + mA.f[ 9]*mB.f[ 7] + mA.f[10]*mB.f[11] + mA.f[11]*mB.f[15];

	mRet.f[12] = mA.f[12]*mB.f[ 0] + mA.f[13]*mB.f[ 4] + mA.f[14]*mB.f[ 8] + mA.f[15]*mB.f[12];
	mRet.f[13] = mA.f[12]*mB.f[ 1] + mA.f[13]*mB.f[ 5] + mA.f[14]*mB.f[ 9] + mA.f[15]*mB.f[13];
	mRet.f[14] = mA.f[12]*mB.f[ 2] + mA.f[13]*mB.f[ 6] + mA.f[14]*mB.f[10] + mA.f[15]*mB.f[14];
	mRet.f[15] = mA.f[12]*mB.f[ 3] + mA.f[13]*mB.f[ 7] + mA.f[14]*mB.f[11] + mA.f[15]*mB.f[15];

	// Copy result in pResultMatrix
	mOut = mRet;
#endif
}


/*!***************************************************************************
 @Function      MatrixVec4Multiply
 @Output        vOut resulting vector
 @Input         Input vector
 @Input         Input matrix
 @Description   Multiply vector vIn by matrix. 
 ****************************************************************************/
void MatrixVec4Multiply(OGVec4& vOut, const OGVec4& vIn, const OGMatrix& mIn)
{
#if (TARGET_IPHONE_SIMULATOR == 0) && (TARGET_OS_IPHONE == 1)
	NEON_Matrix4Vector4Mul( mIn.f, &vIn.x, &vOut.x );
#else
	OGVec4 result;
	
	/* Perform calculation on a dummy VECTOR (result) */
	result.x = mIn.f[_11] * vIn.x + mIn.f[_21] * vIn.y + mIn.f[_31] * vIn.z + mIn.f[_41] * vIn.w;
	result.y = mIn.f[_12] * vIn.x + mIn.f[_22] * vIn.y + mIn.f[_32] * vIn.z + mIn.f[_42] * vIn.w;
	result.z = mIn.f[_13] * vIn.x + mIn.f[_23] * vIn.y + mIn.f[_33] * vIn.z + mIn.f[_43] * vIn.w;
	result.w = mIn.f[_14] * vIn.x + mIn.f[_24] * vIn.y + mIn.f[_34] * vIn.z + mIn.f[_44] * vIn.w;
	
	vOut = result;
#endif
}


/*!***************************************************************************
 @Function      MatrixVecMultiply
 @Output        Output vector
 @Input         Input vector
 @Input         Input matrix
 @Description   Transform point represented using the matrix. 
 ****************************************************************************/
void MatrixVecMultiply(OGVec3& vOut, const OGVec3& vIn, const OGMatrix& mIn)
{
	vOut.x = mIn.f[_11] * vIn.x + mIn.f[_21] * vIn.y + mIn.f[_31] * vIn.z + mIn.f[_41];
	vOut.y = mIn.f[_12] * vIn.x + mIn.f[_22] * vIn.y + mIn.f[_32] * vIn.z + mIn.f[_42];
	vOut.z = mIn.f[_13] * vIn.x + mIn.f[_23] * vIn.y + mIn.f[_33] * vIn.z + mIn.f[_43];
}


/*!***************************************************************************
 @Function      MatrixVec3Multiply
 @Output        Output vector
 @Input         Input vector
 @Input         Input matrix
 @Description   Transform vector vIn using the matrix. 
 ****************************************************************************/
void MatrixVec3Multiply(OGVec3& vOut, const OGVec3& vIn, const OGMatrix& mIn)
{
    OGVec3 result;

    /* Perform calculation on a dummy VECTOR (result) */
    result.x = mIn.f[_11] * vIn.x + mIn.f[_21] * vIn.y + mIn.f[_31] * vIn.z;
    result.y = mIn.f[_12] * vIn.x + mIn.f[_22] * vIn.y + mIn.f[_32] * vIn.z;
    result.z = mIn.f[_13] * vIn.x + mIn.f[_23] * vIn.y + mIn.f[_33] * vIn.z;

    vOut = result;
}


/*!***************************************************************************
 @Function      MatrixTranslation
 @Output        Output matrix
 @Input         Input vector X
 @Input         Input vector Y
 @Input         Input vector Z
 @Description   Build a translation matrix mOut using fX, fY and fZ. 
 ****************************************************************************/
void MatrixTranslation(OGMatrix& mOut, float fX, float fY, float fZ)
{
	mOut.f[ 0]=1.0f;	mOut.f[ 4]=0.0f;	mOut.f[ 8]=0.0f;	mOut.f[12]=fX;
	mOut.f[ 1]=0.0f;	mOut.f[ 5]=1.0f;	mOut.f[ 9]=0.0f;	mOut.f[13]=fY;
	mOut.f[ 2]=0.0f;	mOut.f[ 6]=0.0f;	mOut.f[10]=1.0f;	mOut.f[14]=fZ;
	mOut.f[ 3]=0.0f;	mOut.f[ 7]=0.0f;	mOut.f[11]=0.0f;	mOut.f[15]=1.0f;
}


/*!***************************************************************************
 @Function      MatrixScaling
 @Output        Output matrix
 @Input         Input vector X
 @Input         Input vector Y
 @Input         Input vector Z
 @Description   Build a scale matrix mOut using fX, fY and fZ.
 ****************************************************************************/
void MatrixScaling(OGMatrix& mOut, float fX, float fY, float fZ)
{
	mOut.f[ 0]=fX;		mOut.f[ 4]=0.0f;	mOut.f[ 8]=0.0f;	mOut.f[12]=0.0f;
	mOut.f[ 1]=0.0f;	mOut.f[ 5]=fY;		mOut.f[ 9]=0.0f;	mOut.f[13]=0.0f;
	mOut.f[ 2]=0.0f;	mOut.f[ 6]=0.0f;	mOut.f[10]=fZ;		mOut.f[14]=0.0f;
	mOut.f[ 3]=0.0f;	mOut.f[ 7]=0.0f;	mOut.f[11]=0.0f;	mOut.f[15]=1.0f;
}


/*!***************************************************************************
 @Function      MatrixRotationAxis
 @Output        Output matrix
 @Input         Input angle
 @Input         Input vector X
 @Input         Input vector Y
 @Input         Input vector Z
 @Description   Create an around-axis rotation matrix mOut.
 ****************************************************************************/
void MatrixRotationAxis(OGMatrix& mOut, float fAngle, float fX, float fY, float fZ)
{
	OGVec3 axis(fX, fY, fZ);
	axis.normalize();
	float s = (float)sin(fAngle);
	float c = (float)cos(fAngle);
	float x, y, z;
	
	x = axis.x;
	y = axis.y;
	z = axis.z;
	
	mOut.f[ 0] = x * x * (1 - c) + c;
	mOut.f[ 4] = x * y * (1 - c) - (z * s);
	mOut.f[ 8] = x * z * (1 - c) + (y * s);
	mOut.f[12] = 0;
	
	mOut.f[ 1] = y * x * (1 - c) + (z * s);
	mOut.f[ 5] = y * y * (1 - c) + c;
	mOut.f[ 9] = y * z * (1 - c) - (x * s);
	mOut.f[13] = 0;
	
	mOut.f[ 2] = z * x * (1 - c) - (y * s);
	mOut.f[ 6] = z * y * (1 - c) + (x * s);
	mOut.f[10] = z * z * (1 - c) + c;
	mOut.f[14] = 0.0f;
	
	mOut.f[ 3] = 0.0f;
	mOut.f[ 7] = 0.0f;
	mOut.f[11] = 0.0f;
	mOut.f[15] = 1.0f;
}


/*!***************************************************************************
 @Function      MatrixRotationX
 @Output        Output matrix
 @Input         Input angle
 @Description   Create an X rotation matrix mOut.
 ****************************************************************************/
void MatrixRotationX(OGMatrix& mOut, float fAngle)
{
	/* Precompute cos and sin */
	float fCosine = cosf(fAngle);
    float fSine	= sinf(fAngle);

	/* Create the trigonometric matrix corresponding to X Rotation */
	mOut.f[ 0]=1.0f;	mOut.f[ 4]=0.0f;	mOut.f[ 8]=0.0f;	mOut.f[12]=0.0f;
	mOut.f[ 1]=0.0f;	mOut.f[ 5]=fCosine;	mOut.f[ 9]=fSine;	mOut.f[13]=0.0f;
	mOut.f[ 2]=0.0f;	mOut.f[ 6]=-fSine;	mOut.f[10]=fCosine;	mOut.f[14]=0.0f;
	mOut.f[ 3]=0.0f;	mOut.f[ 7]=0.0f;	mOut.f[11]=0.0f;	mOut.f[15]=1.0f;
}


/*!***************************************************************************
 @Function      MatrixRotationY
 @Output        Output matrix
 @Input         Input angle
 @Description   Create an Y rotation matrix mOut.
 ****************************************************************************/
void MatrixRotationY(OGMatrix& mOut, float fAngle)
{
	/* Precompute cos and sin */
	float fCosine = cosf(fAngle);
    float fSine	= sinf(fAngle);

	/* Create the trigonometric matrix corresponding to Y Rotation */
	mOut.f[ 0]=fCosine;		mOut.f[ 4]=0.0f;	mOut.f[ 8]=-fSine;		mOut.f[12]=0.0f;
	mOut.f[ 1]=0.0f;		mOut.f[ 5]=1.0f;	mOut.f[ 9]=0.0f;		mOut.f[13]=0.0f;
	mOut.f[ 2]=fSine;		mOut.f[ 6]=0.0f;	mOut.f[10]=fCosine;		mOut.f[14]=0.0f;
	mOut.f[ 3]=0.0f;		mOut.f[ 7]=0.0f;	mOut.f[11]=0.0f;		mOut.f[15]=1.0f;
}


/*!***************************************************************************
 @Function      MatrixRotationZ
 @Output        Output matrix
 @Input         Input angle
 @Description   Create an Z rotation matrix mOut.
 ****************************************************************************/
void MatrixRotationZ(OGMatrix& mOut, float fAngle)
{
	/* Precompute cos and sin */
	float fCosine = cosf(fAngle);
    float fSine	= sinf(fAngle);

	/* Create the trigonometric matrix corresponding to Z Rotation */
	mOut.f[ 0]=fCosine;		mOut.f[ 4]=fSine;	mOut.f[ 8]=0.0f;	mOut.f[12]=0.0f;
	mOut.f[ 1]=-fSine;		mOut.f[ 5]=fCosine;	mOut.f[ 9]=0.0f;	mOut.f[13]=0.0f;
	mOut.f[ 2]=0.0f;		mOut.f[ 6]=0.0f;	mOut.f[10]=1.0f;	mOut.f[14]=0.0f;
	mOut.f[ 3]=0.0f;		mOut.f[ 7]=0.0f;	mOut.f[11]=0.0f;	mOut.f[15]=1.0f;
}


/*!***************************************************************************
 @Function      MatrixTranspose
 @Output        Output matrix
 @Input         Input matrix
 @Description   Compute the transpose matrix of mIn.
 ****************************************************************************/
void MatrixTranspose(OGMatrix& mOut, const OGMatrix &mIn)
{
	OGMatrix	mTmp;

	mTmp.f[ 0]=mIn.f[ 0];	mTmp.f[ 4]=mIn.f[ 1];	mTmp.f[ 8]=mIn.f[ 2];	mTmp.f[12]=mIn.f[ 3];
	mTmp.f[ 1]=mIn.f[ 4];	mTmp.f[ 5]=mIn.f[ 5];	mTmp.f[ 9]=mIn.f[ 6];	mTmp.f[13]=mIn.f[ 7];
	mTmp.f[ 2]=mIn.f[ 8];	mTmp.f[ 6]=mIn.f[ 9];	mTmp.f[10]=mIn.f[10];	mTmp.f[14]=mIn.f[11];
	mTmp.f[ 3]=mIn.f[12];	mTmp.f[ 7]=mIn.f[13];	mTmp.f[11]=mIn.f[14];	mTmp.f[15]=mIn.f[15];

	mOut = mTmp;
}


/*!***************************************************************************
 @Function      MatrixInverse
 @Output        Output matrix
 @Input         Input matrix
 @Description   Compute the inverse matrix of mIn.
                The matrix must be of the form:
                 A 0
                 C 1
                Where A is a 3x3 matrix and C is a 1x3 matrix.
 ****************************************************************************/
void MatrixInverse(OGMatrix& mOut, const OGMatrix& mIn)
{
	OGMatrix	mDummyMatrix;
	double		det_1;
	double		pos, neg, temp;

    /* Calculate the determinant of submatrix A and determine if the
       the matrix is singular as limited by the double precision
       floating-point data representation. */
    pos = neg = 0.0;
    temp =  mIn.f[ 0] * mIn.f[ 5] * mIn.f[10];
    if (temp >= 0.0) pos += temp; else neg += temp;
    temp =  mIn.f[ 4] * mIn.f[ 9] * mIn.f[ 2];
    if (temp >= 0.0) pos += temp; else neg += temp;
    temp =  mIn.f[ 8] * mIn.f[ 1] * mIn.f[ 6];
    if (temp >= 0.0) pos += temp; else neg += temp;
    temp = -mIn.f[ 8] * mIn.f[ 5] * mIn.f[ 2];
    if (temp >= 0.0) pos += temp; else neg += temp;
    temp = -mIn.f[ 4] * mIn.f[ 1] * mIn.f[10];
    if (temp >= 0.0) pos += temp; else neg += temp;
    temp = -mIn.f[ 0] * mIn.f[ 9] * mIn.f[ 6];
    if (temp >= 0.0) pos += temp; else neg += temp;
    det_1 = pos + neg;

    /* Is the submatrix A singular? */
    if ((det_1 == 0.0) || (OG_ABS(det_1 / (pos - neg)) < 1.0e-15))
	{
        /* Matrix M has no inverse */
        OG_LOG_WARNING("MatrixInverse: Matrix has no inverse (singular matrix)");
        return;
    }
    else
	{
        /* Calculate inverse(A) = adj(A) / det(A) */
        det_1 = 1.0 / det_1;
        mDummyMatrix.f[ 0] =   ( mIn.f[ 5] * mIn.f[10] - mIn.f[ 9] * mIn.f[ 6] ) * (float)det_1;
        mDummyMatrix.f[ 1] = - ( mIn.f[ 1] * mIn.f[10] - mIn.f[ 9] * mIn.f[ 2] ) * (float)det_1;
        mDummyMatrix.f[ 2] =   ( mIn.f[ 1] * mIn.f[ 6] - mIn.f[ 5] * mIn.f[ 2] ) * (float)det_1;
        mDummyMatrix.f[ 4] = - ( mIn.f[ 4] * mIn.f[10] - mIn.f[ 8] * mIn.f[ 6] ) * (float)det_1;
        mDummyMatrix.f[ 5] =   ( mIn.f[ 0] * mIn.f[10] - mIn.f[ 8] * mIn.f[ 2] ) * (float)det_1;
        mDummyMatrix.f[ 6] = - ( mIn.f[ 0] * mIn.f[ 6] - mIn.f[ 4] * mIn.f[ 2] ) * (float)det_1;
        mDummyMatrix.f[ 8] =   ( mIn.f[ 4] * mIn.f[ 9] - mIn.f[ 8] * mIn.f[ 5] ) * (float)det_1;
        mDummyMatrix.f[ 9] = - ( mIn.f[ 0] * mIn.f[ 9] - mIn.f[ 8] * mIn.f[ 1] ) * (float)det_1;
        mDummyMatrix.f[10] =   ( mIn.f[ 0] * mIn.f[ 5] - mIn.f[ 4] * mIn.f[ 1] ) * (float)det_1;

        /* Calculate -C * inverse(A) */
        mDummyMatrix.f[12] = - ( mIn.f[12] * mDummyMatrix.f[ 0] + mIn.f[13] * mDummyMatrix.f[ 4] + mIn.f[14] * mDummyMatrix.f[ 8] );
        mDummyMatrix.f[13] = - ( mIn.f[12] * mDummyMatrix.f[ 1] + mIn.f[13] * mDummyMatrix.f[ 5] + mIn.f[14] * mDummyMatrix.f[ 9] );
        mDummyMatrix.f[14] = - ( mIn.f[12] * mDummyMatrix.f[ 2] + mIn.f[13] * mDummyMatrix.f[ 6] + mIn.f[14] * mDummyMatrix.f[10] );

        /* Fill in last row */
        mDummyMatrix.f[ 3] = 0.0f;
		mDummyMatrix.f[ 7] = 0.0f;
		mDummyMatrix.f[11] = 0.0f;
        mDummyMatrix.f[15] = 1.0f;
	}

   	/* Copy contents of dummy matrix in pfMatrix */
	mOut = mDummyMatrix;
}


/*!***************************************************************************
 @Function      MatrixLinearEqSolve
 @Output        pRes result
 @Input         pSrc 2D array of floats.
 @Description   Solves 'nCnt' simultaneous equations of 'nCnt' variables.
                pRes should be an array large enough to contain the
                results: the values of the 'nCnt' variables.
                This fn recursively uses Gaussian Elimination.
 ****************************************************************************/
void MatrixLinearEqSolve(
	float* const pRes,
	float** const pSrc,
	int	nCnt)
{
	int		i, j, k;
	float	f;

	if(nCnt == 1)
	{
		_ASSERT(pSrc[0][1] != 0);
		pRes[0] = pSrc[0][0] / pSrc[0][1];
		return;
	}

	// Loop backwards in an attempt avoid the need to swap rows
	i = nCnt;
	while(i)
	{
		--i;

		if(pSrc[i][nCnt] != 0)
		{
			// Row i can be used to zero the other rows; let's move it to the bottom
			if(i != (nCnt-1))
			{
				for(j = 0; j <= nCnt; ++j)
				{
					// Swap the two values
					f = pSrc[nCnt-1][j];
					pSrc[nCnt-1][j] = pSrc[i][j];
					pSrc[i][j] = f;
				}
			}

			// Now zero the last columns of the top rows
			for(j = 0; j < (nCnt-1); ++j)
			{
				_ASSERT(pSrc[nCnt-1][nCnt] != 0);
				f = pSrc[j][nCnt] / pSrc[nCnt-1][nCnt];

				// No need to actually calculate a zero for the final column
				for(k = 0; k < nCnt; ++k)
				{
					pSrc[j][k] -= f * pSrc[nCnt-1][k];
				}
			}

			break;
		}
	}

	// Solve the top-left sub matrix
	MatrixLinearEqSolve(pRes, pSrc, nCnt - 1);

	// Now calc the solution for the bottom row
	f = pSrc[nCnt-1][0];
	for(k = 1; k < nCnt; ++k)
	{
		f -= pSrc[nCnt-1][k] * pRes[k-1];
	}
	_ASSERT(pSrc[nCnt-1][nCnt] != 0);
	f /= pSrc[nCnt-1][nCnt];
	pRes[nCnt-1] = f;
}


/*!***************************************************************************
 @Function      MatrixInverseEx
 @Output        Output matrix
 @Input         Input matrix
 @Description   Compute the inverse matrix of mIn.
                Uses a linear equation solver and the knowledge that M.M^-1=I.
                Use this fn to calculate the inverse of matrices that
                MatrixInverse() cannot.
 ****************************************************************************/
void MatrixInverseEx(OGMatrix& mOut, const OGMatrix& mIn)
{
	OGMatrix		mTmp;
	float 			*ppfRows[4];
	float 			pfRes[4];
	float 			pfIn[20];
	int				i, j;

	for(i = 0; i < 4; ++i)
		ppfRows[i] = &pfIn[i * 5];

	/* Solve 4 sets of 4 linear equations */
	for(i = 0; i < 4; ++i)
	{
		for(j = 0; j < 4; ++j)
		{
			ppfRows[j][0] = c_mIdentity.f[i + 4 * j];
			memcpy(&ppfRows[j][1], &mIn.f[j * 4], 4 * sizeof(float));
		}

		MatrixLinearEqSolve(pfRes, (float**)ppfRows, 4);

		for(j = 0; j < 4; ++j)
		{
			mTmp.f[i + 4 * j] = pfRes[j];
		}
	}

	mOut = mTmp;
}


/*!***************************************************************************
 @Function      MatrixLookAtLH
 @Output        Output matrix
 @Input         eye point
 @Input         look at point
 @Input         up vector
 @Description   Create a left-handed look-at view matrix.
 ****************************************************************************/
void MatrixLookAtLH(
	OGMatrix& mOut,
	const OGVec3& vEye,
	const OGVec3& vAt,
	const OGVec3& vUp)
{
	OGVec3 f, vUpActual, s, u;
	OGMatrix	t;

	f.x = vEye.x - vAt.x;
	f.y = vEye.y - vAt.y;
	f.z = vEye.z - vAt.z;

	Vec3Normalize(f, f);
	Vec3Normalize(vUpActual, vUp);
	Vec3CrossProduct(s, f, vUpActual);
	Vec3CrossProduct(u, s, f);

	mOut.f[ 0] = s.x;
	mOut.f[ 1] = u.x;
	mOut.f[ 2] = -f.x;
	mOut.f[ 3] = 0;

	mOut.f[ 4] = s.y;
	mOut.f[ 5] = u.y;
	mOut.f[ 6] = -f.y;
	mOut.f[ 7] = 0;

	mOut.f[ 8] = s.z;
	mOut.f[ 9] = u.z;
	mOut.f[10] = -f.z;
	mOut.f[11] = 0;

	mOut.f[12] = 0;
	mOut.f[13] = 0;
	mOut.f[14] = 0;
	mOut.f[15] = 1;

	MatrixTranslation(t, -vEye.x, -vEye.y, -vEye.z);
	MatrixMultiply(mOut, t, mOut);
}


/*!***************************************************************************
 @Function      MatrixLookAtRH
 @Output        Output matrix
 @Input         eye point
 @Input         look at point
 @Input         up vector
 @Description   Create a right-handed look-at view matrix.
 ****************************************************************************/
void MatrixLookAtRH(
	OGMatrix& mOut,
	const OGVec3& vEye,
	const OGVec3& vAt,
	const OGVec3& vUp)
{
	OGVec3 f, vUpActual, s, u;
	OGMatrix	t;

	f.x = vAt.x - vEye.x;
	f.y = vAt.y - vEye.y;
	f.z = vAt.z - vEye.z;

	Vec3Normalize(f, f);
	Vec3Normalize(vUpActual, vUp);
	Vec3CrossProduct(s, f, vUpActual);
	Vec3CrossProduct(u, s, f);

	mOut.f[ 0] = s.x;
	mOut.f[ 1] = u.x;
	mOut.f[ 2] = -f.x;
	mOut.f[ 3] = 0;

	mOut.f[ 4] = s.y;
	mOut.f[ 5] = u.y;
	mOut.f[ 6] = -f.y;
	mOut.f[ 7] = 0;

	mOut.f[ 8] = s.z;
	mOut.f[ 9] = u.z;
	mOut.f[10] = -f.z;
	mOut.f[11] = 0;

	mOut.f[12] = 0;
	mOut.f[13] = 0;
	mOut.f[14] = 0;
	mOut.f[15] = 1;

	MatrixTranslation(t, -vEye.x, -vEye.y, -vEye.z);
	MatrixMultiply(mOut, t, mOut);
}


/*!***************************************************************************
 @Function      MatrixPerspectiveFovLH
 @Output        Output matrix
 @Input         field of view
 @Input         aspect ratio
 @Input         Z near
 @Input         Z far
 @Input         is view rotated
 @Description   Create a left-handed perspective projection matrix.
 ****************************************************************************/
void MatrixPerspectiveFovLH(
	OGMatrix& mOut,
	float fFOVy,
	float fAspect,
	float fNear,
	float fFar,
	bool bRotate)
{
	float f, n, fRealAspect;

	if (bRotate)
		fRealAspect = 1.0f / fAspect;
	else
		fRealAspect = fAspect;

	// cotangent(a) == 1.0f / tan(a);
	f = 1.0f / (float)tan(fFOVy * 0.5f);
	n = 1.0f / (fFar - fNear);

	mOut.f[ 0] = f / fRealAspect;
	mOut.f[ 1] = 0;
	mOut.f[ 2] = 0;
	mOut.f[ 3] = 0;

	mOut.f[ 4] = 0;
	mOut.f[ 5] = f;
	mOut.f[ 6] = 0;
	mOut.f[ 7] = 0;

	mOut.f[ 8] = 0;
	mOut.f[ 9] = 0;
	mOut.f[10] = fFar * n;
	mOut.f[11] = 1;

	mOut.f[12] = 0;
	mOut.f[13] = 0;
	mOut.f[14] = -fFar * fNear * n;
	mOut.f[15] = 0;

	if (bRotate)
	{
		OGMatrix mRotation, mTemp = mOut;
		MatrixRotationZ(mRotation, 90.0f*PI/180.0f);
		MatrixMultiply(mOut, mTemp, mRotation);
	}
}


/*!***************************************************************************
 @Function      MatrixPerspectiveFovRH
 @Output        Output matrix
 @Input         field of view
 @Input         aspect ratio
 @Input         Z near
 @Input         Z far
 @Input         is view rotated
 @Description   Create a right-handed perspective projection matrix.
 ****************************************************************************/
void MatrixPerspectiveFovRH(
	OGMatrix& mOut,
	float fFOVy,
	float fAspect,
	float fNear,
	float fFar,
	bool bRotate)
{
	float f, n, fRealAspect;

	if (bRotate)
		fRealAspect = 1.0f / fAspect;
	else
		fRealAspect = fAspect;

	// cotangent(a) == 1.0f / tan(a);
	f = 1.0f / (float)tan(fFOVy * 0.5f);
	n = 1.0f / (fNear - fFar);

	mOut.f[ 0] = f / fRealAspect;
	mOut.f[ 1] = 0;
	mOut.f[ 2] = 0;
	mOut.f[ 3] = 0;

	mOut.f[ 4] = 0;
	mOut.f[ 5] = f;
	mOut.f[ 6] = 0;
	mOut.f[ 7] = 0;

	mOut.f[ 8] = 0;
	mOut.f[ 9] = 0;
	mOut.f[10] = (fFar + fNear) * n;
	mOut.f[11] = -1;

	mOut.f[12] = 0;
	mOut.f[13] = 0;
	mOut.f[14] = (2 * fFar * fNear) * n;
	mOut.f[15] = 0;

	if (bRotate)
	{
		OGMatrix mRotation, mTemp = mOut;
		MatrixRotationZ(mRotation, -90.0*PI/180.0f);
		MatrixMultiply(mOut, mTemp, mRotation);
	}
}


/*!***************************************************************************
 @Function      MatrixOrthoLH
 @Output        Output matrix
 @Input         view width
 @Input         view height
 @Input         Z near
 @Input         Z far
 @Input         is view rotated
 @Description   Create a left-handed orthographic projection matrix.
 ****************************************************************************/
void MatrixOrthoLH(
	OGMatrix& mOut,
	float w,
	float h,
	float zn,
	float zf,
	bool  bRotate)
{
	mOut.f[ 0] = 2 / w;
	mOut.f[ 1] = 0;
	mOut.f[ 2] = 0;
	mOut.f[ 3] = 0;

	mOut.f[ 4] = 0;
	mOut.f[ 5] = 2 / h;
	mOut.f[ 6] = 0;
	mOut.f[ 7] = 0;

	mOut.f[ 8] = 0;
	mOut.f[ 9] = 0;
	mOut.f[10] = 1 / (zf - zn);
	mOut.f[11] = zn / (zn - zf);

	mOut.f[12] = 0;
	mOut.f[13] = 0;
	mOut.f[14] = 0;
	mOut.f[15] = 1;

	if (bRotate)
	{
		OGMatrix mRotation, mTemp = mOut;
		MatrixRotationZ(mRotation, -90.0f*PI/180.0f);
		MatrixMultiply(mOut, mRotation, mTemp);
	}
}


/*!***************************************************************************
 @Function      MatrixOrthoRH
 @Output        Output matrix
 @Input         view width
 @Input         view height
 @Input         Z near
 @Input         Z far
 @Input         is view rotated
 @Description   Create a right-handed orthographic projection matrix.
 ****************************************************************************/
void MatrixOrthoRH(
	OGMatrix& mOut,
	float w,
	float h,
	float zn,
	float zf,
	bool  bRotate)
{
	mOut.f[ 0] = 2 / w;
	mOut.f[ 1] = 0;
	mOut.f[ 2] = 0;
	mOut.f[ 3] = 0;

	mOut.f[ 4] = 0;
	mOut.f[ 5] = 2 / h;
	mOut.f[ 6] = 0;
	mOut.f[ 7] = 0;

	mOut.f[ 8] = 0;
	mOut.f[ 9] = 0;
	mOut.f[10] = 1 / (zn - zf);
	mOut.f[11] = zn / (zn - zf);

	mOut.f[12] = 0;
	mOut.f[13] = 0;
	mOut.f[14] = 0;
	mOut.f[15] = 1;

	if (bRotate)
	{
		OGMatrix mRotation, mTemp = mOut;
		MatrixRotationZ(mRotation, -90.0f*PI/180.0f);
		MatrixMultiply(mOut, mRotation, mTemp);
	}
}
