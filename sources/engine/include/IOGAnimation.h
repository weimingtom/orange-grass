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


class IOGAnim
{
public:
    virtual ~IOGAnim () {}

    // start animation
    virtual void Start(IOGAnimation* _pAnimation) = 0;

    // stop animation
    virtual void Stop() = 0;

    // check if  animation is playing
    virtual bool IsPlaying() = 0;

    // get animation progress
    virtual float GetProgress() = 0;

    // update animation step (for baked animation)
    virtual void Update(unsigned long _ElapsedTime) = 0;

    // update animation step (for procedure animation)
    virtual void Update(unsigned long _ElapsedTime, OGMatrix& _mOut, const OGMatrix& _mIn) = 0;
};


struct OGAnimationCfg
{
    std::map<std::string, IOGAnimation> anim_list;
};

#endif
