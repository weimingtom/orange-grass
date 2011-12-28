#include "OrangeGrass.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "POD.h"
#include "../ogresourcefile.h"


#define PVRTMODELPOD_TAG_MASK			(0x80000000)
#define PVRTMODELPOD_TAG_START			(0x00000000)
#define PVRTMODELPOD_TAG_END			(0x80000000)
#define CFAH		                    (1024)
#define PVRTMODELPOD_VERSION	        ("AB.POD.2.0") /*!< POD file version string */
#define PVRTMODELPODSF_FIXED	        (0x00000001)   /*!< PVRTMODELPOD Fixed-point 16.16 data (otherwise float) flag */


/*!****************************************************************************
 @Struct      EPODFileName
 @Brief       Enum for the binary pod blocks
******************************************************************************/
enum EPODFileName
{
	ePODFileVersion				= 1000,
	ePODFileScene,
	ePODFileExpOpt,
	ePODFileEndiannessMisMatch  = -402456576,

	ePODFileColourBackground	= 2000,
	ePODFileColourAmbient,
	ePODFileNumCamera,
	ePODFileNumLight,
	ePODFileNumMesh,
	ePODFileNumNode,
	ePODFileNumMeshNode,
	ePODFileNumTexture,
	ePODFileNumMaterial,
	ePODFileNumFrame,
	ePODFileCamera,		// Will come multiple times
	ePODFileLight,		// Will come multiple times
	ePODFileMesh,		// Will come multiple times
	ePODFileNode,		// Will come multiple times
	ePODFileTexture,	// Will come multiple times
	ePODFileMaterial,	// Will come multiple times
	ePODFileFlags,

	ePODFileMatName				= 3000,
	ePODFileMatIdxTexDiffuse,
	ePODFileMatOpacity,
	ePODFileMatAmbient,
	ePODFileMatDiffuse,
	ePODFileMatSpecular,
	ePODFileMatShininess,
	ePODFileMatEffectFile,
	ePODFileMatEffectName,

	ePODFileTexName				= 4000,

	ePODFileNodeIdx				= 5000,
	ePODFileNodeName,
	ePODFileNodeIdxMat,
	ePODFileNodeIdxParent,
	ePODFileNodePos,
	ePODFileNodeRot,
	ePODFileNodeScale,
	ePODFileNodeAnimPos,
	ePODFileNodeAnimRot,
	ePODFileNodeAnimScale,
	ePODFileNodeMatrix,
	ePODFileNodeAnimMatrix,
	ePODFileNodeAnimFlags,

	ePODFileMeshNumVtx			= 6000,
	ePODFileMeshNumFaces,
	ePODFileMeshNumUVW,
	ePODFileMeshFaces,
	ePODFileMeshStripLength,
	ePODFileMeshNumStrips,
	ePODFileMeshVtx,
	ePODFileMeshNor,
	ePODFileMeshTan,
	ePODFileMeshBin,
	ePODFileMeshUVW,			// Will come multiple times
	ePODFileMeshVtxCol,
	ePODFileMeshBoneIdx,
	ePODFileMeshBoneWeight,
	ePODFileMeshInterleaved,
	ePODFileMeshBoneBatches,
	ePODFileMeshBoneBatchBoneCnts,
	ePODFileMeshBoneBatchOffsets,
	ePODFileMeshBoneBatchBoneMax,
	ePODFileMeshBoneBatchCnt,

	ePODFileLightIdxTgt			= 7000,
	ePODFileLightColour,
	ePODFileLightType,

	ePODFileCamIdxTgt			= 8000,
	ePODFileCamFOV,
	ePODFileCamFar,
	ePODFileCamNear,
	ePODFileCamAnimFOV,

	ePODFileDataType			= 9000,
	ePODFileN,
	ePODFileStride,
	ePODFileData
};

struct SPVRTPODImpl
{
	float	fFrame;		    /*!< Frame number */
	float	fBlend;		    /*!< Frame blend	(AKA fractional part of animation frame number) */
	int		nFrame;		    /*!< Frame number (AKA integer part of animation frame number) */

	float	*pfCache;		/*!< Cache indicating the frames at which the matrix cache was filled */
	OGMatrix	*pWmCache;		/*!< Cache of world matrices */
	OGMatrix	*pWmZeroCache;	/*!< Pre-calculated frame 0 matrices */

	bool	bFromMemory;	/*!< Was the mesh data loaded from memory? */
};


/*!***************************************************************************
 @Function			DataTypeRead
 @Output			pV
 @Input				pData
 @Input				eType
 @Input				nCnt
 @Description		Read a vector
*****************************************************************************/
void PVRTVertexRead(
	OGVec4		* const pV,
	const void			* const pData,
	const EPVRTDataType	eType,
	const int			nCnt)
{
	int		i;
	float	*pOut = (float*)pV;

	pV->x = 0;
	pV->y = 0;
	pV->z = 0;
	pV->w = 1;

	switch(eType)
	{
	default:
		_ASSERT(false);
		break;

	case EPODDataFloat:
		for(i = 0; i < nCnt; ++i)
			pOut[i] = ((float*)pData)[i];
		break;

	case EPODDataFixed16_16:
		for(i = 0; i < nCnt; ++i)
			pOut[i] = ((int*)pData)[i] * 1.0f / (float)(1 << 16);
		break;

	case EPODDataInt:
		for(i = 0; i < nCnt; ++i)
			pOut[i] = (float)((int*)pData)[i];
		break;

	case EPODDataByte:
		for(i = 0; i < nCnt; ++i)
			pOut[i] = (float)((char*)pData)[i];
		break;

	case EPODDataByteNorm:
		for(i = 0; i < nCnt; ++i)
			pOut[i] = (float)((char*)pData)[i] / (float)((1 << 7)-1);
		break;

	case EPODDataUnsignedByte:
		for(i = 0; i < nCnt; ++i)
			pOut[i] = (float)((unsigned char*)pData)[i];
		break;

	case EPODDataShort:
		for(i = 0; i < nCnt; ++i)
			pOut[i] = (float)((short*)pData)[i];
		break;

	case EPODDataShortNorm:
		for(i = 0; i < nCnt; ++i)
			pOut[i] = (float)((short*)pData)[i] / (float)((1 << 15)-1);
		break;

	case EPODDataUnsignedShort:
		for(i = 0; i < nCnt; ++i)
			pOut[i] = (float)((unsigned short*)pData)[i];
		break;

	case EPODDataRGBA:
		{
			unsigned int dwVal = *(unsigned int*)pData;
			unsigned char v[4];

			v[0] = dwVal >> 24;
			v[1] = dwVal >> 16;
			v[2] = dwVal >>  8;
			v[3] = dwVal >>  0;

			for(i = 0; i < 4; ++i)
				pOut[i] = 1.0f / 255.0f * (float)v[i];
		}
		break;

	case EPODDataARGB:
	case EPODDataD3DCOLOR:
		{
			unsigned int dwVal = *(unsigned int*)pData;
			unsigned char v[4];

			v[0] = dwVal >> 16;
			v[1] = dwVal >>  8;
			v[2] = dwVal >>  0;
			v[3] = dwVal >> 24;

			for(i = 0; i < 4; ++i)
				pOut[i] = 1.0f / 255.0f * (float)v[i];
		}
		break;

	case EPODDataUBYTE4:
		{
			unsigned int dwVal = *(unsigned int*)pData;
			unsigned char v[4];

			v[0] = dwVal >>  0;
			v[1] = dwVal >>  8;
			v[2] = dwVal >> 16;
			v[3] = dwVal >> 24;

			for(i = 0; i < 4; ++i)
				pOut[i] = v[i];
		}
		break;

	case EPODDataDEC3N:
		{
			int dwVal = *(int*)pData;
			int v[4];

			v[0] = (dwVal << 22) >> 22;
			v[1] = (dwVal << 12) >> 22;
			v[2] = (dwVal <<  2) >> 22;
			v[3] = 0;

			for(i = 0; i < 3; ++i)
				pOut[i] = (float)v[i] * (1.0f / 511.0f);
		}
		break;
	}
}

/*!***************************************************************************
 @Function			PVRTVertexRead
 @Output			pV
 @Input				pData
 @Input				eType
 @Description		Read an int
*****************************************************************************/
void PVRTVertexRead(
	unsigned int		* const pV,
	const void			* const pData,
	const EPVRTDataType	eType)
{
	switch(eType)
	{
	default:
		_ASSERT(false);
		break;

	case EPODDataUnsignedShort:
		*pV = *(unsigned short*)pData;
		break;
	}
}

/*!***************************************************************************
 @Function			ReadCPODData
 @Modified			s The CPODData to read into
 @Input				src COGResourceFile object to read data from.
 @Input				nSpec
 @Input				bValidData
 @Return			true if successful
 @Description		Read a CPODData block in  from a pod file
*****************************************************************************/
static bool ReadCPODData(
	CPODData			&s,
	COGResourceFile		&src,
	const unsigned int	nSpec,
	const bool			bValidData)
{
	unsigned int nName, nLen;

	while(src.ReadMarker(nName, nLen))
	{
		if(nName == (nSpec | PVRTMODELPOD_TAG_END))
			return true;

		switch(nName)
		{
		case ePODFileDataType:	if(!src.Read(s.eType)) return false;					break;
		case ePODFileN:			if(!src.Read(s.n)) return false;						break;
		case ePODFileStride:	if(!src.Read(s.nStride)) return false;					break;
		case ePODFileData:		
            if(bValidData) 
            { 
                if(!src.ReadAfterAlloc(s.pData, nLen)) return false; 
            } 
            else 
            { 
                if(!src.Read(s.pData)) return false; 
            }
            break;

		default:
			if(!src.Skip(nLen)) return false;
		}
	}
	return false;
}

/*!***************************************************************************
 @Function			ReadCamera
 @Modified			s The SPODCamera to read into
 @Input				src	COGResourceFile object to read data from.
 @Return			true if successful
 @Description		Read a camera block in from a pod file
*****************************************************************************/
static bool ReadCamera(
	SPODCamera	&s,
	COGResourceFile		&src)
{
	unsigned int nName, nLen;

	while(src.ReadMarker(nName, nLen))
	{
		switch(nName)
		{
		case ePODFileCamera | PVRTMODELPOD_TAG_END:			return true;

		case ePODFileCamIdxTgt:		if(!src.Read(s.nIdxTarget)) return false;					break;
		case ePODFileCamFOV:		if(!src.Read(s.fFOV)) return false;							break;
		case ePODFileCamFar:		if(!src.Read(s.fFar)) return false;							break;
		case ePODFileCamNear:		if(!src.Read(s.fNear)) return false;						break;
		case ePODFileCamAnimFOV:	if(!src.ReadAfterAlloc(s.pfAnimFOV, nLen)) return false;	break;

		default:
			if(!src.Skip(nLen)) return false;
		}
	}
	return false;
}

/*!***************************************************************************
 @Function			ReadLight
 @Modified			s The SPODLight to read into
 @Input				src	COGResourceFile object to read data from.
 @Return			true if successful
 @Description		Read a light block in from a pod file
*****************************************************************************/
static bool ReadLight(
	SPODLight	&s,
	COGResourceFile		&src)
{
	unsigned int nName, nLen;

	while(src.ReadMarker(nName, nLen))
	{
		switch(nName)
		{
		case ePODFileLight | PVRTMODELPOD_TAG_END:			return true;

		case ePODFileLightIdxTgt:	if(!src.Read(s.nIdxTarget)) return false;	break;
		case ePODFileLightColour:	if(!src.Read(s.pfColour)) return false;		break;
		case ePODFileLightType:		if(!src.Read(s.eType)) return false;		break;

		default:
			if(!src.Skip(nLen)) return false;
		}
	}
	return false;
}

/*!***************************************************************************
 @Function			ReadMaterial
 @Modified			s The SPODMaterial to read into
 @Input				src	COGResourceFile object to read data from.
 @Return			true if successful
 @Description		Read a material block in from a pod file
*****************************************************************************/
static bool ReadMaterial(
	SPODMaterial	&s,
	COGResourceFile			&src)
{
	unsigned int nName, nLen;

	while(src.ReadMarker(nName, nLen))
	{
		switch(nName)
		{
		case ePODFileMaterial | PVRTMODELPOD_TAG_END:			return true;

		case ePODFileMatName:			if(!src.ReadAfterAlloc(s.pszName, nLen)) return false;			break;
		case ePODFileMatIdxTexDiffuse:	if(!src.Read(s.nIdxTexDiffuse)) return false;					break;
		case ePODFileMatOpacity:		if(!src.Read(s.fMatOpacity)) return false;						break;
		case ePODFileMatAmbient:		if(!src.Read(s.pfMatAmbient)) return false;						break;
		case ePODFileMatDiffuse:		if(!src.Read(s.pfMatDiffuse)) return false;						break;
		case ePODFileMatSpecular:		if(!src.Read(s.pfMatSpecular)) return false;					break;
		case ePODFileMatShininess:		if(!src.Read(s.fMatShininess)) return false;					break;
		case ePODFileMatEffectFile:		if(!src.ReadAfterAlloc(s.pszEffectFile, nLen)) return false;	break;
		case ePODFileMatEffectName:		if(!src.ReadAfterAlloc(s.pszEffectName, nLen)) return false;	break;

		default:
			if(!src.Skip(nLen)) return false;
		}
	}
	return false;
}

/*!***************************************************************************
 @Function			ReadMesh
 @Modified			s The SPODMesh to read into
 @Input				src	COGResourceFile object to read data from.
 @Return			true if successful
 @Description		Read a mesh block in from a pod file
*****************************************************************************/
static bool ReadMesh(
	SPODMesh	&s,
	COGResourceFile		&src)
{
	unsigned int	nName, nLen;
	unsigned int	nUVWs=0;

	while(src.ReadMarker(nName, nLen))
	{
		switch(nName)
		{
		case ePODFileMesh | PVRTMODELPOD_TAG_END:
			if(nUVWs != s.nNumUVW) return false;
			return true;

		case ePODFileMeshNumVtx:			if(!src.Read(s.nNumVertex)) return false;													break;
		case ePODFileMeshNumFaces:			if(!src.Read(s.nNumFaces)) return false;													break;
		case ePODFileMeshNumUVW:			if(!src.Read(s.nNumUVW)) return false;	if(!SafeAlloc(s.psUVW, s.nNumUVW)) return false;	break;
		case ePODFileMeshStripLength:		if(!src.ReadAfterAlloc(s.pnStripLength, nLen)) return false;								break;
		case ePODFileMeshNumStrips:			if(!src.Read(s.nNumStrips)) return false;													break;
		case ePODFileMeshInterleaved:		if(!src.ReadAfterAlloc(s.pInterleaved, nLen)) return false;									break;
		case ePODFileMeshBoneBatches:		if(!src.ReadAfterAlloc(s.sBoneBatches.pnBatches, nLen)) return false;						break;
		case ePODFileMeshBoneBatchBoneCnts:	if(!src.ReadAfterAlloc(s.sBoneBatches.pnBatchBoneCnt, nLen)) return false;					break;
		case ePODFileMeshBoneBatchOffsets:	if(!src.ReadAfterAlloc(s.sBoneBatches.pnBatchOffset, nLen)) return false;					break;
		case ePODFileMeshBoneBatchBoneMax:	if(!src.Read(s.sBoneBatches.nBatchBoneMax)) return false;									break;
		case ePODFileMeshBoneBatchCnt:		if(!src.Read(s.sBoneBatches.nBatchCnt)) return false;										break;

		case ePODFileMeshFaces:			if(!ReadCPODData(s.sFaces, src, ePODFileMeshFaces, true)) return false;			break;
		case ePODFileMeshVtx:			if(!ReadCPODData(s.sVertex, src, ePODFileMeshVtx, s.pInterleaved == 0)) return false;			break;
		case ePODFileMeshNor:			if(!ReadCPODData(s.sNormals, src, ePODFileMeshNor, s.pInterleaved == 0)) return false;			break;
		case ePODFileMeshTan:			if(!ReadCPODData(s.sTangents, src, ePODFileMeshTan, s.pInterleaved == 0)) return false;			break;
		case ePODFileMeshBin:			if(!ReadCPODData(s.sBinormals, src, ePODFileMeshBin, s.pInterleaved == 0)) return false;			break;
		case ePODFileMeshUVW:			if(!ReadCPODData(s.psUVW[nUVWs++], src, ePODFileMeshUVW, s.pInterleaved == 0)) return false;		break;
		case ePODFileMeshVtxCol:		if(!ReadCPODData(s.sVtxColours, src, ePODFileMeshVtxCol, s.pInterleaved == 0)) return false;		break;
		case ePODFileMeshBoneIdx:		if(!ReadCPODData(s.sBoneIdx, src, ePODFileMeshBoneIdx, s.pInterleaved == 0)) return false;		break;
		case ePODFileMeshBoneWeight:	if(!ReadCPODData(s.sBoneWeight, src, ePODFileMeshBoneWeight, s.pInterleaved == 0)) return false;	break;

		default:
			if(!src.Skip(nLen)) return false;
		}
	}
	return false;
}

/*!***************************************************************************
 @Function			ReadNode
 @Modified			s The SPODNode to read into
 @Input				src	COGResourceFile object to read data from.
 @Return			true if successful
 @Description		Read a node block in from a pod file
*****************************************************************************/
static bool ReadNode(
	SPODNode	&s,
	COGResourceFile		&src)
{
	unsigned int nName, nLen;
	bool bOldNodeFormat = false;
	float fPos[3]   = {0,0,0};
	float fQuat[4]  = {0,0,0,1};
	float fScale[7] = {1,1,1,0,0,0,0};
	unsigned int nSizeOfOldScale = sizeof(float) * 3;

	while(src.ReadMarker(nName, nLen))
	{
		switch(nName)
		{
		case ePODFileNode | PVRTMODELPOD_TAG_END:
			if(bOldNodeFormat)
			{
				if(s.pfAnimPosition)
					s.nAnimFlags |= ePODHasPositionAni;
				else
				{
					s.pfAnimPosition = (float*) malloc(sizeof(fPos));
					memcpy(s.pfAnimPosition, fPos, sizeof(fPos));
				}

				if(s.pfAnimRotation)
					s.nAnimFlags |= ePODHasRotationAni;
				else
				{
					s.pfAnimRotation = (float*) malloc(sizeof(fQuat));
					memcpy(s.pfAnimRotation, fQuat, sizeof(fQuat));
				}

				if(s.pfAnimScale)
					s.nAnimFlags |= ePODHasScaleAni;
				else
				{
					s.pfAnimScale = (float*) malloc(sizeof(fScale));
					memcpy(s.pfAnimScale, fScale, sizeof(fScale));
				}
			}
			return true;

		case ePODFileNodeIdx:		if(!src.Read(s.nIdx)) return false;								break;
		case ePODFileNodeName:		if(!src.ReadAfterAlloc(s.pszName, nLen)) return false;			break;
		case ePODFileNodeIdxMat:	if(!src.Read(s.nIdxMaterial)) return false;						break;
		case ePODFileNodeIdxParent:	if(!src.Read(s.nIdxParent)) return false;						break;
		case ePODFileNodeAnimFlags:if(!src.Read(s.nAnimFlags))return false;							break;
		case ePODFileNodeAnimPos:	if(!src.ReadAfterAlloc(s.pfAnimPosition, nLen)) return false;	break;
		case ePODFileNodeAnimRot:	if(!src.ReadAfterAlloc(s.pfAnimRotation, nLen)) return false;	break;
		case ePODFileNodeAnimScale:	if(!src.ReadAfterAlloc(s.pfAnimScale, nLen)) return false;		break;
		case ePODFileNodeAnimMatrix:if(!src.ReadAfterAlloc(s.pfAnimMatrix, nLen)) return false;	break;

		// Parameters from the older pod format
		case ePODFileNodePos:		if(!src.Read(fPos))   return false;		bOldNodeFormat = true;		break;
		case ePODFileNodeRot:		if(!src.Read(fQuat))  return false;		bOldNodeFormat = true;		break;
		case ePODFileNodeScale:		if(!src.Read(fScale,nSizeOfOldScale)) return false;		bOldNodeFormat = true;		break;

		default:
			if(!src.Skip(nLen)) return false;
		}
	}

	return false;
}

/*!***************************************************************************
 @Function			ReadTexture
 @Modified			s The SPODTexture to read into
 @Input				src	COGResourceFile object to read data from.
 @Return			true if successful
 @Description		Read a texture block in from a pod file
*****************************************************************************/
static bool ReadTexture(
	SPODTexture	&s,
	COGResourceFile		&src)
{
	unsigned int nName, nLen;

	while(src.ReadMarker(nName, nLen))
	{
		switch(nName)
		{
		case ePODFileTexture | PVRTMODELPOD_TAG_END:			return true;

		case ePODFileTexName:		if(!src.ReadAfterAlloc(s.pszName, nLen)) return false;			break;

		default:
			if(!src.Skip(nLen)) return false;
		}
	}
	return false;
}

/*!***************************************************************************
 @Function			ReadScene
 @Modified			s The SPODScene to read into
 @Input				src	COGResourceFile object to read data from.
 @Return			true if successful
 @Description		Read a scene block in from a pod file
*****************************************************************************/
static bool ReadScene(
	SPODScene	&s,
	COGResourceFile		&src)
{
	unsigned int nName, nLen;
	unsigned int nCameras=0, nLights=0, nMaterials=0, nMeshes=0, nTextures=0, nNodes=0;

	while(src.ReadMarker(nName, nLen))
	{
		switch(nName)
		{
		case ePODFileScene | PVRTMODELPOD_TAG_END:
			if(nCameras		!= s.nNumCamera) return false;
			if(nLights		!= s.nNumLight) return false;
			if(nMaterials	!= s.nNumMaterial) return false;
			if(nMeshes		!= s.nNumMesh) return false;
			if(nTextures	!= s.nNumTexture) return false;
			if(nNodes		!= s.nNumNode) return false;
			return true;

		case ePODFileColourBackground:	if(!src.Read(s.pfColourBackground)) return false;	break;
		case ePODFileColourAmbient:		if(!src.Read(s.pfColourAmbient)) return false;		break;
		case ePODFileNumCamera:			if(!src.Read(s.nNumCamera)) return false;			if(!SafeAlloc(s.pCamera, s.nNumCamera)) return false;		break;
		case ePODFileNumLight:			if(!src.Read(s.nNumLight)) return false;			if(!SafeAlloc(s.pLight, s.nNumLight)) return false;			break;
		case ePODFileNumMesh:			if(!src.Read(s.nNumMesh)) return false;				if(!SafeAlloc(s.pMesh, s.nNumMesh)) return false;			break;
		case ePODFileNumNode:			if(!src.Read(s.nNumNode)) return false;				if(!SafeAlloc(s.pNode, s.nNumNode)) return false;			break;
		case ePODFileNumMeshNode:		if(!src.Read(s.nNumMeshNode)) return false;			break;
		case ePODFileNumTexture:		if(!src.Read(s.nNumTexture)) return false;			if(!SafeAlloc(s.pTexture, s.nNumTexture)) return false;		break;
		case ePODFileNumMaterial:		if(!src.Read(s.nNumMaterial)) return false;			if(!SafeAlloc(s.pMaterial, s.nNumMaterial)) return false;	break;
		case ePODFileNumFrame:			if(!src.Read(s.nNumFrame)) return false;			break;
		case ePODFileFlags:				if(!src.Read(s.nFlags)) return false;				break;

		case ePODFileCamera:	if(!ReadCamera(s.pCamera[nCameras++], src)) return false;		break;
		case ePODFileLight:		if(!ReadLight(s.pLight[nLights++], src)) return false;			break;
		case ePODFileMaterial:	if(!ReadMaterial(s.pMaterial[nMaterials++], src)) return false;	break;
		case ePODFileMesh:		if(!ReadMesh(s.pMesh[nMeshes++], src)) return false;			break;
		case ePODFileNode:		if(!ReadNode(s.pNode[nNodes++], src)) return false;				break;
		case ePODFileTexture:	if(!ReadTexture(s.pTexture[nTextures++], src)) return false;	break;

		default:
			if(!src.Skip(nLen)) return false;
		}
	}
	return false;
}

/*!***************************************************************************
 @Function			Read
 @Output			pS				SPODScene data. May be NULL.
 @Input				src				COGResourceFile object to read data from.
 @Output			pszExpOpt		Export options.
 @Input				count			Data size.
 @Description		Loads the specified ".POD" file; returns the scene in
					pScene. This structure must later be destroyed with
					PVRTModelPODDestroy() to prevent memory leaks.
					".POD" files are exported from 3D Studio MAX using a
					PowerVR plugin. pS may be NULL if only the export options
					are required.
*****************************************************************************/
static bool Read(
	SPODScene		* const pS,
	COGResourceFile			&src,
	char			* const pszExpOpt,
	const size_t	count)
{
	unsigned int	nName, nLen;
	bool			bVersionOK = false, bDone = false;

	if(pS)
		pS->bBigEndian = !IsLittleEndian();

	while(src.ReadMarker(nName, nLen))
	{
		switch(nName)
		{
		case ePODFileVersion:
			{
				char *pszVersion = NULL;
				if(nLen != strlen(PVRTMODELPOD_VERSION)+1) return false;
				if(!SafeAlloc(pszVersion, nLen)) return false;
				if(!src.Read(pszVersion, nLen)) return false;
				if(strcmp(pszVersion, PVRTMODELPOD_VERSION) != 0) return false;
				bVersionOK = true;
				delete [] pszVersion;
			}
			continue;

		case ePODFileScene:
			if(pS)
			{
				if(!ReadScene(*pS, src))
					return false;
				bDone = true;
			}
			continue;

		case ePODFileExpOpt:
			if(pszExpOpt)
			{
				if(!src.Read(pszExpOpt, OG_MIN(nLen, (unsigned int) count))) return false;
				return true;
			}
			break;

		case ePODFileScene | PVRTMODELPOD_TAG_END:
			return bVersionOK == true && bDone == true;

		case (unsigned int) ePODFileEndiannessMisMatch:
			OG_LOG_ERROR("POD Read: Endianness mismatch between the .pod file and the platform.");
			return false;

		}

		// Unhandled data, skip it
		if(!src.Skip(nLen))
			return false;
	}

	/*
		Convert data to fixed or float point as this build desires
	*/
	if(pS->nFlags & PVRTMODELPODSF_FIXED)
    {
        OG_LOG_ERROR("POD Read: Cannot read the fixed-point POD.");
		return false;
    }

	return bVersionOK == true && bDone == true;
}


/*!***************************************************************************
 @Function			ReadFromFile
 @Input				pszFileName		Filename to load
 @Output			pszExpOpt		String in which to place exporter options
 @Input				count			Maximum number of characters to store.
 @Return			PVR_SUCCESS if successful, PVR_FAIL if not
 @Description		Loads the specified ".POD" file; returns the scene in
					pScene. This structure must later be destroyed with
					PVRTModelPODDestroy() to prevent memory leaks.
					".POD" files are exported from 3D Studio MAX using a
					PowerVR plugin.
					If pszExpOpt is NULL, the scene is loaded; otherwise the
					scene is not loaded and pszExpOpt is filled in.
*****************************************************************************/
bool CPVRTModelPOD::ReadFromFile(
	const char		* const pszFileName,
	char			* const pszExpOpt,
	const size_t	count)
{
	COGResourceFile src;
    if(!src.Open(pszFileName))
		return false;

	memset(this, 0, sizeof(*this));
	if(!Read(pszExpOpt ? NULL : this, src, pszExpOpt, count))
		return false;
	if(InitImpl() != true)
		return false;
	return true;
}


/*!***********************************************************************
 @Function		InitImpl
 @Description	Used by the Read*() fns to initialise implementation
				details. Should also be called by applications which
				manually build data in the POD structures for rendering;
				in this case call it after the data has been created.
				Otherwise, do not call this function.
*************************************************************************/
bool CPVRTModelPOD::InitImpl()
{
	// Allocate space for implementation data
	m_pImpl = new SPVRTPODImpl;
	if(!m_pImpl)
		return false;

	// Zero implementation data
	memset(m_pImpl, 0, sizeof(*m_pImpl));

	// Allocate world-matrix cache
	m_pImpl->pfCache		= new float[nNumNode];
	m_pImpl->pWmCache		= new  OGMatrix[nNumNode];
	m_pImpl->pWmZeroCache	= new  OGMatrix[nNumNode];
	FlushCache();

	return true;
}

/*!***********************************************************************
 @Function		FlushCache
 @Description	Clears the matrix cache; use this if necessary when you
				edit the position or animation of a node.
*************************************************************************/
void CPVRTModelPOD::FlushCache()
{
	// Pre-calc frame zero matrices
	SetFrame(0);
	for(unsigned int i = 0; i < nNumNode; ++i)
		GetWorldMatrixNoCache(m_pImpl->pWmZeroCache[i], pNode[i]);

	// Load cache with frame-zero data
	memcpy(m_pImpl->pWmCache, m_pImpl->pWmZeroCache, nNumNode * sizeof(*m_pImpl->pWmCache));
	memset(m_pImpl->pfCache, 0, nNumNode * sizeof(*m_pImpl->pfCache));
}


/*!***************************************************************************
 @Function			Constructor
 @Description		Initializes the pointer to scene data to NULL
*****************************************************************************/
CPVRTModelPOD::CPVRTModelPOD() : m_pImpl(NULL)
{
}


/*!***************************************************************************
 @Function			Destructor
 @Description		Frees the memory allocated to store the scene in pScene.
*****************************************************************************/
CPVRTModelPOD::~CPVRTModelPOD()
{
	Destroy();
}


/*!***************************************************************************
 @Function			Destroy
 @Description		Frees the memory allocated to store the scene in pScene.
*****************************************************************************/
void CPVRTModelPOD::Destroy()
{
	unsigned int	i;

	if(m_pImpl != NULL)
	{
		/*
			Only attempt to free this memory if it was actually allocated at
			run-time, as opposed to compiled into the app.
		*/
		if(!m_pImpl->bFromMemory)
		{

			for(i = 0; i < nNumCamera; ++i)
				free(pCamera[i].pfAnimFOV);
			free(pCamera);

			free(pLight);

			for(i = 0; i < nNumMaterial; ++i)
			{
				free(pMaterial[i].pszName);
				free(pMaterial[i].pszEffectFile);
				free(pMaterial[i].pszEffectName);
			}
			free(pMaterial);

			for(i = 0; i < nNumMesh; ++i) {
				free(pMesh[i].sFaces.pData);
				free(pMesh[i].pnStripLength);
				if(pMesh[i].pInterleaved)
				{
					free(pMesh[i].pInterleaved);
				}
				else
				{
					free(pMesh[i].sVertex.pData);
					free(pMesh[i].sNormals.pData);
					free(pMesh[i].sTangents.pData);
					free(pMesh[i].sBinormals.pData);
					for(unsigned int j = 0; j < pMesh[i].nNumUVW; ++j)
						free(pMesh[i].psUVW[j].pData);
					free(pMesh[i].sVtxColours.pData);
					free(pMesh[i].sBoneIdx.pData);
					free(pMesh[i].sBoneWeight.pData);
				}
				free(pMesh[i].psUVW);
				pMesh[i].sBoneBatches.Release();
			}
			free(pMesh);

			for(i = 0; i < nNumNode; ++i) {
				free(pNode[i].pszName);
				free(pNode[i].pfAnimPosition);
				free(pNode[i].pfAnimRotation);
				free(pNode[i].pfAnimScale);
				free(pNode[i].pfAnimMatrix);
				pNode[i].nAnimFlags = 0;
			}

			free(pNode);

			for(i = 0; i < nNumTexture; ++i)
				free(pTexture[i].pszName);
			free(pTexture);
		}

		// Free the working space used by the implementation
		delete [] m_pImpl->pfCache;
		delete [] m_pImpl->pWmCache;
		delete [] m_pImpl->pWmZeroCache;
		delete m_pImpl;
	}

	memset(this, 0, sizeof(*this));
}

/*!***************************************************************************
 @Function			SetFrame
 @Input				fFrame			Frame number
 @Description		Set the animation frame for which subsequent Get*() calls
					should return data.
*****************************************************************************/
void CPVRTModelPOD::SetFrame(const float fFrame)
{
	if(nNumFrame) {
		/*
			Limit animation frames.

			Example: If there are 100 frames of animation, the highest frame
			number allowed is 98, since that will blend between frames 98 and
			99. (99 being of course the 100th frame.)
		*/
		_ASSERT(fFrame <= (float)(nNumFrame-1));
		m_pImpl->nFrame = (int)fFrame;
		m_pImpl->fBlend = fFrame - m_pImpl->nFrame;
	}
	else
	{
		m_pImpl->fBlend = 0;
		m_pImpl->nFrame = 0;
	}

	m_pImpl->fFrame = fFrame;
}

/*!***************************************************************************
 @Function			GetRotationMatrix
 @Output			mOut			Rotation matrix
 @Input				node			Node to get the rotation matrix from
 @Description		Generates the world matrix for the given Mesh Instance;
					applies the parent's transform too. Uses animation data.
*****************************************************************************/
void CPVRTModelPOD::GetRotationMatrix(
	OGMatrix		&mOut,
	const SPODNode	&node) const
{
	 OGQuat	q;

	if(node.pfAnimRotation)
	{
		if(node.nAnimFlags & ePODHasRotationAni)
		{
			QuaternionSlerp(
			    q,
				(OGQuat&)node.pfAnimRotation[4*m_pImpl->nFrame],
				(OGQuat&)node.pfAnimRotation[4*(m_pImpl->nFrame+1)], m_pImpl->fBlend);
			QuaternionToRotationMatrix(mOut, q);
		}
		else
		{
			QuaternionToRotationMatrix(mOut, *(OGQuat*)node.pfAnimRotation);
		}
	}
	else
	{
		MatrixIdentity(mOut);
	}
}

/*!***************************************************************************
 @Function		GetRotationMatrix
 @Input			node			Node to get the rotation matrix from
 @Returns		Rotation matrix
 @Description	Generates the world matrix for the given Mesh Instance;
				applies the parent's transform too. Uses animation data.
*****************************************************************************/
OGMatrix CPVRTModelPOD::GetRotationMatrix(const SPODNode &node) const
{
	OGMatrix mOut;
	GetRotationMatrix(mOut,node);
	return mOut;
}

/*!***************************************************************************
 @Function			GetScalingMatrix
 @Output			mOut			Scaling matrix
 @Input				node			Node to get the rotation matrix from
 @Description		Generates the world matrix for the given Mesh Instance;
					applies the parent's transform too. Uses animation data.
*****************************************************************************/
void CPVRTModelPOD::GetScalingMatrix(
	OGMatrix		&mOut,
	const SPODNode	&node) const
{
	 OGVec3 v;

	if(node.pfAnimScale)
	{
		if(node.nAnimFlags & ePODHasScaleAni)
		{
			Vec3Lerp(
			    v,
				(OGVec3&)node.pfAnimScale[7*(m_pImpl->nFrame+0)],
				(OGVec3&)node.pfAnimScale[7*(m_pImpl->nFrame+1)], m_pImpl->fBlend);
			MatrixScaling(mOut, v.x, v.y, v.z);
	}
	else
	{
			MatrixScaling(mOut, node.pfAnimScale[0], node.pfAnimScale[1], node.pfAnimScale[2]);
		}
	}
	else
	{
		MatrixIdentity(mOut);
	}
}

/*!***************************************************************************
 @Function		GetScalingMatrix
 @Input			node			Node to get the rotation matrix from
 @Returns		Scaling matrix
 @Description	Generates the world matrix for the given Mesh Instance;
				applies the parent's transform too. Uses animation data.
*****************************************************************************/
OGMatrix CPVRTModelPOD::GetScalingMatrix(const SPODNode &node) const
{
	OGMatrix mOut;
	GetScalingMatrix(mOut, node);
	return mOut;
}

/*!***************************************************************************
 @Function			GetTranslation
 @Output			V				Translation vector
 @Input				node			Node to get the translation vector from
 @Description		Generates the translation vector for the given Mesh
					Instance. Uses animation data.
*****************************************************************************/
void CPVRTModelPOD::GetTranslation(
	OGVec3		&V,
	const SPODNode	&node) const
{
	if(node.pfAnimPosition)
	{
		if(node.nAnimFlags & ePODHasPositionAni)
		{
			Vec3Lerp(
			    V,
				(OGVec3&)node.pfAnimPosition[3 * (m_pImpl->nFrame+0)],
				(OGVec3&)node.pfAnimPosition[3 * (m_pImpl->nFrame+1)], m_pImpl->fBlend);
		}
		else
		{
			V = *(OGVec3*) node.pfAnimPosition;
		}
	}
	else
	{
		_ASSERT(false);
	}
}

/*!***************************************************************************
 @Function		GetTranslation
 @Input			node			Node to get the translation vector from
 @Returns		Translation vector
 @Description	Generates the translation vector for the given Mesh
				Instance. Uses animation data.
*****************************************************************************/
OGVec3 CPVRTModelPOD::GetTranslation(const SPODNode &node) const
{
	OGVec3 vOut;
	GetTranslation(vOut, node);
	return vOut;
}

/*!***************************************************************************
 @Function			GetTranslationMatrix
 @Output			mOut			Translation matrix
 @Input				node			Node to get the translation matrix from
 @Description		Generates the world matrix for the given Mesh Instance;
					applies the parent's transform too. Uses animation data.
*****************************************************************************/
void CPVRTModelPOD::GetTranslationMatrix(
	OGMatrix		&mOut,
	const SPODNode	&node) const
{
	 OGVec3 v;

	if(node.pfAnimPosition)
	{
		if(node.nAnimFlags & ePODHasPositionAni)
		{
			Vec3Lerp(v,
				(OGVec3&)node.pfAnimPosition[3*(m_pImpl->nFrame+0)],
				(OGVec3&)node.pfAnimPosition[3*(m_pImpl->nFrame+1)], m_pImpl->fBlend);
			MatrixTranslation(mOut, v.x, v.y, v.z);
		}
		else
		{
			MatrixTranslation(mOut, node.pfAnimPosition[0], node.pfAnimPosition[1], node.pfAnimPosition[2]);
		}
	}
	else
	{
		MatrixIdentity(mOut);
	}
}

/*!***************************************************************************
 @Function		GetTranslationMatrix
 @Input			node			Node to get the translation matrix from
 @Returns		Translation matrix
 @Description	Generates the world matrix for the given Mesh Instance;
				applies the parent's transform too. Uses animation data.
*****************************************************************************/
OGMatrix CPVRTModelPOD::GetTranslationMatrix(const SPODNode &node) const
{
	OGMatrix mOut;
	GetTranslationMatrix(mOut, node);
	return mOut;
}

/*!***************************************************************************
 @Function		GetTransformationMatrix
 @Output		mOut			Transformation matrix
 @Input			node			Node to get the transformation matrix from
 @Description	Generates the world matrix for the given Mesh Instance;
				applies the parent's transform too. Uses animation data.
*****************************************************************************/
void CPVRTModelPOD::GetTransformationMatrix(OGMatrix &mOut, const SPODNode &node) const
{
	if(node.pfAnimMatrix)
	{
		if(node.nAnimFlags & ePODHasMatrixAni)
		{
			mOut = *((OGMatrix*) &node.pfAnimMatrix[16*m_pImpl->nFrame]);
		}
		else
		{
			mOut = *((OGMatrix*) node.pfAnimMatrix);
		}
	}
	else
	{
		MatrixIdentity(mOut);
	}
}
/*!***************************************************************************
 @Function			GetWorldMatrixNoCache
 @Output			mOut			World matrix
 @Input				node			Node to get the world matrix from
 @Description		Generates the world matrix for the given Mesh Instance;
					applies the parent's transform too. Uses animation data.
*****************************************************************************/
void CPVRTModelPOD::GetWorldMatrixNoCache(
	OGMatrix		&mOut,
	const SPODNode	&node) const
{
	 OGMatrix mTmp;

	if(node.pfAnimMatrix) // The transformations are stored as matrices
		GetTransformationMatrix(mOut, node);
	else
	{
	// Scale
	GetScalingMatrix(mOut, node);

	// Rotation
	GetRotationMatrix(mTmp, node);
	 MatrixMultiply(mOut, mOut, mTmp);

	// Translation
	GetTranslationMatrix(mTmp, node);
	 MatrixMultiply(mOut, mOut, mTmp);
	 }

	// Do we have to worry about a parent?
	if(node.nIdxParent < 0)
		return;

	// Apply parent's transform too.
	GetWorldMatrixNoCache(mTmp, pNode[node.nIdxParent]);
	MatrixMultiply(mOut, mOut, mTmp);
}

/*!***************************************************************************
 @Function		GetWorldMatrixNoCache
 @Input			node			Node to get the world matrix from
 @Returns		World matrix
 @Description	Generates the world matrix for the given Mesh Instance;
				applies the parent's transform too. Uses animation data.
*****************************************************************************/
OGMatrix CPVRTModelPOD::GetWorldMatrixNoCache(const SPODNode& node) const
{
	OGMatrix mWorld;
	GetWorldMatrixNoCache(mWorld,node);
	return mWorld;
}

/*!***************************************************************************
 @Function			GetWorldMatrix
 @Output			mOut			World matrix
 @Input				node			Node to get the world matrix from
 @Description		Generates the world matrix for the given Mesh Instance;
					applies the parent's transform too. Uses animation data.
*****************************************************************************/
void CPVRTModelPOD::GetWorldMatrix(
	OGMatrix		&mOut,
	const SPODNode	&node) const
{
	unsigned int nIdx;

	// Calculate a node index
	nIdx = (unsigned int)(&node - pNode);

	// There is a dedicated cache for frame 0 data
	if(m_pImpl->fFrame == 0)
	{
		mOut = m_pImpl->pWmZeroCache[nIdx];
		return;
	}

	// Has this matrix been calculated & cached?
	if(m_pImpl->fFrame == m_pImpl->pfCache[nIdx])
	{
		mOut = m_pImpl->pWmCache[nIdx];
		return;
	}

	GetWorldMatrixNoCache(mOut, node);

	// Cache the matrix
	m_pImpl->pfCache[nIdx]	= m_pImpl->fFrame;
	m_pImpl->pWmCache[nIdx]	= mOut;
}

/*!***************************************************************************
 @Function		GetWorldMatrix
 @Input			node			Node to get the world matrix from
 @Returns		World matrix
 @Description	Generates the world matrix for the given Mesh Instance;
				applies the parent's transform too. Uses animation data.
*****************************************************************************/
OGMatrix CPVRTModelPOD::GetWorldMatrix(const SPODNode& node) const
{
	OGMatrix mWorld;
	GetWorldMatrix(mWorld,node);
	return mWorld;
}

/*!***************************************************************************
 @Function			GetBoneWorldMatrix
 @Output			mOut			Bone world matrix
 @Input				NodeMesh		Mesh to take the bone matrix from
 @Input				NodeBone		Bone to take the matrix from
 @Description		Generates the world matrix for the given bone.
*****************************************************************************/
void CPVRTModelPOD::GetBoneWorldMatrix(OGMatrix		    &mOut,
                                       const SPODNode	&NodeMesh,
                                       const SPODNode	&NodeBone)
{
    OGMatrix	mTmp;
    float	fFrame;

    fFrame = m_pImpl->fFrame;

    SetFrame(0);

    // Transform by object matrix
    GetWorldMatrix(mOut, NodeMesh);

    // Back transform bone from frame 0 position
    GetWorldMatrix(mTmp, NodeBone);
    MatrixInverse(mTmp, mTmp);
    MatrixMultiply(mOut, mOut, mTmp);

    // The bone origin should now be at the origin
    SetFrame(fFrame);

    // Transform bone into frame fFrame position
    GetWorldMatrix(mTmp, NodeBone);
    MatrixMultiply(mOut, mOut, mTmp);
}

/*!***************************************************************************
 @Function		GetBoneWorldMatrix
 @Input			NodeMesh		Mesh to take the bone matrix from
 @Input			NodeBone		Bone to take the matrix from
 @Returns		Bone world matrix
 @Description	Generates the world matrix for the given bone.
*****************************************************************************/
OGMatrix CPVRTModelPOD::GetBoneWorldMatrix(
	const SPODNode	&NodeMesh,
	const SPODNode	&NodeBone)
{
	OGMatrix mOut;
	GetBoneWorldMatrix(mOut,NodeMesh,NodeBone);
	return mOut;
}

/*!***************************************************************************
 @Function			GetCamera
 @Output			vFrom			Position of the camera
 @Output			vTo				Target of the camera
 @Output			vUp				Up direction of the camera
 @Input				nIdx			Camera number
 @Return			Camera horizontal FOV
 @Description		Calculate the From, To and Up vectors for the given
					camera. Uses animation data.
					Note that even if the camera has a target, *pvTo is not
					the position of that target. *pvTo is a position in the
					correct direction of the target, one unit away from the
					camera.
*****************************************************************************/
float CPVRTModelPOD::GetCamera(
	OGVec3			&vFrom,
	OGVec3			&vTo,
	OGVec3			&vUp,
	const unsigned int	nIdx) const
{
	 OGMatrix		mTmp;
	float		*pfData;
	SPODCamera		*pCam;
	const SPODNode	*pNd;

	_ASSERT(nIdx < nNumCamera);

	// Camera nodes are after the mesh and light nodes in the array
	pNd = &pNode[nNumMeshNode + nNumLight + nIdx];

	pCam = &pCamera[pNd->nIdx];

	GetWorldMatrix(mTmp, *pNd);

	// View position is 0,0,0,1 transformed by world matrix
	vFrom.x = mTmp.f[12];
	vFrom.y = mTmp.f[13];
	vFrom.z = mTmp.f[14];

	// View direction is 0,-1,0,1 transformed by world matrix
	vTo.x = -mTmp.f[4] + mTmp.f[12];
	vTo.y = -mTmp.f[5] + mTmp.f[13];
	vTo.z = -mTmp.f[6] + mTmp.f[14];

	/*
		When you rotate the camera from "straight forward" to "straight down", in
		OpenGL the UP vector will be [0, 0, -1]
	*/
	vUp.x = -mTmp.f[ 8];
	vUp.y = -mTmp.f[ 9];
	vUp.z = -mTmp.f[10];

	/*
		Find & calculate FOV value
	*/
	if(pCam->pfAnimFOV) {
		pfData = &pCam->pfAnimFOV[m_pImpl->nFrame];

		return pfData[0] + m_pImpl->fBlend * (pfData[1] - pfData[0]);
	} else {
		return pCam->fFOV;
	}
}

/*!***************************************************************************
 @Function			GetCameraPos
 @Output			vFrom			Position of the camera
 @Output			vTo				Target of the camera
 @Input				nIdx			Camera number
 @Return			Camera horizontal FOV
 @Description		Calculate the position of the camera and its target. Uses
					animation data.
					If the queried camera does not have a target, *pvTo is
					not changed.
*****************************************************************************/
float CPVRTModelPOD::GetCameraPos(
	OGVec3			&vFrom,
	OGVec3			&vTo,
	const unsigned int	nIdx) const
{
	 OGMatrix		mTmp;
	float		*pfData;
	SPODCamera		*pCam;
	const SPODNode	*pNd;

	_ASSERT(nIdx < nNumCamera);

	// Camera nodes are after the mesh and light nodes in the array
	pNd = &pNode[nNumMeshNode + nNumLight + nIdx];

	// View position is 0,0,0,1 transformed by world matrix
	GetWorldMatrix(mTmp, *pNd);
	vFrom.x = mTmp.f[12];
	vFrom.y = mTmp.f[13];
	vFrom.z = mTmp.f[14];

	pCam = &pCamera[pNd->nIdx];
	if(pCam->nIdxTarget >= 0)
	{
		// View position is 0,0,0,1 transformed by world matrix
		GetWorldMatrix(mTmp, pNode[pCam->nIdxTarget]);
		vTo.x = mTmp.f[12];
		vTo.y = mTmp.f[13];
		vTo.z = mTmp.f[14];
	}

	/*
		Find & calculate FOV value
	*/
	if(pCam->pfAnimFOV) {
		pfData = &pCam->pfAnimFOV[m_pImpl->nFrame];

		return pfData[0] + m_pImpl->fBlend * (pfData[1] - pfData[0]);
	} else {
		return pCam->fFOV;
	}
}

/*!***************************************************************************
 @Function			GetLight
 @Output			vPos			Position of the light
 @Output			vDir			Direction of the light
 @Input				nIdx			Light number
 @Description		Calculate the position and direction of the given Light.
					Uses animation data.
*****************************************************************************/
void CPVRTModelPOD::GetLight(
	OGVec3			&vPos,
	OGVec3			&vDir,
	const unsigned int	nIdx) const
{
	 OGMatrix		mTmp;
	const SPODNode	*pNd;

	_ASSERT(nIdx < nNumLight);

	// Light nodes are after the mesh nodes in the array
	pNd = &pNode[nNumMeshNode + nIdx];

	GetWorldMatrix(mTmp, *pNd);

	// View position is 0,0,0,1 transformed by world matrix
	vPos.x = mTmp.f[12];
	vPos.y = mTmp.f[13];
	vPos.z = mTmp.f[14];

	// View direction is 0,-1,0,0 transformed by world matrix
	vDir.x = -mTmp.f[4];
	vDir.y = -mTmp.f[5];
	vDir.z = -mTmp.f[6];
}

/*!***************************************************************************
 @Function		GetLight
 @Input			nIdx			Light number
 @Return		OGVec4 position/direction of light with w set correctly
 @Description	Calculate the position or direction of the given Light.
				Uses animation data.
*****************************************************************************/
OGVec4 CPVRTModelPOD::GetLightPosition(const unsigned int u32Idx) const
{	// TODO: make this a real function instead of just wrapping GetLight()
	OGVec3 vPos, vDir;
	GetLight(vPos,vDir,u32Idx);

	_ASSERT(u32Idx < nNumLight);
	_ASSERT(pLight[u32Idx].eType==ePODPoint);
	return OGVec4(vPos,1);
}

/*!***************************************************************************
 @Function		GetLightDirection
 @Input			u32Idx			Light number
 @Return		OGVec4 direction of light with w set correctly
 @Description	Calculate the direction of the given Light. Uses animation data.
*****************************************************************************/
OGVec4 CPVRTModelPOD::GetLightDirection(const unsigned int u32Idx) const
{	// TODO: make this a real function instead of just wrapping GetLight()
	OGVec3 vPos, vDir;
	GetLight(vPos,vDir,u32Idx);

	_ASSERT(u32Idx < nNumLight);
	_ASSERT(pLight[u32Idx].eType==ePODDirectional);
	return OGVec4(vDir,1);
}

/*!***************************************************************************
 @Function			CreateSkinIdxWeight
 @Output			pIdx				Four bytes containing matrix indices for vertex (0..255)
 @Output			pWeight				Four bytes containing blend weights for vertex (0.0 .. 1.0)
 @Input				nVertexBones		Number of bones this vertex uses
 @Input				pnBoneIdx			Pointer to 'nVertexBones' indices
 @Input				pfBoneWeight		Pointer to 'nVertexBones' blend weights
 @Description		Creates the matrix indices and blend weights for a boned
					vertex. Call once per vertex of a boned mesh.
*****************************************************************************/
bool CPVRTModelPOD::CreateSkinIdxWeight(
	char* const pIdx,
	char* const pWeight,
	int	nVertexBones,
	const int* const pnBoneIdx,
	const float* const pfBoneWeight)
{
	int i, nSum;
	int nIdx[4];
	int nWeight[4];

	for(i = 0; i < nVertexBones; ++i)
	{
		nIdx[i]		= pnBoneIdx[i];
		nWeight[i]	= (int)(255.0f * pfBoneWeight[i]);

		if(nIdx[i] > 255)
		{
			OG_LOG_WARNING("CPVRTModelPOD::CreateSkinIdxWeight - Too many bones (highest index is 255).");
			return false;
		}

		nWeight[i]	= OG_MAX(nWeight[i], 0);
		nWeight[i]	= OG_MIN(nWeight[i], 255);
	}

	for(; i < 4; ++i)
	{
		nIdx[i]		= 0;
		nWeight[i]	= 0;
	}

	if(nVertexBones)
	{
		// It's important the weights sum to 1
		nSum = 0;
		for(i = 0; i < 4; ++i)
			nSum += nWeight[i];

		if(!nSum)
			return false;

		_ASSERT(nSum <= 255);

		i = 0;
		while(nSum < 255)
		{
			if(nWeight[i]) {
				++nWeight[i];
				++nSum;
			}

			if(++i > 3)
				i = 0;
		}

		_ASSERT(nSum == 255);
	}

	// Return indices and weights as bytes
	for(i = 0; i < 4; ++i)
	{
		pIdx[i]		= nIdx[i];
		pWeight[i]	= nWeight[i];
	}
	return true;
}


/*!***************************************************************************
 @Function			ModelPODDataTypeSize
 @Input				type		Type to get the size of
 @Return			Size of the data element
 @Description		Returns the size of each data element.
*****************************************************************************/
size_t PVRTModelPODDataTypeSize(const EPVRTDataType type)
{
	switch(type)
	{
	default:
		_ASSERT(false);
		return 0;
	case EPODDataFloat:
		return sizeof(float);
	case EPODDataInt:
		return sizeof(int);
	case EPODDataShort:
	case EPODDataShortNorm:
	case EPODDataUnsignedShort:
		return sizeof(unsigned short);
	case EPODDataRGBA:
		return sizeof(unsigned int);
	case EPODDataARGB:
		return sizeof(unsigned int);
	case EPODDataD3DCOLOR:
		return sizeof(unsigned int);
	case EPODDataUBYTE4:
		return sizeof(unsigned int);
	case EPODDataDEC3N:
		return sizeof(unsigned int);
	case EPODDataFixed16_16:
		return sizeof(unsigned int);
	case EPODDataUnsignedByte:
	case EPODDataByte:
	case EPODDataByteNorm:
		return sizeof(unsigned char);
	}
}

/*!***************************************************************************
@Function			ModelPODDataTypeComponentCount
@Input				type		Type to get the number of components from
@Return				number of components in the data element
@Description		Returns the number of components in a data element.
*****************************************************************************/
size_t PVRTModelPODDataTypeComponentCount(const EPVRTDataType type)
{
	switch(type)
	{
	default:
		_ASSERT(false);
		return 0;

	case EPODDataFloat:
	case EPODDataInt:
	case EPODDataShort:
	case EPODDataShortNorm:
	case EPODDataUnsignedShort:
	case EPODDataFixed16_16:
	case EPODDataByte:
	case EPODDataByteNorm:
	case EPODDataUnsignedByte:
		return 1;

	case EPODDataDEC3N:
		return 3;

	case EPODDataRGBA:
	case EPODDataARGB:
	case EPODDataD3DCOLOR:
	case EPODDataUBYTE4:
		return 4;
	}
}

/*!***************************************************************************
 @Function			PVRTModelPODDataStride
 @Input				data		Data elements
 @Return			Size of the vector elements
 @Description		Returns the size of the vector of data elements.
*****************************************************************************/
size_t PVRTModelPODDataStride(const CPODData &data)
{
	return PVRTModelPODDataTypeSize(data.eType) * data.n;
}

/*!***************************************************************************
 @Function		PVRTModelPODCountIndices
 @Input			mesh		Mesh
 @Return		Number of indices used by mesh
 @Description	Counts the number of indices of a mesh
*****************************************************************************/
unsigned int PVRTModelPODCountIndices(const SPODMesh &mesh)
{
	if(mesh.nNumStrips)
	{
		unsigned int i, n = 0;

		for(i = 0; i < mesh.nNumStrips; ++i)
			n += mesh.pnStripLength[i] + 2;

		return n;
	}

	return mesh.nNumFaces * 3;
}
