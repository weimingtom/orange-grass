/*
 *  ogbakedanimation.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogbakedanimation.h"


COGBakedAnimation::COGBakedAnimation()
    : m_fProgress(0.0f)
    , m_bPlaying(false)
    , m_pCurAnimation(NULL)
{
}


COGBakedAnimation::~COGBakedAnimation ()
{
}


void COGBakedAnimation::Start(IOGAnimation* _pAnimation)
{
    m_pCurAnimation = _pAnimation;
    m_bPlaying = true;
    m_fProgress = (float)m_pCurAnimation->start_frame;
}


void COGBakedAnimation::Stop()
{
    m_pCurAnimation = NULL;
    m_bPlaying = false;
    m_fProgress = 0.0f;
}


void COGBakedAnimation::Update(unsigned long _ElapsedTime)
{
    if (m_bPlaying)
    {
        float fNewProgress = m_fProgress + m_pCurAnimation->speed;
        if (fNewProgress < m_pCurAnimation->end_frame - 1)
        {
            m_fProgress = fNewProgress;
        }
        else
        {
            if (m_pCurAnimation->looped)
                m_fProgress = (float)m_pCurAnimation->start_frame + (fNewProgress - m_pCurAnimation->end_frame - 1);
            else
            {
                m_bPlaying = false;
                m_fProgress = (float)(m_pCurAnimation->end_frame - 1);
            }
        }
    }
}


void COGBakedAnimation::Update(unsigned long _ElapsedTime, OGMatrix& _mOut, const OGMatrix& _mIn)
{
    Update(_ElapsedTime);
}
