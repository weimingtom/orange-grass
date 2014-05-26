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
