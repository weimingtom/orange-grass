#ifndef _TEXTURE_h_
#define _TEXTURE_h_

#include "OpenGL2.h"
#include <stdio.h>


// Describes the header of a PVR header-texture
typedef struct PVR_Header_Texture_TAG
{
    unsigned int dwHeaderSize;			/*!< size of the structure */
    unsigned int dwHeight;				/*!< height of surface to be created */
    unsigned int dwWidth;				/*!< width of input surface */
    unsigned int dwMipMapCount;			/*!< number of mip-map levels requested */
    unsigned int dwpfFlags;				/*!< pixel format flags */
    unsigned int dwTextureDataSize;		/*!< Total size in bytes */
    unsigned int dwBitCount;			/*!< number of bits per pixel  */
    unsigned int dwRBitMask;			/*!< mask for red bit */
    unsigned int dwGBitMask;			/*!< mask for green bits */
    unsigned int dwBBitMask;			/*!< mask for blue bits */
    unsigned int dwAlphaBitMask;		/*!< mask for alpha channel */
    unsigned int dwPVR;					/*!< magic number identifying pvr file */
    unsigned int dwNumSurfs;			/*!< the number of surfaces present in the pvr */
} PVR_Texture_Header;


// Loads the whole texture from PVR.
unsigned int  LoadTextureFromPVR(
    const char* const filename, 
    GLuint* const texName, 
    const void* psTextureHeader=NULL);


// PVRTC Decompression
void PVRTCDecompress(
    const void* pCompressedData,
    int Do2bitMode,
    int XDim,
    int YDim,
    unsigned char* pResultImage);


// ETC Decompression
int ETCDecompress(
    const void* const pSrcData,
    unsigned int x,
    unsigned int y,
    void *pDestData,
    int nMode);

#endif
