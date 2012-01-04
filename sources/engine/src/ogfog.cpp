/*
 *  ogfog.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogfog.h"


COGFog::COGFog () : m_bEnabled(false)
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
