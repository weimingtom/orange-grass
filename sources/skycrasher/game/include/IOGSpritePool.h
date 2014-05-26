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
#ifndef IOGSPRITEPOOL_H_
#define IOGSPRITEPOOL_H_

#include "IOGSprite.h"
#include "IOGGuiButton.h"
#include "IOGGuiLifebar.h"
#include "IOGGuiBonusbar.h"
#include "IOGGuiWeaponPanel.h"


class IOGSpritePool
{
public:
	virtual ~IOGSpritePool () {}

	// add sprite.
	virtual void AddSprite (IOGSprite* _pSprite) = 0;

	// remove sprite.
	virtual void RemoveSprite (IOGSprite* _pSprite) = 0;

	// create button.
	virtual IOGGuiButton* CreateButton () = 0;

	// desroy button.
	virtual void DestroyButton (IOGGuiButton* _pBtn) = 0;

	// create life bar.
	virtual IOGGuiLifebar* CreateLifebar () = 0;

	// desroy life bar.
	virtual void DestroyLifebar (IOGGuiLifebar* _pBar) = 0;

	// create bonus bar.
	virtual IOGGuiBonusbar* CreateBonusbar () = 0;

	// desroy bonus bar.
	virtual void DestroyBonusbar (IOGGuiBonusbar* _pBar) = 0;

	// create weapon panel.
	virtual IOGGuiWeaponPanel* CreateWeaponPanel () = 0;

	// desroy weapon panel.
	virtual void DestroyWeaponPanel (IOGGuiWeaponPanel* _pPanel) = 0;
};

#endif
