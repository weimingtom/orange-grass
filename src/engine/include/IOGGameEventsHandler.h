/*
 *  IOGGameEventsHandler.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGGAMEEVENTSHANDLER_H_
#define IOGGAMEEVENTSHANDLER_H_


class IOGGameEventsHandler
{
public:
	// destructor
	virtual ~IOGGameEventsHandler () {}

	// Level finish point handler
	virtual void OnReachedFinishPoint () = 0;

	// Level finish handler
	virtual void OnLevelFinish () = 0;
};

#endif