/*
 *  IOGGuiButton.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGGUIBUTTON_H_
#define IOGGUIBUTTON_H_

#include "Mathematics.h"
#include <string>
#include "IOGInputReceiver.h"


class IOGGuiButton
{
public:
	virtual ~IOGGuiButton() {}

	// Load graphics.
    virtual void Load (const std::string& _SprN, const std::string& _SprPr, const Vec2& _Size) = 0;

	// Unload graphics.
    virtual void Unload () = 0;

	// Set button position.
    virtual void SetPosition (const Vec2& _Pos) = 0;

	// Touch event handler.
	virtual bool OnTouch (const Vec2& _vPos, IOGTouchParam _param) = 0;

	// Render sprite.
	virtual void Render () = 0;
};


#endif
