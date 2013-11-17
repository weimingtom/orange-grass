/*
*  ogrenderer.h
*  OrangeGrass
*
*  Created by Viacheslav Bogdanov on 07.11.09.
*  Copyright 2009 __MyCompanyName__. All rights reserved.
*
*/
#ifndef OGRENDERER_H_
#define OGRENDERER_H_

#include "IOGRenderer.h"
#include "IOGStatistics.h"
#include "IOGShaderManager.h"
#include "ogmesh.h"
#include "ogrendertarget.h"
#include "ogtextrenderer.h"
#include "ogrendertarget.h"

#include <string>
#include <map>


class COGRenderer : public IOGRenderer
{
public:
    COGRenderer ();
    virtual ~COGRenderer ();

    // initialize renderer.
    virtual bool Init ();

    // set viewport.
    virtual void SetViewport (
        unsigned int _Width, 
        unsigned int _Height,
        float _fZNear,
        float _fZFar,
        float _fFOV);

    // Create vertex buffer for mesh.
    virtual IOGVertexBuffers* CreateVertexBuffer (
        const void* _pVertexData, 
        unsigned int _NumVertices, 
        unsigned int _NumFaces, 
        unsigned int _Stride, 
        const void* _pIndexData, 
        unsigned int _NumIndices);

    // Create vertex buffer for effects.
    virtual IOGDynVertexBuffers* CreateDynVertexBuffer (unsigned int _NumVertices);

    // add rendering command.
    virtual void SetTexture (IOGTexture* _pTexture);

    // add rendering command.
    virtual void SetMaterial (IOGMaterial* _pMaterial);

    // add rendering command.
    virtual void SetBlend (OGBlendType _Blend);

    // set model matrix.
    virtual void SetModelMatrix (const OGMatrix& _mModel);

    // set view matrix.
    virtual void SetViewMatrix (const OGMatrix& _mView);

    // get model matrix.
    virtual void GetModelMatrix (OGMatrix& _mModel);

    // get view matrix.
    virtual void GetViewMatrix (OGMatrix& _mView);

    // get projection matrix.
    virtual void GetProjectionMatrix (OGMatrix& _mProjection);

    // Enable scene light.
    virtual void EnableLight (bool _bEnable);

    // Enable scene fog.
    virtual void EnableFog (bool _bEnable);

    // Enable color channel.
    virtual void EnableColor (bool _bEnable);

    // start rendering mode.
    virtual void StartRenderMode(OGRenderMode _Mode);

    // finish rendering mode.
    virtual void FinishRenderMode();

    // add render job.
    virtual void RenderStatic (
        IOGTexture* _pTexture,
        IOGMaterial* _pMaterial,
        IOGVertexBuffers* _pMesh,
        OGMatrix _mTransform,
        OGBlendType _Blend,
        OGShaderID _ShaderID);

    // clear frame buffer with the given color
    virtual void ClearFrame (const OGVec4& _vClearColor);

    // Create material.
    virtual IOGMaterial* CreateMaterial ();

    // Get scene light.
    virtual IOGLightMgr* GetLightMgr ();

    // Get main camera.
    virtual IOGCamera* GetCamera ();

    // Get fog.
    virtual IOGFog* GetFog ();

    // reset renderer pipeline.
    virtual void Reset ();

    // Unproject screen coords.
    virtual OGVec3 UnprojectCoords (int _X, int _Y);

    // Display string.
    virtual void DisplayString (
        const OGVec2& _vPos, 
        float _fScale, 
        unsigned int Colour, 
        const char * const pszFormat, ...);

    // Draw effects buffer.
    virtual void DrawEffectBuffer (void* _pBuffer, int _StartId, int _NumVertices);

    // Draw sprite buffer.
    virtual void DrawSpriteBuffer (void* _pBuffer, int _StartId, int _NumVertices);

    // Draw render target.
    virtual void DrawRT ();

    // Debug - insert event marker.
    virtual void InsertEventMarker (const std::string& _MarkerStr);

    // Debug - push group marker.
    virtual void PushGroupMarker (const std::string& _MarkerStr);

    // Debug - pop group marker.
    virtual void PopGroupMarker ();

    // Debug - label object.
    virtual void LabelObject (unsigned int _ObjType, unsigned int _ObjId, const std::string& _ObjLabelStr);

protected:

    struct RenderJob
    {
        RenderJob()
            : pTexture(NULL)
            , pMaterial(NULL)
            , pMesh(NULL)
            , Blend(OG_BLEND_NO)
            , ShaderID(OG_SHADER_NO)
        {}

        IOGTexture*         pTexture;
        IOGMaterial*        pMaterial;
        IOGVertexBuffers*   pMesh;
        OGMatrix            mTransform;
        OGBlendType         Blend;
        OGShaderID          ShaderID;
    };

    struct RenderQueue
    {
        RenderQueue()
        {
            OpaqueObjs.reserve(64);
            AlphaTestObjs.reserve(64);
            BlendedObjs.reserve(64);
        }

        std::vector<RenderJob>  OpaqueObjs;
        std::vector<RenderJob>  AlphaTestObjs;
        std::vector<RenderJob>  BlendedObjs;
    };

    // do actual rendering here
    void FlushRenderQueue();

    // do rendering of the particular mesh
    void DoRenderJob(const RenderJob& _rj);

protected:

    IOGTexture*         m_pCurTexture;
    IOGMaterial*        m_pCurMaterial;
    IOGVertexBuffers*   m_pCurMesh;
    OGBlendType         m_CurBlend;
    IOGStatistics*      m_pStats;
    IOGShaderManager*   m_pShaderMgr;
    IOGFog*             m_pFog;
    IOGLightMgr*        m_pLightMgr;
    IOGCamera*          m_pCamera;
    COGTextRenderer*    m_pText;
    COGRenderTarget*    m_pRT;
    OGMatrix            m_mOrthoProj;
    OGMatrix            m_mProjection;
    OGMatrix            m_mTextProj;
    OGMatrix            m_mView;
    unsigned int        m_Width; 
    unsigned int        m_Height;
    float               m_fZNear;
    float               m_fZFar;
    float               m_fFOV;
    bool                m_bLandscapeMode;
    OGRenderMode        m_Mode;

    OGMatrix            m_mWorld;
    bool                m_bLightEnabled;
    bool                m_bFogEnabled;

    IOGShader*          m_pCurShader;

    RenderQueue         m_RenderQueue;
};

#endif
