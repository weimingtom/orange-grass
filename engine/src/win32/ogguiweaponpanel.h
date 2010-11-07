/*
 *  OGGuiWeaponPanel.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGGUIWEAPONPANEL_H_
#define OGGUIWEAPONPANEL_H_

#include "IOGGuiWeaponPanel.h"


class COGGuiWeaponPanel :   public IOGGuiWeaponPanel
{
public:
    COGGuiWeaponPanel ();
	virtual ~COGGuiWeaponPanel();

	// Load graphics.
    virtual void Load ();

	// Unload graphics.
    virtual void Unload ();

	// Update data.
	virtual void UpdateData (const std::string& _SprWeapon);

	// Render sprite.
	virtual void Render ();

	// Hit test.
	virtual bool IsHit (const Vec2& _vPos);

protected:

	IOGResourceMgr*	m_pResourceMgr;
    IOGSprite*      m_pFrame;
    IOGSprite*      m_pWeapon;
    Vec2            m_Size;
    Vec2            m_Position;
};


#endif
