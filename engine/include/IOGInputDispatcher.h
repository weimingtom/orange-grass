/*
 *  IOGInputDispatcher.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
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
};


#endif
