/*
 * OrangeGrass
 * Copyright (C) 2009 Vyacheslav Bogdanov.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/lgpl-3.0-standalone.html>.
 */
#ifndef OGSPRITEPOOL_H_
#define OGSPRITEPOOL_H_

#include "IOGSpritePool.h"


class COGSpritePool : public IOGSpritePool
{
public:
	COGSpritePool ();
	virtual ~COGSpritePool ();

	// add sprite.
	virtual void AddSprite (IOGSprite* _pSprite);

	// remove sprite.
	virtual void RemoveSprite (IOGSprite* _pSprite);

	// create button.
	virtual IOGGuiButton* CreateButton ();

	// desroy button.
	virtual void DestroyButton (IOGGuiButton* _pBtn);

	// create life bar.
	virtual IOGGuiLifebar* CreateLifebar ();

	// desroy life bar.
	virtual void DestroyLifebar (IOGGuiLifebar* _pBar);

	// create bonus bar.
	virtual IOGGuiBonusbar* CreateBonusbar ();

	// desroy bonus bar.
	virtual void DestroyBonusbar (IOGGuiBonusbar* _pBar);

	// create weapon panel.
	virtual IOGGuiWeaponPanel* CreateWeaponPanel ();

	// desroy weapon panel.
	virtual void DestroyWeaponPanel (IOGGuiWeaponPanel* _pPanel);
};

#endif
