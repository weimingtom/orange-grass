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
#ifndef IOGRENDERTYPES_H_
#define IOGRENDERTYPES_H_

enum OGRenderPass
{
    OG_RENDERPASS_SHADOWMAP,
    OG_RENDERPASS_SCENE,
};

enum OGRenderMode
{
    OG_RENDERMODE_GEOMETRY,
    OG_RENDERMODE_EFFECTS,
    OG_RENDERMODE_SPRITES,
    OG_RENDERMODE_SHADOWMAP,
    OG_RENDERMODE_SHADOWEDSCENE,
    OG_RENDERMODE_TEXT
};


enum OGBlendType
{
    OG_BLEND_NO,
    OG_BLEND_SOLID,
    OG_BLEND_ALPHATEST,
    OG_BLEND_ALPHABLEND,
    OG_BLEND_ALPHAADD,
    OG_BLEND_ALPHAONE,
};


#endif