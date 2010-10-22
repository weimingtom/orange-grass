/*
 *  OGGameSequence.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGGAMESEQUENCE_H_
#define OGGAMESEQUENCE_H_

#include "IOGGameSequence.h"
#include <vector>


class COGGameSequence : public IOGGameSequence
{
public:
	COGGameSequence ();
	virtual ~COGGameSequence ();

	// Add level
	virtual void AddLevel (const IOGLevelParams& _level);

	// Get level
	virtual IOGLevelParams* GetLevel (unsigned int _Id);

protected:

	std::vector<IOGLevelParams>	m_Levels;
};

#endif