/*
 *  oglight.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "oglight.h"


COGLight::COGLight ()
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
void COGLight::SetDirection (const Vec3& _vDirection)
{
	m_vDirection = _vDirection;
}
