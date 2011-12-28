/*
 *  IOGInputReceiver.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
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
