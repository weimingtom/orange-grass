/*
 *  oglight.mm
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


// set light source position.
void COGLight::SetPosition (const VECTOR3& _vPosition)
{
	m_vPosition = _vPosition;
}


// set light direction.
void COGLight::SetDirection (const VECTOR3& _vDirection)
{
	m_vDirection = _vDirection;
}
