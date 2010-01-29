#ifndef IOGGRAPHICSHELPERS_H_
#define IOGGRAPHICSHELPERS_H_

#include "IOGAabb.h"


// Draw AABB
void DrawAABB (const IOGAabb& _aabb);

// Draw coordiantes grid
void DrawCoordGrid (int _Bounds, int _Step, int _MajorStep);

// Draw point patch grid
void DrawPatchGrid (int _NumPatchVerts, const Vec3* _pGridData);

#endif