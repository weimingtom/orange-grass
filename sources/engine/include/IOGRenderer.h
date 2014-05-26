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
#ifndef IOGRENDERER_H_
#define IOGRENDERER_H_

#include "IOGTexture.h"
#include "IOGMaterial.h"
#include "IOGLight.h"
#include "IOGCamera.h"
#include "IOGFog.h"
#include "IOGVertexBuffers.h"
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

    // set clear color.
    virtual void SetClearColor (const OGVec4& _vColor) = 0;

    // set fog state.
    virtual void EnableFog (bool _bEnable) = 0;

    // Create vertex buffer for effects.
    virtual IOGVertexBuffers* CreateDynVertexBuffer (unsigned int _NumFaces) = 0;

    // Create vertex buffer for mesh.
    virtual IOGVertexBuffers* CreateVertexBuffer (
        const void* _pVertexData, 
        unsigned int _NumVertices, 
        unsigned int _NumFaces,
        unsigned int _Stride, 
        const void* _pIndexData, 
        unsigned int _NumIndices) = 0;

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
        OGShaderID _ShaderID,
        OGRenderPass _Pass) = 0;

    // add render job.
    virtual void RenderEffect (
        IOGTexture* _pTexture,
        IOGVertexBuffers* _pMesh,
        OGBlendType _Blend,
        OGShaderID _ShaderID,
        OGRenderPass _Pass) = 0;

    // Get scene light.
    virtual IOGLightMgr* GetLightMgr () = 0;

    // Get main camera.
    virtual IOGCamera* GetCamera () = 0;

    // Get fog.
    virtual IOGFog* GetFog () = 0;

    // Create material.
    virtual IOGMaterial* CreateMaterial () = 0;

    // reset renderer pipeline.
    virtual void Reset () = 0;

    // Unproject screen coords.
    virtual OGVec3 UnprojectCoords (int _X, int _Y) = 0;

    // Display string.
    virtual void DisplayString (const OGVec2& _vPos, float _fScale, unsigned int Colour, const char * const pszFormat, ...) = 0;

    // Draw scene.
    virtual void DrawScene () = 0;

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
