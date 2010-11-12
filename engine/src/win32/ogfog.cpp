/*
 *  ogfog.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogfog.h"


COGFog::COGFog ()
{
}


COGFog::~COGFog ()
{
}


// set light color.
void COGFog::SetColor (const Vec4& _vColor)
{
	m_Color = _vColor;
	//m_Color = Vec4(0.08f, 0.08f, 0.05f, 1.0f);
}


// set fog start.
void COGFog::SetStart (float _fStart)
{
	m_fStart = _fStart;
	//m_fStart = 200.0f;
}


// set fog end.
void COGFog::SetEnd (float _fEnd)
{
	m_fEnd = _fEnd;
	//m_fEnd = 250.0f;
}


// set fog density.
void COGFog::SetDensity (float _fDensity)
{
	m_fDensity = _fDensity;
}
