/*
 *  OGInputDispatcher.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGINPUTDISPATCHER_H_
#define OGINPUTDISPATCHER_H_

#include "IOGInputDispatcher.h"
#include <vector>


class COGInputDispatcher : public IOGInputDispatcher
{
public:
	COGInputDispatcher();
	virtual ~COGInputDispatcher();

	// Register input receiver.
	virtual void RegisterReceiver (IOGInputReceiver* _pReceiver);

	// Unregister input receiver.
	virtual void UnregisterReceiver (IOGInputReceiver* _pReceiver);

	// Pointing device press handler.
	virtual void OnPointerDown ( int _X, int _Y );

	// Pointing device release handler.
	virtual void OnPointerUp ( int _X, int _Y );

	// Pointing device move handler.
	virtual void OnPointerMove ( int _X, int _Y );

private:

	std::vector<IOGInputReceiver*>	m_Receivers;
};


#endif
