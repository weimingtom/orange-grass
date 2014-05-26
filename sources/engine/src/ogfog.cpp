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
#include "ogfog.h"


COGFog::COGFog () 
    : m_bEnabled(false)
    , m_fDensity(0.0f)
    , m_fStart(0.0f)
    , m_fEnd(0.0f)
    , m_Color(0.0f, 0.0f, 0.0f, 0.0f)
{
}


COGFog::~COGFog ()
{
}


// set light color.
void COGFog::SetColor (const OGVec4& _vColor)
{
	m_Color = _vColor;
}


// set fog start.
void COGFog::SetStart (float _fStart)
{
	m_fStart = _fStart;
}


// set fog end.
void COGFog::SetEnd (float _fEnd)
{
	m_fEnd = _fEnd;
}


// set fog density.
void COGFog::SetDensity (float _fDensity)
{
	m_fDensity = _fDensity;
}


// set fog enabled status.
void COGFog::SetEnabled (bool _bEnable)
{
    m_bEnabled = _bEnable;
}
