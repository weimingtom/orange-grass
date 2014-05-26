/*
 * OrangeGrass
 * Copyright (C) 2009 Vyacheslav Bogdanov.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/lgpl-3.0-standalone.html>.
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