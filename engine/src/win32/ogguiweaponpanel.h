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
    virtual void Load (IOGGroupNode* _pNode);

	// Unload graphics.
    virtual void Unload ();

	// Update data.
	virtual void UpdateData (const std::string& _SprWeapon);

	// Render sprite.
	virtual void Render ();

	// Hit test.
	virtual bool IsHit (const Vec2& _vPos);

protected:

	IOGSettingsReader*	m_pReader;
	IOGResourceMgr*		m_pResourceMgr;
    IOGSprite*			m_pFrame;
    IOGSprite*			m_pWeapon;

	// UI layout settings
	std::string			m_HUDSprStr;
	Vec2				m_Size;
    Vec2				m_Position;
	Vec2				m_WeaponIconPos;
	Vec2				m_WeaponIconSize;
};


#endif
