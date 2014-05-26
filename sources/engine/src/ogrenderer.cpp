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
#include "OpenGL2.h"
#include "OrangeGrass.h"
#include "ogrenderer.h"
#include "oglight.h"
#include "ogcamera.h"
#include "ogfog.h"
#include "ogmaterial.h"
#include "ogsprite.h"
#include "ogvertexbuffers.h"
#include "ogdynvertexbuffers.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifdef __ANDROID_API__
typedef void (GL_APIENTRYP PFNGLLABELOBJECTEXTPROC) (GLenum type, GLuint object, GLsizei length, const GLchar *label);
typedef void (GL_APIENTRYP PFNGLGETOBJECTLABELEXTPROC) (GLenum type, GLuint object, GLsizei bufSize, GLsizei *length, GLchar *label);
typedef void (GL_APIENTRYP PFNGLINSERTEVENTMARKEREXTPROC) (GLsizei length, const GLchar *marker);
typedef void (GL_APIENTRYP PFNGLPUSHGROUPMARKEREXTPROC) (GLsizei length, const GLchar *marker);
typedef void (GL_APIENTRYP PFNGLPOPGROUPMARKEREXTPROC) (void);

PFNGLINSERTEVENTMARKEREXTPROC glInsertEventMarkerEXT; 
PFNGLPUSHGROUPMARKEREXTPROC glPushGroupMarkerEXT; 
PFNGLPOPGROUPMARKEREXTPROC glPopGroupMarkerEXT;
PFNGLLABELOBJECTEXTPROC glLabelObjectEXT;
PFNGLGETOBJECTLABELEXTPROC glGetObjectLabelEXT;
#endif

#ifdef __cplusplus
}
#endif


COGRenderer::COGRenderer () :   m_pCurTexture(NULL),
                                m_pCurMaterial(NULL),
                                m_pCurMesh(NULL),
                                m_pCurShader(NULL),
                                m_CurBlend(OG_BLEND_NO),
                                m_pFog(NULL),
                                m_pLightMgr(NULL),
                                m_pCamera(NULL),
                                m_pText(NULL),
                                m_pShadowMapRT(NULL),
                                m_bFogEnabled(false),
                                m_bLandscapeMode(false)
{
    m_pStats = GetStatistics();
    m_pShaderMgr = GetShaderManager();
}


COGRenderer::~COGRenderer ()
{
    m_pShaderMgr->Destroy();

    OG_SAFE_DELETE(m_pText);
    OG_SAFE_DELETE(m_pShadowMapRT);
    OG_SAFE_DELETE(m_pFog);
    OG_SAFE_DELETE(m_pLightMgr);
    OG_SAFE_DELETE(m_pCamera);
}


// initialize renderer.
bool COGRenderer::Init ()
{
#ifdef __ANDROID_API__
    glInsertEventMarkerEXT = (PFNGLINSERTEVENTMARKEREXTPROC) eglGetProcAddress("glInsertEventMarkerEXT");
    glPushGroupMarkerEXT = (PFNGLPUSHGROUPMARKEREXTPROC) eglGetProcAddress("glPushGroupMarkerEXT");
    glPopGroupMarkerEXT = (PFNGLPOPGROUPMARKEREXTPROC) eglGetProcAddress("glPopGroupMarkerEXT");
    glLabelObjectEXT = (PFNGLLABELOBJECTEXTPROC) eglGetProcAddress("glLabelObjectEXT");
    glGetObjectLabelEXT = (PFNGLGETOBJECTLABELEXTPROC) eglGetProcAddress("glGetObjectLabelEXT");
#endif

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    Reset();

    m_pLightMgr = new COGLightMgr ();
    m_pCamera = new COGCamera ();
    m_pFog = new COGFog ();
    m_pText = new COGTextRenderer();
    if (!m_pShaderMgr->Init())
        return false;
    return true;
}

// set clear color.
void COGRenderer::SetClearColor (const OGVec4& _vColor)
{
    m_vClearColor = _vColor;
    glClearColor(m_vClearColor.x, m_vClearColor.y, m_vClearColor.z, m_vClearColor.w);
}


// set fog state.
void COGRenderer::EnableFog (bool _bEnable)
{
    m_bFogEnabled = _bEnable;
}


// set viewport.
void COGRenderer::SetViewport (
    unsigned int _Width, 
    unsigned int _Height,
    float _fZNear,
    float _fZFar,
    float _fFOV )
{
    m_Width = _Width;
    m_Height = _Height;
    m_fFOV = _fFOV;
    m_fZNear = _fZNear;
    m_fZFar = _fZFar;

    for(int i=0; i<16; i++){m_mTextProj.f[i]=0;}
    m_mTextProj.f[10] = 1.0f; m_mTextProj.f[12] = -1.0f;
    m_mTextProj.f[13] = 1.0f; m_mTextProj.f[15] = 1.0f;

    m_bLandscapeMode = (GetGlobalVars()->GetIVar("landscape") == 1);

#ifndef WIN32
    if (m_bLandscapeMode)
    {
        MatrixOrthoRH(m_mOrthoProj, (float)m_Height, (float)m_Width, -1, 1, true);
        MatrixPerspectiveFovRH(m_mProjection, m_fFOV, float(m_Height)/float(m_Width), m_fZNear, m_fZFar, true);
        m_pText->SetTextures(_Width, _Height, true);
        m_mTextProj.f[0] = 2.0f/(m_Height);
        m_mTextProj.f[5] = -2.0f/(m_Width);
    }
    else
#endif
    {
        MatrixOrthoRH(m_mOrthoProj, (float)m_Width, (float)m_Height, -1, 1, false);
        MatrixPerspectiveFovRH(m_mProjection, m_fFOV, float(m_Width)/float(m_Height), m_fZNear, m_fZFar, false);
        m_pText->SetTextures(_Width, _Height, false);
        m_mTextProj.f[0] = 2.0f/(m_Width);
        m_mTextProj.f[5] = -2.0f/(m_Height);
    }

    m_pCamera->SetupViewport(m_mProjection);
    m_pShadowMapRT = new COGRenderTarget();
    m_pShadowMapRT->Init(false, true, 512, 1024, 1);
}


// Create vertex buffer for mesh.
IOGVertexBuffers* COGRenderer::CreateVertexBuffer (
    const void* _pVertexData, 
    unsigned int _NumVertices, 
    unsigned int _NumFaces,
    unsigned int _Stride, 
    const void* _pIndexData, 
    unsigned int _NumIndices)
{
    return new COGVertexBuffers(_pVertexData, _NumVertices, _NumFaces, _Stride, _pIndexData, _NumIndices);
}


// Create vertex buffer for effects.
IOGVertexBuffers* COGRenderer::CreateDynVertexBuffer (unsigned int _NumFaces)
{
    return new COGDynVertexBuffers(_NumFaces);
}


// get model matrix.
void COGRenderer::GetModelMatrix (OGMatrix& _mModel)
{
    _mModel = m_mWorld;
}


// get view matrix.
void COGRenderer::GetViewMatrix (OGMatrix& _mView)
{
    _mView = m_mView;
}


// get projection matrix.
void COGRenderer::GetProjectionMatrix (OGMatrix& _mProjection)
{
    _mProjection = m_mProjection;
}


// add render job.
void COGRenderer::RenderStatic (
    IOGTexture* _pTexture,
    IOGMaterial* _pMaterial,
    IOGVertexBuffers* _pMesh,
    OGMatrix _mTransform,
    OGBlendType _Blend,
    OGShaderID _ShaderID,
    OGRenderPass _Pass)
{
    RenderQueue* pCurQueue = NULL;
    switch(_Pass)
    {
    case OG_RENDERPASS_SCENE:
        pCurQueue = &m_SceneQueue;
        break;

    case OG_RENDERPASS_SHADOWMAP:
        pCurQueue = &m_ShadowMapQueue;
        break;

    default:
        return;
    }

    std::vector<RenderJob>* pCurObjList = NULL;
    switch (_Blend)
    {
    case OG_BLEND_SOLID:
        pCurObjList = &pCurQueue->OpaqueObjs;
        break;

    case OG_BLEND_ALPHABLEND:
    case OG_BLEND_ALPHAADD:
    case OG_BLEND_ALPHAONE:
        pCurObjList = &pCurQueue->BlendedObjs;
        break;

    case OG_BLEND_ALPHATEST:
        pCurObjList = &pCurQueue->AlphaTestObjs;
        break;

    default:
        return;
    }

    RenderJob curJob;
    curJob.Blend = _Blend;
    curJob.mTransform = _mTransform;
    curJob.pTexture = _pTexture;
    curJob.pMaterial = _pMaterial;
    curJob.pMesh = _pMesh;
    curJob.ShaderID = _ShaderID;
    pCurObjList->push_back(curJob);
}


// add render job.
void COGRenderer::RenderEffect (
    IOGTexture* _pTexture,
    IOGVertexBuffers* _pMesh,
    OGBlendType _Blend,
    OGShaderID _ShaderID,
    OGRenderPass _Pass)
{
    RenderQueue* pCurQueue = NULL;
    switch(_Pass)
    {
    case OG_RENDERPASS_SCENE:
        pCurQueue = &m_SceneQueue;
        break;

    case OG_RENDERPASS_SHADOWMAP:
        pCurQueue = &m_ShadowMapQueue;
        break;

    default:
        return;
    }

    RenderJob curJob;
    curJob.Blend = _Blend;
    MatrixIdentity(curJob.mTransform);
    curJob.pTexture = _pTexture;
    curJob.pMaterial = NULL;
    curJob.pMesh = _pMesh;
    curJob.ShaderID = _ShaderID;
    pCurQueue->EffectObjs.push_back(curJob);
}


// Draw scene.
void COGRenderer::DrawScene ()
{
    m_mView = m_pCamera->GetViewMatrix();
    FlushRenderQueue();
    Reset();
}


// do actual rendering here
void COGRenderer::FlushRenderQueue()
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // Render shadow map
    if (m_pShadowMapRT->Begin())
    {
        m_ShadowMapQueue.m_mProjection = m_pLightMgr->GetGlobalLightProjMatrix();
        m_ShadowMapQueue.m_mView = m_pLightMgr->GetGlobalLightViewMatrix();
        m_ShadowMapQueue.m_pCamera = m_pLightMgr->GetLightCamera();

        m_pFog->SetEnabled(false);
        for (auto it = m_ShadowMapQueue.OpaqueObjs.begin(); it != m_ShadowMapQueue.OpaqueObjs.end(); ++it)
        {
            DoRenderJob(*it, &m_ShadowMapQueue);
        }
        for (auto it = m_ShadowMapQueue.AlphaTestObjs.begin(); it != m_ShadowMapQueue.AlphaTestObjs.end(); ++it)
        {
            DoRenderJob(*it, &m_ShadowMapQueue);
        }
        for (auto it = m_ShadowMapQueue.BlendedObjs.begin(); it != m_ShadowMapQueue.BlendedObjs.end(); ++it)
        {
            DoRenderJob(*it, &m_ShadowMapQueue);
        }
        m_pShadowMapRT->End();
    }
    m_ShadowMapQueue.Clear();

    // Rendering scene
    m_SceneQueue.m_mProjection = m_mProjection;
    m_SceneQueue.m_mView = m_mView;
    m_SceneQueue.m_pCamera = m_pCamera;

    glViewport(0, 0, m_Width, m_Height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_pShadowMapRT->GetDepthTextureId());
    glActiveTexture(GL_TEXTURE0);

    m_pFog->SetEnabled(m_bFogEnabled);

    for (auto it = m_SceneQueue.OpaqueObjs.begin(); it != m_SceneQueue.OpaqueObjs.end(); ++it)
    {
        DoRenderJob(*it, &m_SceneQueue);
    }
    for (auto it = m_SceneQueue.AlphaTestObjs.begin(); it != m_SceneQueue.AlphaTestObjs.end(); ++it)
    {
        DoRenderJob(*it, &m_SceneQueue);
    }
    for (auto it = m_SceneQueue.BlendedObjs.begin(); it != m_SceneQueue.BlendedObjs.end(); ++it)
    {
        DoRenderJob(*it, &m_SceneQueue);
    }

    m_pFog->SetEnabled(false);

    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    for (auto it = m_SceneQueue.EffectObjs.begin(); it != m_SceneQueue.EffectObjs.end(); ++it)
    {
        DoRenderJob(*it, &m_SceneQueue);
    }
    glEnable(GL_DEPTH_TEST);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    m_SceneQueue.Clear();

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE0);

    // Rendering text
    m_pCurShader = m_pShaderMgr->GetShader(OG_SHADER_TEXT);
    SetBlend(OG_BLEND_ALPHABLEND);
    m_pCurShader->SetProjectionMatrix(m_mTextProj);
    m_pCurShader->Setup();
    m_pText->Flush();
}


// do rendering of the particular mesh
void COGRenderer::DoRenderJob(const RenderJob& _rj, RenderQueue* _pQueue)
{
    if (!m_pCurShader || m_pCurShader->GetShaderID() != _rj.ShaderID)
    {
        m_pCurShader = m_pShaderMgr->GetShader(_rj.ShaderID);
        m_pCurShader->SetCamera(_pQueue->m_pCamera);
        m_pCurShader->SetProjectionMatrix(_pQueue->m_mProjection);
        m_pCurShader->SetViewMatrix(_pQueue->m_mView);
        m_pCurShader->SetLighting(m_pFog, m_pLightMgr);
        m_pCurShader->Setup();
    }

    if (_rj.pMesh != m_pCurMesh)
    {
        m_pCurMesh = _rj.pMesh;
        m_pCurMesh->Apply();
    }

    if (_rj.pMaterial != NULL)
    {
        m_pCurMaterial = _rj.pMaterial;
        m_pCurShader->SetMaterial(m_pCurMaterial);
    }

    if (_rj.pTexture != m_pCurTexture)
    {
        m_pCurTexture = _rj.pTexture;
        m_pCurTexture->Apply();
    }

    SetBlend(_rj.Blend);

    m_pCurShader->SetModelMatrix(_rj.mTransform);
    m_pCurShader->Apply();
    m_pCurMesh->Render();
}


// set current blend mode
void COGRenderer::SetBlend(OGBlendType _blend)
{
    if (m_CurBlend != _blend)
    {
        m_CurBlend = _blend;
        switch (m_CurBlend)
        {
        case OG_BLEND_NO:
            break;

        case OG_BLEND_SOLID:
            glDisable (GL_BLEND);
            m_pCurShader->EnableAlphaTest(false);
            break;

        case OG_BLEND_ALPHATEST:
            glDisable (GL_BLEND); 
            m_pCurShader->EnableAlphaTest(true);
            break;

        case OG_BLEND_ALPHABLEND:
            glEnable (GL_BLEND); 
            glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
            m_pCurShader->EnableAlphaTest(false);
            break;

        case OG_BLEND_ALPHAADD:
            glEnable (GL_BLEND); 
            glBlendFunc (GL_ONE, GL_ONE);
            m_pCurShader->EnableAlphaTest(false);
            break;

        case OG_BLEND_ALPHAONE:
            glEnable (GL_BLEND); 
            glBlendFunc (GL_SRC_ALPHA,GL_ONE);
            m_pCurShader->EnableAlphaTest(false);
            break;
        }
    }
}


// Get scene light.
IOGLightMgr* COGRenderer::GetLightMgr ()
{
    return m_pLightMgr;
}


// Get main camera.
IOGCamera* COGRenderer::GetCamera ()
{
    return m_pCamera;
}


// Get fog.
IOGFog* COGRenderer::GetFog ()
{
    return m_pFog;
}


// Create material.
IOGMaterial* COGRenderer::CreateMaterial ()
{
    return new COGMaterial();
}


// reset renderer pipeline.
void COGRenderer::Reset ()
{
    m_pCurTexture = NULL;
    m_pCurMaterial = NULL;
    m_pCurMesh = NULL;
    m_pCurShader = NULL;
    m_CurBlend = OG_BLEND_NO;
}


// Unproject screen coords.
OGVec3 COGRenderer::UnprojectCoords (int _X, int _Y)
{
    OGVec3 vOut;
#ifdef WIN32
    UnProject(_X, m_Height - _Y, 0, m_mView, m_mProjection, m_Width, m_Height, vOut);
#else
    if (m_bLandscapeMode)
    {
        UnProject(_Y, _X, 0, m_mView, m_mProjection, m_Height, m_Width, vOut);
    }
    else
    {
        UnProject(_X, m_Height - _Y, 0, m_mView, m_mProjection, m_Width, m_Height, vOut);
    }
#endif    
    return vOut;
}


// Display string.
void COGRenderer::DisplayString (const OGVec2& _vPos, 
    float _fScale, 
    unsigned int Colour, 
    const char * const pszFormat, ...)
{
    va_list args;
    static char Text[5120+1];
    va_start(args, pszFormat);
    vsprintf(Text, pszFormat, args);
    va_end(args);

    m_pText->DisplayText(_vPos.x,_vPos.y,_fScale, Colour, Text);
}


// Debug - insert event marker.
void COGRenderer::InsertEventMarker (const std::string& _MarkerStr)
{
#ifdef __ANDROID_API__
    if (glInsertEventMarkerEXT)
        glInsertEventMarkerEXT(_MarkerStr.size()+1, _MarkerStr.c_str());
#endif
}


// Debug - push group marker.
void COGRenderer::PushGroupMarker (const std::string& _MarkerStr)
{
#ifdef __ANDROID_API__
    if (glPushGroupMarkerEXT)
        glPushGroupMarkerEXT(_MarkerStr.size()+1, _MarkerStr.c_str());
#endif
}


// Debug - pop group marker.
void COGRenderer::PopGroupMarker ()
{
#ifdef __ANDROID_API__
    if (glPopGroupMarkerEXT)
        glPopGroupMarkerEXT();
#endif
}


// Debug - label object.
void COGRenderer::LabelObject (unsigned int _ObjType, unsigned int _ObjId, const std::string& _ObjLabelStr)
{
#ifdef __ANDROID_API__
    if (glLabelObjectEXT)
        glLabelObjectEXT(_ObjType, _ObjId, _ObjLabelStr.size()+1, _ObjLabelStr.c_str());
#endif
}
