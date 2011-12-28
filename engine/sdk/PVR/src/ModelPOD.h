#ifndef _MODELPOD_H_
#define _MODELPOD_H_

#include <Mathematics.h>
#include <Geometry.h>
#include <MemoryManager.h>
#include "Macros.h"

#define PVRTMODELPOD_VERSION	("AB.POD.2.0") /*!< POD file version string */
#define PVRTMODELPODSF_FIXED	(0x00000001)   /*!< PVRTMODELPOD Fixed-point 16.16 data (otherwise float) flag */


/*!****************************************************************************
 @Struct      EPODLight
 @Brief       Enum for the POD format light types
******************************************************************************/
enum EPODLight
{
    ePODPoint=0,	/*!< Point light */
    ePODDirectional /*!< Directional light */
};


/*!****************************************************************************
 @Struct      EPODPrimitiveType
 @Brief       Enum for the POD format primitive types
******************************************************************************/
enum EPODPrimitiveType
{
    ePODTriangles=0, /*!< Triangles */
    ePODLines		 /*!< Lines*/
};


/*!****************************************************************************
 @Struct      EPODAnimationData
 @Brief       Enum for the POD format animation types
******************************************************************************/
enum EPODAnimationData
{
    ePODHasPositionAni	= 0x01,	/*!< Position animation */
    ePODHasRotationAni	= 0x02, /*!< Rotation animation */
    ePODHasScaleAni		= 0x04, /*!< Scale animation */
    ePODHasMatrixAni	= 0x08  /*!< Matrix animation */
};


/*!****************************************************************************
 @Struct      EPVRTDataType
 @Brief       Enum for the POD format data types
******************************************************************************/
enum EPVRTDataType 
{
    EPODDataNone,
    EPODDataFloat,
    EPODDataInt,
    EPODDataUnsignedShort,
    EPODDataRGBA,
    EPODDataARGB,
    EPODDataD3DCOLOR,
    EPODDataUBYTE4,
    EPODDataDEC3N,
    EPODDataFixed16_16,
    EPODDataUnsignedByte,
    EPODDataShort,
    EPODDataShortNorm,
    EPODDataByte,
    EPODDataByteNorm
};


/*!***************************************************************************
 Handles a batch of bones
*****************************************************************************/
class CPVRTBoneBatches
{
public:
    int	*pnBatches;			/*!< Space for nBatchBoneMax bone indices, per batch */
    int	*pnBatchBoneCnt;	/*!< Actual number of bone indices, per batch */
    int	*pnBatchOffset;		/*!< Offset into triangle array, per batch */
    int nBatchBoneMax;		/*!< Stored value as was passed into Create() */
    int	nBatchCnt;			/*!< Number of batches to render */

public:

    /*!***********************************************************************
     @Function		Release
     @Description	Destroy the bone batch structure
    *************************************************************************/
    void Release()
    {
        { delete pnBatches;			pnBatches = 0; }
        { delete pnBatchBoneCnt;	pnBatchBoneCnt = 0; }
        { delete pnBatchOffset;		pnBatchOffset = 0; }
        nBatchCnt = 0;
    }
};


/*!****************************************************************************
 @Class      CPODData
 @Brief      A class for representing POD data
******************************************************************************/
class CPODData 
{
public:
    /*!***************************************************************************
     @Function			Reset
     @Description		Resets the POD Data to NULL
    *****************************************************************************/
    void Reset();

public:
    EPVRTDataType	eType;		/*!< Type of data stored */
    unsigned int	n;			/*!< Number of values per vertex */
    unsigned int	nStride;	/*!< Distance in bytes from one array entry to the next */
    unsigned char	*pData;		/*!< Actual data (array of values); if mesh is interleaved, this is an OFFSET from pInterleaved */
};


/*!****************************************************************************
 @Struct      SPODCamera
 @Brief       Struct for storing POD camera data
******************************************************************************/
struct SPODCamera 
{
    int			nIdxTarget;			/*!< Index of the target object */
    float	fFOV;				/*!< Field of view */
    float	fFar;				/*!< Far clip plane */
    float	fNear;				/*!< Near clip plane */
    float	*pfAnimFOV;			/*!< 1 float per frame of animation. */
};


/*!****************************************************************************
 @Struct      SPODLight
 @Brief       Struct for storing POD light data
******************************************************************************/
struct SPODLight 
{
    int			nIdxTarget;		/*!< Index of the target object */
    float	pfColour[3];	/*!< Light colour (0.0f -> 1.0f for each channel) */
    EPODLight	eType;			/*!< Light type (point, directional etc.) */
};


/*!****************************************************************************
 @Struct      SPODMesh
 @Brief       Struct for storing POD mesh data
******************************************************************************/
struct SPODMesh 
{
    unsigned int		nNumVertex;		/*!< Number of vertices in the mesh */
    unsigned int		nNumFaces;		/*!< Number of triangles in the mesh */
    unsigned int		nNumUVW;		/*!< Number of texture coordinate channels per vertex */
    CPODData			sFaces;			/*!< List of triangle indices */
    unsigned int		*pnStripLength;	/*!< If mesh is stripped: number of tris per strip. */
    unsigned int		nNumStrips;		/*!< If mesh is stripped: number of strips, length of pnStripLength array. */
    CPODData			sVertex;		/*!< List of vertices (x0, y0, z0, x1, y1, z1, x2, etc...) */
    CPODData			sNormals;		/*!< List of vertex normals (Nx0, Ny0, Nz0, Nx1, Ny1, Nz1, Nx2, etc...) */
    CPODData			sTangents;		/*!< List of vertex tangents (Tx0, Ty0, Tz0, Tx1, Ty1, Tz1, Tx2, etc...) */
    CPODData			sBinormals;		/*!< List of vertex binormals (Bx0, By0, Bz0, Bx1, By1, Bz1, Bx2, etc...) */
    CPODData			*psUVW;			/*!< List of UVW coordinate sets; size of array given by 'nNumUVW' */
    CPODData			sVtxColours;	/*!< A colour per vertex */
    CPODData			sBoneIdx;		/*!< nNumBones*nNumVertex ints (Vtx0Idx0, Vtx0Idx1, ... Vtx1Idx0, Vtx1Idx1, ...) */
    CPODData			sBoneWeight;	/*!< nNumBones*nNumVertex floats (Vtx0Wt0, Vtx0Wt1, ... Vtx1Wt0, Vtx1Wt1, ...) */
    unsigned char		*pInterleaved;	/*!< Interleaved vertex data */
    CPVRTBoneBatches	sBoneBatches;	/*!< Bone tables */
    EPODPrimitiveType	ePrimitiveType;	/*!< Primitive type used by this mesh */
};


/*!****************************************************************************
 @Struct      SPODNode
 @Brief       Struct for storing POD node data
******************************************************************************/
struct SPODNode 
{
    int			nIdx;				/*!< Index into mesh, light or camera array, depending on which object list contains this Node */
    char		*pszName;			/*!< Name of object */
    int			nIdxMaterial;		/*!< Index of material used on this mesh */
    int			nIdxParent;			/*!< Index into MeshInstance array; recursively apply ancestor's transforms after this instance's. */
    unsigned int nAnimFlags;		/*!< Stores which animation arrays the POD Node contains */
    float	*pfAnimPosition;	/*!< 3 floats per frame of animation. */
    float	*pfAnimRotation;	/*!< 4 floats per frame of animation. */
    float	*pfAnimScale;		/*!< 7 floats per frame of animation. */
    float	*pfAnimMatrix;		/*!< 16 floats per frame of animation. */
};


/*!****************************************************************************
 @Struct      SPODTexture
 @Brief       Struct for storing POD texture data
******************************************************************************/
struct SPODTexture 
{
    char	*pszName;			/*!< File-name of texture */
};


/*!****************************************************************************
 @Struct      SPODMaterial
 @Brief       Struct for storing POD material data
******************************************************************************/
struct SPODMaterial 
{
    char		*pszName;			/*!< Name of material */
    int			nIdxTexDiffuse;		/*!< Idx into textures for diffuse texture */
    float	fMatOpacity;		/*!< Material opacity (used with vertex alpha ?) */
    float	pfMatAmbient[3];	/*!< Ambient RGB value */
    float	pfMatDiffuse[3];	/*!< Diffuse RGB value */
    float	pfMatSpecular[3];	/*!< Specular RGB value */
    float	fMatShininess;		/*!< Material shininess */
    char		*pszEffectFile;		/*!< Name of effect file */
    char		*pszEffectName;		/*!< Name of effect in the effect file */
};


/*!****************************************************************************
 @Struct      SPODScene
 @Brief       Struct for storing POD scene data
******************************************************************************/
struct SPODScene 
{
    float	pfColourBackground[3];	/*!< Background colour */
    float	pfColourAmbient[3];		/*!< Ambient colour */

    unsigned int	nNumCamera;			/*!< The length of the array pCamera */
    SPODCamera		*pCamera;			/*!< Camera nodes array */

    unsigned int	nNumLight;			/*!< The length of the array pLight */
    SPODLight		*pLight;			/*!< Light nodes array */

    unsigned int	nNumMesh;			/*!< The length of the array pMesh */
    SPODMesh		*pMesh;				/*!< Mesh array. Meshes may be instanced several times in a scene; i.e. multiple Nodes may reference any given mesh. */

    unsigned int	nNumNode;		    /*!< Number of items in the array pNode */
    unsigned int	nNumMeshNode;	    /*!< Number of items in the array pNode which are objects */
    SPODNode		*pNode;			    /*!< Node array. Sorted as such: objects, lights, cameras, Everything Else (bones, helpers etc) */

    unsigned int	nNumTexture;	    /*!< Number of textures in the array pTexture */
    SPODTexture		*pTexture;		    /*!< Texture array */

    unsigned int	nNumMaterial;	    /*!< Number of materials in the array pMaterial */
    SPODMaterial	*pMaterial;		    /*!< Material array */

    unsigned int	nNumFrame;		    /*!< Number of frames of animation */
    unsigned int	nFlags;			    /*!< PVRTMODELPODSF_* bit-flags */

    bool bBigEndian;				    /*!< bool to say if the scene is big endian or not */
};


struct SPVRTPODImpl;	// Internal implementation data


/*!***************************************************************************
 @Class CPVRTModelPOD
 @Brief A class for loading and storing data from POD files/headers
*****************************************************************************/
class CPVRTModelPOD : public SPODScene
{
public:
    /*!***************************************************************************
     @Function		Constructor
     @Description	Constructor for CPVRTModelPOD class
    *****************************************************************************/
    CPVRTModelPOD();

    /*!***************************************************************************
     @Function		Destructor
     @Description	Destructor for CPVRTModelPOD class
    *****************************************************************************/
    ~CPVRTModelPOD();

    /*!***************************************************************************
     @Function		ReadFromFile
     @Input			pszFileName		Filename to load
     @Output		pszExpOpt		String in which to place exporter options
     @Input			count			Maximum number of characters to store.
     @Return		PVR_SUCCESS if successful, PVR_FAIL if not
     @Description	Loads the specified ".POD" file; returns the scene in
                    pScene. This structure must later be destroyed with
                    PVRTModelPODDestroy() to prevent memory leaks.
                    ".POD" files are exported from 3D Studio MAX using a
                    PowerVR plugin.
                    If pszExpOpt is NULL, the scene is loaded; otherwise the
                    scene is not loaded and pszExpOpt is filled in.
    *****************************************************************************/
    bool ReadFromFile(
        const char		* const pszFileName,
        char			* const pszExpOpt = NULL,
        const size_t	count = 0);

    /*!***********************************************************************
     @Function		InitImpl
     @Description	Used by the Read*() fns to initialise implementation
                    details. Should also be called by applications which
                    manually build data in the POD structures for rendering;
                    in this case call it after the data has been created.
                    Otherwise, do not call this function.
    *************************************************************************/
    bool InitImpl();

    /*!***********************************************************************
     @Function		FlushCache
     @Description	Clears the matrix cache; use this if necessary when you
                    edit the position or animation of a node.
    *************************************************************************/
    void FlushCache();

    /*!***************************************************************************
     @Function		Destroy
     @Description	Frees the memory allocated to store the scene in pScene.
    *****************************************************************************/
    void Destroy();

    /*!***************************************************************************
     @Function		SetFrame
     @Input			fFrame			Frame number
     @Description	Set the animation frame for which subsequent Get*() calls
                    should return data.
    *****************************************************************************/
    void SetFrame(const float fFrame);

    /*!***************************************************************************
     @Function		GetRotationMatrix
     @Output		mOut			Rotation matrix
     @Input			node			Node to get the rotation matrix from
     @Description	Generates the world matrix for the given Mesh Instance;
                    applies the parent's transform too. Uses animation data.
    *****************************************************************************/
    void GetRotationMatrix(MATRIX &mOut, const SPODNode &node) const;

    /*!***************************************************************************
     @Function		GetRotationMatrix
     @Input			node			Node to get the rotation matrix from
     @Returns		Rotation matrix
     @Description	Generates the world matrix for the given Mesh Instance;
                    applies the parent's transform too. Uses animation data.
    *****************************************************************************/
    MATRIX GetRotationMatrix(const SPODNode	&node) const;

    /*!***************************************************************************
     @Function		GetScalingMatrix
     @Output		mOut			Scaling matrix
     @Input			node			Node to get the rotation matrix from
     @Description	Generates the world matrix for the given Mesh Instance;
                    applies the parent's transform too. Uses animation data.
    *****************************************************************************/
    void GetScalingMatrix(MATRIX &mOut, const SPODNode &node) const;

    /*!***************************************************************************
     @Function		GetScalingMatrix
     @Input			node			Node to get the rotation matrix from
     @Returns		Scaling matrix
     @Description	Generates the world matrix for the given Mesh Instance;
                    applies the parent's transform too. Uses animation data.
    *****************************************************************************/
    MATRIX GetScalingMatrix(const SPODNode &node) const;

    /*!***************************************************************************
     @Function		GetTranslation
     @Output		V				Translation vector
     @Input			node			Node to get the translation vector from
     @Description	Generates the translation vector for the given Mesh
                    Instance. Uses animation data.
    *****************************************************************************/
    void GetTranslation(VECTOR3 &V, const SPODNode& node) const;

    /*!***************************************************************************
     @Function		GetTranslation
     @Input			node			Node to get the translation vector from
     @Returns		Translation vector
     @Description	Generates the translation vector for the given Mesh
                    Instance. Uses animation data.
    *****************************************************************************/
    VECTOR3 GetTranslation(const SPODNode &node) const;

    /*!***************************************************************************
     @Function		GetTranslationMatrix
     @Output		mOut			Translation matrix
     @Input			node			Node to get the translation matrix from
     @Description	Generates the world matrix for the given Mesh Instance;
                    applies the parent's transform too. Uses animation data.
    *****************************************************************************/
    void GetTranslationMatrix( MATRIX &mOut, const SPODNode &node) const;

    /*!***************************************************************************
     @Function		GetTranslationMatrix
     @Input			node			Node to get the translation matrix from
     @Returns		Translation matrix
     @Description	Generates the world matrix for the given Mesh Instance;
                    applies the parent's transform too. Uses animation data.
    *****************************************************************************/
    MATRIX GetTranslationMatrix(const SPODNode	&node) const;

    /*!***************************************************************************
     @Function		GetTransformationMatrix
     @Output		mOut			Transformation matrix
     @Input			node			Node to get the transformation matrix from
     @Description	Generates the world matrix for the given Mesh Instance;
                    applies the parent's transform too. Uses animation data.
    *****************************************************************************/
    void GetTransformationMatrix(MATRIX &mOut, const SPODNode &node) const;

    /*!***************************************************************************
     @Function		GetWorldMatrixNoCache
     @Output		mOut			World matrix
     @Input			node			Node to get the world matrix from
     @Description	Generates the world matrix for the given Mesh Instance;
                    applies the parent's transform too. Uses animation data.
    *****************************************************************************/
    void GetWorldMatrixNoCache(MATRIX &mOut, const SPODNode &node) const;

    /*!***************************************************************************
     @Function		GetWorldMatrixNoCache
     @Input			node			Node to get the world matrix from
     @Returns		World matrix
     @Description	Generates the world matrix for the given Mesh Instance;
                    applies the parent's transform too. Uses animation data.
    *****************************************************************************/
    MATRIX GetWorldMatrixNoCache(const SPODNode &node) const;

    /*!***************************************************************************
     @Function		GetWorldMatrix
     @Output		mOut			World matrix
     @Input			node			Node to get the world matrix from
     @Description	Generates the world matrix for the given Mesh Instance;
                    applies the parent's transform too. Uses animation data.
    *****************************************************************************/
    void GetWorldMatrix( MATRIX	&mOut, const SPODNode &node) const;

    /*!***************************************************************************
     @Function		GetWorldMatrix
     @Input			node			Node to get the world matrix from
     @Returns		World matrix
     @Description	Generates the world matrix for the given Mesh Instance;
                    applies the parent's transform too. Uses animation data.
    *****************************************************************************/
    MATRIX GetWorldMatrix(const SPODNode& node) const;

    /*!***************************************************************************
     @Function		GetBoneWorldMatrix
     @Output		mOut			Bone world matrix
     @Input			NodeMesh		Mesh to take the bone matrix from
     @Input			NodeBone		Bone to take the matrix from
     @Description	Generates the world matrix for the given bone.
    *****************************************************************************/
    void GetBoneWorldMatrix(
        MATRIX		&mOut,
        const SPODNode	&NodeMesh,
        const SPODNode	&NodeBone);

    /*!***************************************************************************
     @Function		GetBoneWorldMatrix
     @Input			NodeMesh		Mesh to take the bone matrix from
     @Input			NodeBone		Bone to take the matrix from
     @Returns		Bone world matrix
     @Description	Generates the world matrix for the given bone.
    *****************************************************************************/
    MATRIX GetBoneWorldMatrix(
        const SPODNode	&NodeMesh,
        const SPODNode	&NodeBone);

    /*!***************************************************************************
     @Function		GetCamera
     @Output		vFrom			Position of the camera
     @Output		vTo				Target of the camera
     @Output		vUp				Up direction of the camera
     @Input			nIdx			Camera number
     @Return		Camera horizontal FOV
     @Description	Calculate the From, To and Up vectors for the given
                    camera. Uses animation data.
                    Note that even if the camera has a target, *pvTo is not
                    the position of that target. *pvTo is a position in the
                    correct direction of the target, one unit away from the camera.
    *****************************************************************************/
    float GetCamera(
        VECTOR3			&vFrom,
        VECTOR3			&vTo,
        VECTOR3			&vUp,
        const unsigned int	nIdx) const;

    /*!***************************************************************************
     @Function		GetCameraPos
     @Output		vFrom			Position of the camera
     @Output		vTo				Target of the camera
     @Input			nIdx			Camera number
     @Return		Camera horizontal FOV
     @Description	Calculate the position of the camera and its target. Uses
                    animation data.
                    If the queried camera does not have a target, *pvTo is
                    not changed.
    *****************************************************************************/
    float GetCameraPos(
        VECTOR3			&vFrom,
        VECTOR3			&vTo,
        const unsigned int	nIdx) const;

    /*!***************************************************************************
     @Function		GetLight
     @Output		vPos			Position of the light
     @Output		vDir			Direction of the light
     @Input			nIdx			Light number
     @Description	Calculate the position and direction of the given Light.
                    Uses animation data.
    *****************************************************************************/
    void GetLight(
        VECTOR3			&vPos,
        VECTOR3			&vDir,
        const unsigned int	nIdx) const;

    /*!***************************************************************************
     @Function		GetLightPosition
     @Input			u32Idx			Light number
     @Return		VECTOR4         position of light with w set correctly
     @Description	Calculate the position the given Light. Uses animation data.
    *****************************************************************************/
    Vec4 GetLightPosition(const unsigned int u32Idx) const;

    /*!***************************************************************************
     @Function		GetLightDirection
     @Input			u32Idx			Light number
     @Return		VECTOR4         direction of light with w set correctly
     @Description	Calculate the direction of the given Light. Uses animation data.
    *****************************************************************************/
    Vec4 GetLightDirection(const unsigned int u32Idx) const;

    /*!***************************************************************************
     @Function		CreateSkinIdxWeight
     @Output		pIdx				Four bytes containing matrix indices for vertex (0..255)
     @Output		pWeight				Four bytes containing blend weights for vertex (0.0 .. 1.0)
     @Input			nVertexBones		Number of bones this vertex uses
     @Input			pnBoneIdx			Pointer to 'nVertexBones' indices
     @Input			pfBoneWeight		Pointer to 'nVertexBones' blend weights
     @Description	Creates the matrix indices and blend weights for a boned
                    vertex. Call once per vertex of a boned mesh.
    *****************************************************************************/
    bool CreateSkinIdxWeight(
        char			* const pIdx,
        char			* const pWeight,
        const int		nVertexBones,
        const int		* const pnBoneIdx,
        const float	* const pfBoneWeight);

private:
    SPVRTPODImpl	*m_pImpl;	/*!< Internal implementation data */
};


/*!***************************************************************************
 @Function		PVRTModelPODDataTypeSize
 @Input			type		Type to get the size of
 @Return		Size of the data element
 @Description	Returns the size of each data element.
*****************************************************************************/
size_t PVRTModelPODDataTypeSize(const EPVRTDataType type);


/*!***************************************************************************
 @Function		PVRTModelPODDataTypeComponentCount
 @Input			type		Type to get the number of components from
 @Return		number of components in the data element
 @Description	Returns the number of components in a data element.
*****************************************************************************/
size_t PVRTModelPODDataTypeComponentCount(const EPVRTDataType type);


/*!***************************************************************************
 @Function		PVRTModelPODDataStride
 @Input			data		Data elements
 @Return		Size of the vector elements
 @Description	Returns the size of the vector of data elements.
*****************************************************************************/
size_t PVRTModelPODDataStride(const CPODData &data);


/*!***************************************************************************
 @Function		PVRTModelPODCountIndices
 @Input			mesh		Mesh
 @Return		Number of indices used by mesh
 @Description	Counts the number of indices of a mesh
*****************************************************************************/
unsigned int PVRTModelPODCountIndices(const SPODMesh &mesh);


#endif
