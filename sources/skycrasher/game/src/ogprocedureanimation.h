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
#ifndef OGPROCEDUREANIMATION_H_
#define OGPROCEDUREANIMATION_H_

#include "IOGMath.h"
#include "IOGAnimation.h"


class COGRotationAnimation : public IOGAnim
{
public:
    COGRotationAnimation();
    virtual ~COGRotationAnimation ();

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
