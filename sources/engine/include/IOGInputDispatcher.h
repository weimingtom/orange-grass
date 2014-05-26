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
#ifndef IOGINPUTDISPATCHER_H_
#define IOGINPUTDISPATCHER_H_

#include "IOGInputReceiver.h"


class IOGInputDispatcher
{
public:
	virtual ~IOGInputDispatcher() {}

	// Register input receiver.
	virtual void RegisterReceiver (IOGInputReceiver* _pReceiver) = 0;

	// Unregister input receiver.
	virtual void UnregisterReceiver (IOGInputReceiver* _pReceiver) = 0;

	// Pointing device press handler.
	virtual void OnPointerDown ( int _X, int _Y ) = 0;

	// Pointing device release handler.
	virtual void OnPointerUp ( int _X, int _Y ) = 0;

	// Pointing device move handler.
	virtual void OnPointerMove ( int _X, int _Y ) = 0;
    
	// Accelerometer handler.
	virtual void OnAccelerometer ( float _X, float _Y, float _Z ) = 0;
};


#endif
