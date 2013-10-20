/*
 *  ogbakedanimation.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGBAKEDANIMATION_H_
#define OGBAKEDANIMATION_H_

#include "IOGMath.h"
#include "IOGAnimation.h"


class COGBakedAnimation : public IOGAnim
{
public:
    COGBakedAnimation();
    virtual ~COGBakedAnimation ();

    // start animation
    virtual void Start(IOGAnimation* _pAnimation);

    // stop animation
    virtual void Stop();

    // check if  animation is playing
    virtual bool IsPlaying() { return m_bPlaying; }

    // get animation progress
    virtual float GetProgress() { return m_fProgress; }

    // update animation step (for baked animation)
    virtual void Update(unsigned long _ElapsedTime);

    // update animation step (for procedure animation)
    virtual void Update(unsigned long _ElapsedTime, OGMatrix& _mOut, const OGMatrix& _mIn);

protected:
    IOGAnimation*   m_pCurAnimation;
    float           m_fProgress;
    bool            m_bPlaying;
};

#endif
