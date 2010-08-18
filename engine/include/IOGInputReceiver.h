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


class IOGInputReceiver
{
public:
	virtual ~IOGInputReceiver() {}

	// Control vector change event handler.
	virtual void OnVectorChanged (const Vec3& _vVec) = 0;
};


#endif
