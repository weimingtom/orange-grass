/*
 *  ogfog.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenGL2.h"
#include "ogfog.h"


COGFog::COGFog () : m_bEnabled(false)
{
	glFogf(GL_FOG_MODE, GL_LINEAR);
	glHint(GL_FOG_HINT, GL_DONT_CARE);
}


COGFog::~COGFog ()
{
}


// set light color.
void COGFog::SetColor (const Vec4& _vColor)
{
	m_Color = _vColor;
	glFogfv(GL_FOG_COLOR, m_Color.ptr());
}


// set fog start.
void COGFog::SetStart (float _fStart)
{
	m_fStart = _fStart;
	glFogf(GL_FOG_START, m_fStart);
}


// set fog end.
void COGFog::SetEnd (float _fEnd)
{
	m_fEnd = _fEnd;
	glFogf(GL_FOG_END, m_fEnd);
}


// set fog density.
void COGFog::SetDensity (float _fDensity)
{
	m_fDensity = _fDensity;
	glFogf(GL_FOG_DENSITY, m_fDensity);
}


// enable or disable.
void COGFog::Enable (bool _bEnable)
{
	m_bEnabled = _bEnable;

	if (m_bEnabled)
		glEnable(GL_FOG);
	else
		glDisable(GL_FOG);
}
