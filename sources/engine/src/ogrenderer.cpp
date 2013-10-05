/*
 *  ogrenderer.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
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

#ifdef __cplusplus
extern "C" {
#endif
#ifndef WIN32
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

COGSprite::SprVert g_RTVertices[4];


COGRenderer::COGRenderer () :   m_pCurTexture(NULL),
                                m_pCurMaterial(NULL),
                                m_pCurMesh(NULL),
                                m_CurBlend(OG_BLEND_NO),
                                m_pFog(NULL),
                                m_pLightMgr(NULL),
                                m_pCamera(NULL),
                                m_pText(NULL),
                                m_pRT(NULL),
                                m_bLandscapeMode(false)
{
    m_bLightEnabled = false;
    m_bFogEnabled = false;

    m_pStats = GetStatistics();
    m_pShaderMgr = GetShaderManager();
}


COGRenderer::~COGRenderer ()
{
    m_pShaderMgr->Destroy();

    OG_SAFE_DELETE(m_pText);
    OG_SAFE_DELETE(m_pRT);
    OG_SAFE_DELETE(m_pFog);
    OG_SAFE_DELETE(m_pLightMgr);
    OG_SAFE_DELETE(m_pCamera);
}


// initialize renderer.
bool COGRenderer::Init ()
{
#ifndef WIN32
    glInsertEventMarkerEXT = (PFNGLINSERTEVENTMARKEREXTPROC) eglGetProcAddress("glInsertEventMarkerEXT");
    glPushGroupMarkerEXT = (PFNGLPUSHGROUPMARKEREXTPROC) eglGetProcAddress("glPushGroupMarkerEXT");
    glPopGroupMarkerEXT = (PFNGLPOPGROUPMARKEREXTPROC) eglGetProcAddress("glPopGroupMarkerEXT");
    glLabelObjectEXT = (PFNGLLABELOBJECTEXTPROC) eglGetProcAddress("glLabelObjectEXT");
    glGetObjectLabelEXT = (PFNGLGETOBJECTLABELEXTPROC) eglGetProcAddress("glGetObjectLabelEXT");
#endif

    glClearColor(0.3f, 0.3f, 0.4f, 1.0f);
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

    m_pCamera->SetupViewport(m_mProjection, m_fFOV);
    m_pRT = new COGRenderTarget();
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


// set model matrix.
void COGRenderer::SetModelMatrix (const OGMatrix& _mModel)
{
    m_mWorld = _mModel;
}


// set view matrix.
void COGRenderer::SetViewMatrix (const OGMatrix& _mView)
{
    m_mView = _mView;
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


// Enable scene light.
void COGRenderer::EnableLight (bool _bEnable)
{
    m_bLightEnabled = _bEnable;
}


// Enable scene fog.
void COGRenderer::EnableFog (bool _bEnable)
{
    m_pFog->SetEnabled(_bEnable);
}


// Enable color channel.
void COGRenderer::EnableColor (bool _bEnable)
{
    GLboolean enabled = _bEnable ? GL_TRUE : GL_FALSE;
    glColorMask(enabled, enabled, enabled, enabled);
}


// add rendering command.
void COGRenderer::SetTexture (IOGTexture* _pTexture)
{
    switch (m_Mode)
    {
    case OG_RENDERMODE_SHADOWEDSCENE:
        return;
    default:
        break;
    }

    if (_pTexture != m_pCurTexture)
    {
#ifdef STATISTICS
        m_pStats->AddTextureSwitch();
#endif
        m_pCurTexture = _pTexture;
        m_pCurTexture->Apply();
    }
}


// add rendering command.
void COGRenderer::SetMaterial (IOGMaterial* _pMaterial)
{
    switch (m_Mode)
    {
    case OG_RENDERMODE_SHADOWMAP:
    case OG_RENDERMODE_SHADOWEDSCENE:
        return;
    default:
        break;
    }

    if (_pMaterial != m_pCurMaterial)
    {
        m_pCurMaterial = _pMaterial;
        if(m_Mode == OG_RENDERMODE_GEOMETRY)
        {
            m_pCurShader->SetMaterial(m_pCurMaterial);
        }
        SetBlend(m_pCurMaterial->GetBlend());
    }
}


// add rendering command.
void COGRenderer::SetBlend (OGBlendType _Blend)
{
    switch (m_Mode)
    {
    case OG_RENDERMODE_SHADOWMAP:
    case OG_RENDERMODE_SHADOWEDSCENE:
        return;
    default:
        break;
    }

    if (m_CurBlend != _Blend)
    {
        m_CurBlend = _Blend;

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


// start rendering mode.
void COGRenderer::StartRenderMode(OGRenderMode _Mode)
{
    m_Mode = _Mode;
    switch(m_Mode)
    {
    case OG_RENDERMODE_GEOMETRY:
        m_pCurShader = m_pShaderMgr->GetShader(OG_SHADER_MODEL);
        glDisable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        SetViewMatrix(m_pCamera->GetViewMatrix());

        m_pCurShader->SetCamera(m_pCamera);
        m_pCurShader->SetProjectionMatrix(m_mProjection);
        m_pCurShader->SetViewMatrix(m_mView);
        m_pCurShader->SetLighting(m_pFog, m_pLightMgr);
        m_pCurShader->Setup();

        EnableLight(true);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        break;

    case OG_RENDERMODE_EFFECTS:
        m_pCurShader = m_pShaderMgr->GetShader(OG_SHADER_COLOREFFECT);
        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
        SetViewMatrix(m_pCamera->GetViewMatrix());

        m_pCurShader->SetCamera(m_pCamera);
        m_pCurShader->SetProjectionMatrix(m_mProjection);
        m_pCurShader->SetViewMatrix(m_mView);
        m_pCurShader->SetLighting(m_pFog, m_pLightMgr);
        m_pCurShader->Setup();

        EnableLight(false);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        break;

    case OG_RENDERMODE_SPRITES:
        m_pCurShader = m_pShaderMgr->GetShader(OG_SHADER_SPRITE);
        SetBlend(OG_BLEND_ALPHABLEND);
        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);

        m_pCurShader->SetProjectionMatrix(m_mOrthoProj);
        m_pCurShader->Setup();

        EnableLight(false);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        break;

    case OG_RENDERMODE_SHADOWMAP:
        m_pCurShader = m_pShaderMgr->GetShader(OG_SHADER_SHADOWMODEL);
        Reset();

        m_pLightMgr->UpdateGlobalLight(m_pCamera);
        glDisable(GL_BLEND);
        glDisable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        m_pRT->Begin();

        m_pCurShader->SetCamera(m_pCamera);
        m_pCurShader->SetProjectionMatrix(m_pLightMgr->GetGlobalLightProjMatrix());
        m_pCurShader->SetViewMatrix(m_pLightMgr->GetGlobalLightViewMatrix());
        m_pCurShader->SetLighting(m_pFog, m_pLightMgr);
        m_pCurShader->Setup();

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        break;

    case OG_RENDERMODE_SHADOWEDSCENE:
        m_pCurShader = m_pShaderMgr->GetShader(OG_SHADER_SHADOWEDSCENE);
        glDisable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND); 
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        glBindTexture(GL_TEXTURE_2D, m_pRT->GetTextureId());

        m_pCurShader->SetCamera(m_pCamera);
        m_pCurShader->SetProjectionMatrix(m_mProjection);
        m_pCurShader->SetViewMatrix(m_mView);
        m_pCurShader->SetLighting(m_pFog, m_pLightMgr);
        m_pCurShader->Setup();

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        break;

    case OG_RENDERMODE_TEXT:
        m_pCurShader = m_pShaderMgr->GetShader(OG_SHADER_TEXT);
        SetBlend(OG_BLEND_ALPHABLEND);

        m_pCurShader->SetProjectionMatrix(m_mTextProj);
        m_pCurShader->Setup();
        break;
    }
}


// finish rendering mode.
void COGRenderer::FinishRenderMode()
{
    switch(m_Mode)
    {
    case OG_RENDERMODE_GEOMETRY:
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        break;

    case OG_RENDERMODE_EFFECTS:
        glEnable(GL_DEPTH_TEST);
        glDisable(GL_BLEND); 
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        break;

    case OG_RENDERMODE_SPRITES:
        glDisable(GL_BLEND); 
        glEnable(GL_DEPTH_TEST);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        break;

    case OG_RENDERMODE_TEXT:
        m_pText->Flush();
        glDisable(GL_BLEND); 
        glEnable(GL_DEPTH_TEST);
        //glEnable(GL_CULL_FACE);
        break;

    case OG_RENDERMODE_SHADOWMAP:
        m_pRT->End();
        glViewport(0, 0, m_Width, m_Height);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        Reset();
        break;

    case OG_RENDERMODE_SHADOWEDSCENE:
        glDisable(GL_BLEND);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        break;
    }
}


// add rendering command.
void COGRenderer::RenderMesh (void* _pMesh)
{
    m_pCurShader->SetModelMatrix(m_mWorld);
    m_pCurShader->Apply();

    if ((IOGVertexBuffers*)_pMesh != m_pCurMesh)
    {
        m_pCurMesh = (IOGVertexBuffers*)_pMesh;
        m_pCurMesh->Apply();
    }
    m_pCurMesh->Render();
}


// clear frame buffer with the given color
void COGRenderer::ClearFrame (const OGVec4& _vClearColor)
{
    glClearColor(_vClearColor.x, _vClearColor.y, _vClearColor.z, _vClearColor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
    va_list	args;
    static char	Text[5120+1];
    va_start(args, pszFormat);
    vsprintf(Text, pszFormat, args);
    va_end(args);

    m_pText->DisplayText(_vPos.x,_vPos.y,_fScale, Colour, Text);
}


// Draw effects buffer.
void COGRenderer::DrawEffectBuffer (void* _pBuffer, int _StartId, int _NumVertices)
{
    m_pCurShader->SetModelMatrix(m_mWorld);
    m_pCurShader->Apply();

    // vertex pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 36, _pBuffer);
    // texture coord pointer
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 36, (void*)((char *)_pBuffer + 12));
    // color pointer
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 36, (void*)((char *)_pBuffer + 20));
    glDrawArrays(GL_TRIANGLE_STRIP, _StartId, _NumVertices);

#ifdef STATISTICS
    m_pStats->AddVertexCount(_NumVertices, 1);
    m_pStats->AddDrawCall();
    m_pStats->AddVBOSwitch();
#endif
}


// Draw sprite buffer.
void COGRenderer::DrawSpriteBuffer (void* _pBuffer, int _StartId, int _NumVertices)
{
    // vertex pointer
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 32, _pBuffer);
    // texture coord pointer
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 32, (void*)((char *)_pBuffer + 8));
    // color pointer
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 32, (void*)((char *)_pBuffer + 16));
    glDrawArrays(GL_TRIANGLE_STRIP, _StartId, _NumVertices);

#ifdef STATISTICS
    m_pStats->AddVertexCount(_NumVertices, 1);
    m_pStats->AddDrawCall();
    m_pStats->AddVBOSwitch();
#endif
}


// Draw render target.
void COGRenderer::DrawRT ()
{
    float HalfScrWidth = (float)m_Width / 2;
    float HalfScrHeight = (float)m_Height / 2;
    OGVec4 Color = OGVec4(1.0f, 1.0f, 1.0f, 1.0f);
    OGVec2 vSize = OGVec2((float)m_pRT->m_Size, (float)m_pRT->m_Size);
    OGVec2 vPos = OGVec2(m_Width - vSize.x, 0);

    float fLeft = -HalfScrWidth+vPos.x;
    float fRight = -HalfScrWidth+vSize.x+vPos.x;
    float fTop = HalfScrHeight-vSize.y-vPos.y;
    float fBottom = HalfScrHeight-vPos.y;

    g_RTVertices[0].p = OGVec2(fRight, fTop);	
    g_RTVertices[0].t = OGVec2(1.0f, 0.0f); 
    g_RTVertices[0].c = Color;
    g_RTVertices[1].p = OGVec2(fLeft, fTop);	
    g_RTVertices[1].t = OGVec2(0.0f, 0.0f); 
    g_RTVertices[1].c = Color;
    g_RTVertices[2].p = OGVec2(fRight, fBottom);	
    g_RTVertices[2].t = OGVec2(1.0f, 1.0f); 
    g_RTVertices[2].c = Color;
    g_RTVertices[3].p = OGVec2(fLeft, fBottom);	
    g_RTVertices[3].t = OGVec2(0.0f, 1.0f); 
    g_RTVertices[3].c = Color;

    glBindTexture(GL_TEXTURE_2D, m_pRT->GetTextureId());
    DrawSpriteBuffer(g_RTVertices, 0, 4);
}


// Debug - insert event marker.
void COGRenderer::InsertEventMarker (const std::string& _MarkerStr)
{
#ifndef WIN32
    if (glInsertEventMarkerEXT)
        glInsertEventMarkerEXT(_MarkerStr.size()+1, _MarkerStr.c_str());
#endif
}


// Debug - push group marker.
void COGRenderer::PushGroupMarker (const std::string& _MarkerStr)
{
#ifndef WIN32
    if (glPushGroupMarkerEXT)
        glPushGroupMarkerEXT(_MarkerStr.size()+1, _MarkerStr.c_str());
#endif
}


// Debug - pop group marker.
void COGRenderer::PopGroupMarker ()
{
#ifndef WIN32
    if (glPopGroupMarkerEXT)
        glPopGroupMarkerEXT();
#endif
}


// Debug - label object.
void COGRenderer::LabelObject (unsigned int _ObjType, unsigned int _ObjId, const std::string& _ObjLabelStr)
{
#ifndef WIN32
    if (glLabelObjectEXT)
        glLabelObjectEXT(_ObjType, _ObjId, _ObjLabelStr.size()+1, _ObjLabelStr.c_str());
#endif
}
