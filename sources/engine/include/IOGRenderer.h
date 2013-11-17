/*
*  IOGRenderer.h
*  OrangeGrass
*
*  Created by Viacheslav Bogdanov on 07.11.09.
*  Copyright 2009 __MyCompanyName__. All rights reserved.
*
*/
#ifndef IOGRENDERER_H_
#define IOGRENDERER_H_

#include "IOGTexture.h"
#include "IOGMaterial.h"
#include "IOGLight.h"
#include "IOGCamera.h"
#include "IOGFog.h"
#include "IOGVertexBuffers.h"
#include "IOGDynVertexBuffers.h"
#include "IOGShader.h"


class IOGRenderer
{
public:
    virtual ~IOGRenderer () {}

    // initialize renderer.
    virtual bool Init () = 0;

    // set viewport.
    virtual void SetViewport (
        unsigned int _Width, 
        unsigned int _Height,
        float _fZNear,
        float _fZFar,
        float _fFOV) = 0;

    // Create vertex buffer for effects.
    virtual IOGDynVertexBuffers* CreateDynVertexBuffer (unsigned int _NumVertices) = 0;

    // Create vertex buffer for mesh.
    virtual IOGVertexBuffers* CreateVertexBuffer (
        const void* _pVertexData, 
        unsigned int _NumVertices, 
        unsigned int _NumFaces,
        unsigned int _Stride, 
        const void* _pIndexData, 
        unsigned int _NumIndices) = 0;

    // add rendering command.
    virtual void SetTexture (IOGTexture* _pTexture) = 0;

    // add rendering command.
    virtual void SetMaterial (IOGMaterial* _pMaterial) = 0;

    // add rendering command.
    virtual void SetBlend (OGBlendType _Blend) = 0;

    // set model matrix.
    virtual void SetModelMatrix (const OGMatrix& _mModel) = 0;

    // set view matrix.
    virtual void SetViewMatrix (const OGMatrix& _mView) = 0;

    // get model matrix.
    virtual void GetModelMatrix (OGMatrix& _mModel) = 0;

    // get view matrix.
    virtual void GetViewMatrix (OGMatrix& _mView) = 0;

    // get projection matrix.
    virtual void GetProjectionMatrix (OGMatrix& _mProjection) = 0;

    // add render job.
    virtual void RenderStatic (
        IOGTexture* _pTexture,
        IOGMaterial* _pMaterial,
        IOGVertexBuffers* _pMesh,
        OGMatrix _mTransform,
        OGBlendType _Blend,
        OGShaderID _ShaderID) = 0;

    // clear frame buffer with the given color
    virtual void ClearFrame (const OGVec4& _vClearColor) = 0;

    // Get scene light.
    virtual IOGLightMgr* GetLightMgr () = 0;

    // Enable scene light.
    virtual void EnableLight (bool _bEnable) = 0;

    // Get main camera.
    virtual IOGCamera* GetCamera () = 0;

    // Get fog.
    virtual IOGFog* GetFog () = 0;

    // Create material.
    virtual IOGMaterial* CreateMaterial () = 0;

    // Enable scene fog.
    virtual void EnableFog (bool _bEnable) = 0;

    // Enable color channel.
    virtual void EnableColor (bool _bEnable) = 0;

    // start rendering mode.
    virtual void StartRenderMode(OGRenderMode _Mode) = 0;

    // finish rendering mode.
    virtual void FinishRenderMode() = 0;

    // reset renderer pipeline.
    virtual void Reset () = 0;

    // Unproject screen coords.
    virtual OGVec3 UnprojectCoords (int _X, int _Y) = 0;

    // Display string.
    virtual void DisplayString (const OGVec2& _vPos, float _fScale, unsigned int Colour, const char * const pszFormat, ...) = 0;

    // Draw effects buffer.
    virtual void DrawEffectBuffer (void* _pBuffer, int _StartId, int _NumVertices) = 0;

    // Draw sprite buffer.
    virtual void DrawSpriteBuffer (void* _pBuffer, int _StartId, int _NumVertices) = 0;

    // Draw render target.
    virtual void DrawRT () = 0;

    // Debug - insert event marker.
    virtual void InsertEventMarker (const std::string& _MarkerStr) = 0;

    // Debug - push group marker.
    virtual void PushGroupMarker (const std::string& _MarkerStr) = 0;

    // Debug - pop group marker.
    virtual void PopGroupMarker () = 0;

    // Debug - label object.
    virtual void LabelObject (unsigned int _ObjType, unsigned int _ObjId, const std::string& _ObjLabelStr) = 0;
};

#endif
