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

    // set clear color.
    virtual void SetClearColor (const OGVec4& _vColor);

    // set fog state.
    virtual void EnableFog (bool _bEnable);

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
    virtual IOGVertexBuffers* CreateDynVertexBuffer (unsigned int _NumFaces);

    // get model matrix.
    virtual void GetModelMatrix (OGMatrix& _mModel);

    // get view matrix.
    virtual void GetViewMatrix (OGMatrix& _mView);

    // get projection matrix.
    virtual void GetProjectionMatrix (OGMatrix& _mProjection);

    // add render job.
    virtual void RenderStatic (
        IOGTexture* _pTexture,
        IOGMaterial* _pMaterial,
        IOGVertexBuffers* _pMesh,
        OGMatrix _mTransform,
        OGBlendType _Blend,
        OGShaderID _ShaderID,
        OGRenderPass _Pass);

    // add render job.
    virtual void RenderEffect (
        IOGTexture* _pTexture,
        IOGVertexBuffers* _pMesh,
        OGBlendType _Blend,
        OGShaderID _ShaderID,
        OGRenderPass _Pass);

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

    // Draw scene.
    virtual void DrawScene ();

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
            EffectObjs.reserve(64);
            m_pCamera = NULL;
        }

        void Clear()
        {
            OpaqueObjs.clear();
            AlphaTestObjs.clear();
            BlendedObjs.clear();
            EffectObjs.clear();
        }

        std::vector<RenderJob>  OpaqueObjs;
        std::vector<RenderJob>  AlphaTestObjs;
        std::vector<RenderJob>  BlendedObjs;
        std::vector<RenderJob>  EffectObjs;

        OGMatrix                m_mView;
        OGMatrix                m_mProjection;
        IOGCamera*              m_pCamera;
    };

    // do actual rendering here
    void FlushRenderQueue();

    // do rendering of the particular mesh
    void DoRenderJob(const RenderJob& _rj, RenderQueue* _pQueue);

    // set current blend mode
    void SetBlend(OGBlendType _blend);

protected:

    IOGTexture*         m_pCurTexture;
    IOGMaterial*        m_pCurMaterial;
    IOGVertexBuffers*   m_pCurMesh;
    IOGShader*          m_pCurShader;
    OGBlendType         m_CurBlend;

    IOGStatistics*      m_pStats;
    IOGShaderManager*   m_pShaderMgr;
    IOGFog*             m_pFog;
    IOGLightMgr*        m_pLightMgr;
    IOGCamera*          m_pCamera;
    COGTextRenderer*    m_pText;
    COGRenderTarget*    m_pShadowMapRT;
    OGMatrix            m_mOrthoProj;
    OGMatrix            m_mProjection;
    OGMatrix            m_mTextProj;
    OGMatrix            m_mView;
    OGMatrix            m_mWorld;
    OGVec4              m_vClearColor;
    bool                m_bFogEnabled;

    unsigned int        m_Width; 
    unsigned int        m_Height;
    float               m_fZNear;
    float               m_fZFar;
    float               m_fFOV;
    bool                m_bLandscapeMode;

    RenderQueue         m_SceneQueue;
    RenderQueue         m_ShadowMapQueue;
};

#endif
