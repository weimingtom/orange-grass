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
#ifndef IOGRENDERABLE_H_
#define IOGRENDERABLE_H_

#include "IOGAabb.h"
#include "IOGAnimation.h"
#include <string>


// Type of the renderables
enum RenderableType
{
    OG_RENDERABLE_MODEL,
    OG_RENDERABLE_TERRAIN,
    OG_RENDERABLE_EFFECT,
};


enum SceneMeshType
{
    OG_SCENEMESH_TERRA              = 0,
    OG_SCENEMESH_SOLID_OBJ          = 1,
    OG_SCENEMESH_TRANSPARENT_OBJ    = 2
};


enum SubMeshType
{
    OG_SUBMESH_DUMMY        = 0,
    OG_SUBMESH_BODY         = 1,
    OG_SUBMESH_PROPELLER    = 2,
    OG_SUBMESH_ACTPOINT     = 3
};


enum OGSceneProps
{
    OG_SCENEPROP_SHADOWCASTER   = 1,
    OG_SCENEPROP_SHADOWRECEIVER = 2,
};


struct IOGActivePoint
{
    std::string     alias;
    OGVec3          pos;
    unsigned int    part;
};


#endif
