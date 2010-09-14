/*
 *  oglight.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenGL2.h"
#include "oglight.h"


COGLight::COGLight () : m_bEnabled(false)
{
}


COGLight::~COGLight ()
{
}


// set light color.
void COGLight::SetColor (const Vec4& _vColor)
{
	m_vColor = _vColor;
}


// set light direction.
void COGLight::SetDirection (const Vec4& _vDirection)
{
	m_vDirection = _vDirection;
}

		
// apply lighting.
void COGLight::Apply ()
{
	glLightfv(GL_LIGHT0, GL_POSITION, (VERTTYPE*)&m_vDirection);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, (VERTTYPE*)&m_vColor);
	glLightfv(GL_LIGHT0, GL_AMBIENT, (VERTTYPE*)&m_vColor);
	glLightfv(GL_LIGHT0, GL_SPECULAR, (VERTTYPE*)&m_vColor);
}


// enable or disable light.
void COGLight::Enable (bool _bEnable)
{
	m_bEnabled = _bEnable;
	if (m_bEnabled)
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	}
	else
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
	}
}
