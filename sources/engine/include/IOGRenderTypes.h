/*
 *  IOGRenderTypes.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 07.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
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