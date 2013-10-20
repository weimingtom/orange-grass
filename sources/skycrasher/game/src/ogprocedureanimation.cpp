/*
 *  ogprocedureanimation.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogprocedureanimation.h"


COGRotationAnimation::COGRotationAnimation()
    : m_fProgress(0.0f)
    , m_bPlaying(false)
{
}


COGRotationAnimation::~COGRotationAnimation ()
{
}


void COGRotationAnimation::Start(IOGAnimation* _pAnimation)
{
    m_pCurAnimation = _pAnimation;
    m_bPlaying = true;
    m_fProgress = 0.0f;
}


void COGRotationAnimation::Stop()
{
    m_bPlaying = false;
    m_fProgress = 0.0f;
}


void COGRotationAnimation::Update(unsigned long _ElapsedTime, OGMatrix& _mOut, const OGMatrix& _mIn)
{
    if (m_bPlaying)
        m_fProgress += 0.5f;

    OGMatrix mSpin;
    MatrixRotationY(mSpin, m_fProgress);
    MatrixMultiply(_mOut, mSpin, _mIn);
}


void COGRotationAnimation::Update(unsigned long _ElapsedTime)
{
}
