/*
 *  IOGGuiBonusbar.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGGUIBONUSBAR_H_
#define IOGGUIBONUSBAR_H_

#include "IOGMath.h"
#include <string>
#include "IOGSettingsReader.h"


class IOGGuiBonusbar
{
public:
	virtual ~IOGGuiBonusbar() {}

	// Load graphics.
    virtual void Load (IOGGroupNode* _pNode) = 0;

	// Unload graphics.
    virtual void Unload () = 0;

	// Update data.
	virtual void SetData (
        unsigned int _Id, 
        const std::string& _SprBonus, 
        unsigned int _Val, 
        unsigned int _MaxVal) = 0;

	// Render sprite.
	virtual void Render () = 0;

	// Reset data.
    virtual void ResetData () = 0;
};


#endif
