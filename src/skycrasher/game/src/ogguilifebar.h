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
    virtual void Load (IOGGroupNode* _pNode);

	// Unload graphics.
    virtual void Unload ();

	// Update data.
	virtual void UpdateData (unsigned int _Val, unsigned int _MaxVal);

	// Render sprite.
	virtual void Render ();

protected:

	IOGSettingsReader*	m_pReader;
	IOGResourceMgr*		m_pResourceMgr;
    IOGSprite*			m_pFrame;
    IOGSprite*			m_pBar;
    unsigned int		m_Val; 
    unsigned int		m_MaxVal;

	// UI layout settings
	std::string			m_PanelSprStr;
	std::string			m_BarSprStr;
	OGVec2				m_Size;
    OGVec2				m_Position;
	OGVec2				m_BarPos;
	OGVec2				m_BarSize;
	int					m_MaxBars;
};


#endif
