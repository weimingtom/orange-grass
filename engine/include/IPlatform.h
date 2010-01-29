/*
 *  IPlatform.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IPLATFORM_H_
#define IPLATFORM_H_

#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#include "Mathematics.h"
#include "UI.h"
#include "IOGResourceMgr.h"


class IPlatform
{
public:
	virtual ~IPlatform () {}
		
	// Initialize app
	virtual bool Init () = 0;
		
	// destroy app
	virtual bool Destroy () = 0;
		
	// Update app
	virtual bool Update () = 0;
		
	// Get resource manager
	virtual IOGResourceMgr* GetResourceManager () = 0;
		
	// Get UI handler
	virtual CDisplayText* GetUIHandler () = 0;
};

#endif