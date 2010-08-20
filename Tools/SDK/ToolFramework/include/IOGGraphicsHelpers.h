/*
 *  IOGGraphicsHelpers.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGGRAPHICSHELPERS_H_
#define IOGGRAPHICSHELPERS_H_

#include "IOGObb.h"
#include "IOGMesh.h"
#include <vector>


// Draw AABB
void DrawAABB (const IOGAabb& _aabb);

// Draw OBB
void DrawOBB (const IOGObb& _obb);

// Draw line
void DrawLine (const Vec3& _vStart, const Vec3& _vEnd);

// Draw coordiantes grid
void DrawCoordGrid (int _Bounds, int _Step, int _MajorStep);

// Draw point patch grid
void DrawPatchGrid (int _NumPatchVerts, const Vec3* _pGridData);

// Draw geometry grid
void DrawGeometryGrid (const std::vector<OGFace>& _GridData);

// Draw level ranges
void DrawLevelRanges (const Vec3& _StartPoint, const Vec3& _FinishPoint, float _fWidth, float _fHeight);

#endif