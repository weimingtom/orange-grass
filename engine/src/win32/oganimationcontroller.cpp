/*
 *  oganimationcontroller.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "oganimationcontroller.h"


COGAnimationController::COGAnimationController()
{
}


COGAnimationController::~COGAnimationController ()
{
}


// start animation.
void COGAnimationController::StartAnimation (IOGAnimation* _pAnimation)
{
	if (_pAnimation == NULL)
		return;

	m_pCurAnimation = _pAnimation;
	m_bPlaying = true;
	m_fProgress = 0.0f;
}


// stop animation.
void COGAnimationController::StopAnimation ()
{
	m_pCurAnimation = NULL;
	m_bPlaying = false;
	m_fProgress = 0.0f;
}


// pause animation.
void COGAnimationController::PauseAnimation ()
{
	m_bPlaying = false;
}


// resume animation.
void COGAnimationController::ResumeAnimation ()
{
	m_bPlaying = true;
}


// update animation.
void COGAnimationController::UpdateAnimation (unsigned long _ElapsedTime)
{
	if (m_bPlaying)
	{
	}
}
