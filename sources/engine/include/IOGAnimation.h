/*
 *  IOGAnimation.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGANIMATION_H_
#define IOGANIMATION_H_

#include <string>
#include <map>

struct IOGAnimation
{
    std::string name;
    unsigned int start_frame;
    unsigned int end_frame;
    unsigned int speed;
    bool looped;
};

struct IOGProcAnimation
{
    std::string name;
    float speed;
};

struct OGAnimationCfg
{
    std::map<std::string, IOGAnimation> anim_list;
};

#endif
