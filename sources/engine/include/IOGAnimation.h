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


struct OGAnimationCfg
{
    struct Anim
    {
        std::string anim_alias;
        int anim_start;
        int anim_end;
        int speed;
        int looped;
    };
    std::list<Anim> anim_list;
};


struct IOGAnimation
{
	std::string name;
	unsigned int start_frame;
	unsigned int end_frame;
    unsigned int speed;
    bool looped;
};

#endif