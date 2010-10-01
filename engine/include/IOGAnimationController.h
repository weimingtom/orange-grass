/*
 *  IOGAnimationController.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGANIMATIONCONTROLLER_H_
#define IOGANIMATIONCONTROLLER_H_

#include "IOGAnimation.h"


class IOGAnimationController
{
public:
	virtual ~IOGAnimationController () {}

	// start animation.
	virtual void StartAnimation (IOGAnimation* _pAnimation) = 0;

	// stop animation.
	virtual void StopAnimation () = 0;

	// pause animation.
	virtual void PauseAnimation () = 0;

	// resume animation.
	virtual void ResumeAnimation () = 0;

	// update animation.
	virtual void UpdateAnimation (unsigned long _ElapsedTime) = 0;

	// get current animation.
	virtual IOGAnimation* GetCurrentAnimation () = 0;

	// get current animation progress.
	virtual float GetCurrentAnimationProgress () const = 0;

	// is animation playing.
	virtual bool IsAnimationPlaying () const = 0;
};

#endif
