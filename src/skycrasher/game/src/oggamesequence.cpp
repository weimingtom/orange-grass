/*
 *  OGGameSequence.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "Game.h"
#include "oggamesequence.h"


COGGameSequence::COGGameSequence ()
{
}


COGGameSequence::~COGGameSequence ()
{
	m_Levels.clear();
}


// Add level
void COGGameSequence::AddLevel (const IOGLevelParams& _level)
{
	IOGLevelParams level = _level;
	level.id = m_Levels.size();
	m_Levels.push_back(level);
}


// Get level
IOGLevelParams* COGGameSequence::GetLevel (unsigned int _Id)
{
	if (_Id < m_Levels.size())
		return &m_Levels[_Id];
	return NULL;
}
