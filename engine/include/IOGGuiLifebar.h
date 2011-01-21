/*
 *  IOGGuiLifebar.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGGUILIFEBAR_H_
#define IOGGUILIFEBAR_H_

#include "Mathematics.h"
#include <string>
#include "IOGSettingsReader.h"


class IOGGuiLifebar
{
public:
	virtual ~IOGGuiLifebar() {}

	// Load graphics.
    virtual void Load (IOGGroupNode* _pNode) = 0;

	// Unload graphics.
    virtual void Unload () = 0;

	// Update data.
	virtual void UpdateData (unsigned int _Val, unsigned int _MaxVal) = 0;

	// Render sprite.
	virtual void Render () = 0;
};


#endif
