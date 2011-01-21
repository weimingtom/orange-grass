/*
 *  OGGuiButton.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGGUIBUTTON_H_
#define OGGUIBUTTON_H_

#include "IOGGuiButton.h"


class COGGuiButton : public IOGGuiButton
{
public:
    COGGuiButton ();
	virtual ~COGGuiButton();

	// Load graphics.
    virtual void Load (const std::string& _SprN, const std::string& _SprPr, const Vec2& _Size);

	// Unload graphics.
    virtual void Unload ();

	// Set button position.
    virtual void SetPosition (const Vec2& _Pos);

	// Touch event handler.
	virtual bool OnTouch (const Vec2& _vPos, IOGTouchParam _param);

	// Render sprite.
	virtual void Render ();

protected:

	IOGResourceMgr*	m_pResourceMgr;
    IOGSprite*      m_pNormal;
    IOGSprite*      m_pPressed;
    IOGSprite*      m_pCurSpr;
    Vec2            m_Size;
    Vec2            m_Position;
};


#endif
