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
    
	// Accelerometer handler.
	virtual void OnAccelerometer ( float _X, float _Y, float _Z );
    
private:

	std::vector<IOGInputReceiver*>	m_Receivers;
    float   m_fPrevX;
    float   m_fPrevY;
    bool    m_bInMove;
};


#endif
