/*
 *  IOGGuiWeaponPanel.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGGUIWEAPONPANEL_H_
#define IOGGUIWEAPONPANEL_H_

#include "IOGMath.h"
#include <string>
#include "IOGSettingsReader.h"


class IOGGuiWeaponPanel
{
public:
	virtual ~IOGGuiWeaponPanel() {}

	// Load graphics.
    virtual void Load (IOGGroupNode* _pNode) = 0;

	// Unload graphics.
    virtual void Unload () = 0;

	// Update data.
	virtual void UpdateData (const std::string& _SprWeapon) = 0;

	// Render sprite.
	virtual void Render () = 0;

	// Hit test.
	virtual bool IsHit (const OGVec2& _vPos) = 0;
};


#endif
