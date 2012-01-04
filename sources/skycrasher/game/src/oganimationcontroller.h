/*
 *  OGAnimationController.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGANIMATIONCONTROLLER_H_
#define OGANIMATIONCONTROLLER_H_

#include "IOGAnimationController.h"


class COGAnimationController : public IOGAnimationController
{
public:
	COGAnimationController();
	virtual ~COGAnimationController ();

	// start animation.
	virtual void StartAnimation (IOGAnimation* _pAnimation);

	// stop animation.
	virtual void StopAnimation ();

	// pause animation.
	virtual void PauseAnimation ();

	// resume animation.
	virtual void ResumeAnimation ();

	// update animation.
	virtual void UpdateAnimation (unsigned long _ElapsedTime);

	// get current animation.
	virtual IOGAnimation* GetCurrentAnimation () {return m_pCurAnimation;}

	// get current animation progress.
	virtual float GetCurrentAnimationProgress () const {return m_fProgress;}

	// is animation playing.
	virtual bool IsAnimationPlaying () const {return m_bPlaying;}

protected:

	IOGAnimation*	m_pCurAnimation;
	float			m_fProgress;
	bool			m_bPlaying;
};

#endif
