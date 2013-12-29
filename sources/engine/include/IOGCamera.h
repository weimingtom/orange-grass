/*
 *  IOGCamera.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 14.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGCAMERA_H_
#define IOGCAMERA_H_

#include "IOGMath.h"
#include "IOGFrustum.h"


class IOGCamera
{
public:
    virtual ~IOGCamera () {}

    // setup camera viewport.
    virtual void SetupViewport (const OGMatrix& _mProjection) = 0;

    // setup camera.
    virtual void Setup (const OGVec3& _vPosition, const OGVec3& _vDirection, const OGVec3& _vUp) = 0;

    // get camera position.
    virtual const OGVec3& GetPosition () const = 0;

    // get camera direction.
    virtual const OGVec3& GetDirection () const = 0;

    // get camera up.
    virtual const OGVec3& GetUp () const = 0;

    // get camera right.
    virtual const OGVec3& GetRight () const = 0;

    // move camera in defined direction
    virtual void Strafe(float _fSpeed, const OGVec3& _vDir) = 0;

    // move camera forward/backward
    virtual void Move(float _fSpeed) = 0;

    // update camera.
    virtual void Update () = 0;

    // get camera view matrix.
    virtual const OGMatrix& GetViewMatrix () const = 0;

    // get viewing frustum.
    virtual const IOGFrustum& GetFrustum () const = 0;

    // get left and right edges.
    virtual void GetEdges (OGVec3& _vLeft, OGVec3& _vRight, float _fFOV, float _fDist) = 0;
};

#endif
