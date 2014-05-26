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
#ifndef IOGINPUTRECEIVER_H_
#define IOGINPUTRECEIVER_H_


enum IOGTouchParam
{
    OG_TOUCH_DOWN,
    OG_TOUCH_UP
};


class IOGInputReceiver
{
public:
	virtual ~IOGInputReceiver() {}

	// Control vector change event handler.
	virtual bool OnVectorChanged (const OGVec3& _vVec) = 0;

	// Touch event handler.
	virtual bool OnTouch (const OGVec2& _vPos, IOGTouchParam _param) = 0;
};


#endif
