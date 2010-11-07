/*
 *  OGGuiLifebar.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGGUILIFEBAR_H_
#define OGGUILIFEBAR_H_

#include "IOGGuiLifebar.h"


class COGGuiLifebar : public IOGGuiLifebar
{
public:
    COGGuiLifebar ();
	virtual ~COGGuiLifebar();

	// Load graphics.
    virtual void Load ();

	// Unload graphics.
    virtual void Unload ();

	// Update data.
	virtual void UpdateData (unsigned int _Val, unsigned int _MaxVal);

	// Render sprite.
	virtual void Render ();

protected:

	IOGResourceMgr*	m_pResourceMgr;
    IOGSprite*      m_pFrame;
    IOGSprite*      m_pBar;
    Vec2            m_Size;
    Vec2            m_Position;
    unsigned int    m_Val; 
    unsigned int    m_MaxVal;
};


#endif
