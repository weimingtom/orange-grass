/*
 * IOGAabb.h
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
