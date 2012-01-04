/*
 *  OGSpritePool.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
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
