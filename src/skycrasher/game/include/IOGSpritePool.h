/*
 *  IOGSpritePool.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
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
