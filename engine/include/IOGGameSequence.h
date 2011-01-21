/*
 *  IOGGameSequence.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGGAMESEQUENCE_H_
#define IOGGAMESEQUENCE_H_

#include <string>


struct IOGLevelParams
{
	unsigned int id;
	std::string alias;
	std::string player_actor;
	std::string weapon;
};


class IOGGameSequence
{
public:
	// destructor
	virtual ~IOGGameSequence () {}

	// Add level
	virtual void AddLevel (const IOGLevelParams& _level) = 0;

	// Get level
	virtual IOGLevelParams* GetLevel (unsigned int _Id) = 0;
};

#endif