/*
 *  ogeffect.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenGL2.h"
#include "ogeffect.h"
#include "common.h"


COGEffect::COGEffect()
{
}


COGEffect::~COGEffect()
{
}


// Set position.
void COGEffect::SetPosition (const Vec3& _vPos)
{
	m_Position = _vPos;
}


// Set direction.
void COGEffect::SetDirection (const Vec3& _vDir)
{
	m_Direction = _vDir;
}


// Start.
void COGEffect::Start ()
{
}


// Stop.
void COGEffect::Stop ()
{
}
