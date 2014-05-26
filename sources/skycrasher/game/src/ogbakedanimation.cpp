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
