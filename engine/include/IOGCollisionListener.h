/*
 *  IOGCollisionListener.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGCOLLISIONLISTENER_H_
#define IOGCOLLISIONLISTENER_H_


struct IOGCollision
{
	void* pActorMissile;
	void* pActorBot;
};


class IOGCollisionListener
{
public:
    // collision event handler
	virtual bool OnCollision (const IOGCollision& _Collision) = 0;
};

#endif
