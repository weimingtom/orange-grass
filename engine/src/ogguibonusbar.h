/*
 *  OGGuiBonusbar.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGGUIBONUSBAR_H_
#define OGGUIBONUSBAR_H_

#include "IOGGuiBonusbar.h"
#include <vector>


class COGGuiBonusbar : public IOGGuiBonusbar
{
public:
    COGGuiBonusbar ();
	virtual ~COGGuiBonusbar();

	// Load graphics.
    virtual void Load (IOGGroupNode* _pNode);

	// Unload graphics.
    virtual void Unload ();

	// Update data.
	virtual void SetData (
        unsigned int _Id, 
        const std::string& _SprBonus, 
        unsigned int _Val, 
        unsigned int _MaxVal);

	// Render sprite.
	virtual void Render ();

	// Reset data.
    virtual void ResetData ();

protected:

    struct BonusEntry
    {
        IOGSprite*      m_pBonus;
        unsigned int    m_Val; 
        unsigned int    m_MaxVal;
    };

protected:

	IOGSettingsReader*		m_pReader;
	IOGResourceMgr*	        m_pResourceMgr;
    IOGSprite*              m_pFrame;
    IOGSprite*              m_pCooldown;
    std::vector<BonusEntry> m_Entries;

	// UI layout settings
	std::string				m_PanelSprStr;
	std::string				m_BarSprStr;
    Vec2                    m_Size;
    Vec2                    m_Position;
    Vec2					m_BonusIcoPos;
	Vec2					m_BonusIcoSize;
    Vec2					m_CoolDownBarPos;
	Vec2					m_CoolDownBarSize;
	float					m_fVertInterval;
};


#endif
