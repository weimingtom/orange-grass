/*
 *  IOGScreenController.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGSCREENCONTROLLER_H_
#define IOGSCREENCONTROLLER_H_

enum ScreenType
{
    SCRTYPE_NONE,
    SCRTYPE_STARTMENU,
    SCRTYPE_LOAD,
    SCRTYPE_GAME
};

enum ControllerState
{
    CSTATE_NO,
    CSTATE_ACTIVE,
    CSTATE_INACTIVE,
    CSTATE_FAILED
};

class IOGScreenController
{
public:
	virtual ~IOGScreenController() {}
	
	// Initialize controller
	virtual bool Init () = 0;
	
	// Get controller state
	virtual ControllerState GetState () const = 0;
	
	// Get controller type
	virtual ScreenType GetType () const = 0;
	
	// Update controller
	virtual void Update (unsigned long _ElapsedTime) = 0;
	
	// Render controller scene
	virtual void RenderScene () = 0;
	
	// Activate
	virtual void Activate () = 0;
	
	// deactivate
	virtual void Deactivate () = 0;
};

#endif