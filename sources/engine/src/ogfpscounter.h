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
#ifndef OGFPSCOUNTER_H_
#define OGFPSCOUNTER_H_

#include <IOGCoreHelpers.h>
#include <IOGFPSCounter.h>

class COGFPSCounter : public IOGFPSCounter
{
public:
	COGFPSCounter();
	virtual ~COGFPSCounter();

	// updating FPS counter
	virtual void Update ();

	// getting current FPS rate
	virtual long GetFPS ()  { return (long)fps; }

private:

	float fps;
	float speedfactor;

	LARGE_INTEGER tickspersecond;
	LARGE_INTEGER currentticks;
	LARGE_INTEGER framedelay;
};

#endif
