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

#include "IOGGuiLifebar.h"
#include <vector>


class COGGuiBonusbar : public IOGGuiBonusbar
{
public:
    COGGuiBonusbar ();
	virtual ~COGGuiBonusbar();

	// Load graphics.
    virtual void Load ();

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

	IOGResourceMgr*	        m_pResourceMgr;
    IOGSprite*              m_pFrame;
    IOGSprite*              m_pCooldown;
    Vec2                    m_Size;
    Vec2                    m_Position;
    std::vector<BonusEntry> m_Entries;
};


#endif
