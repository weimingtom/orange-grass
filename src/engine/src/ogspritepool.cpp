/*
 *  ogspritepool.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogspritepool.h"
#include "ogsprite.h"
#include "ogguibutton.h"
#include "ogguilifebar.h"
#include "ogguibonusbar.h"
#include "ogguiweaponpanel.h"


COGSpritePool::COGSpritePool ()
{
}


COGSpritePool::~COGSpritePool ()
{
}


// add sprite.
void COGSpritePool::AddSprite (IOGSprite* _pSprite)
{
}


// remove sprite.
void COGSpritePool::RemoveSprite (IOGSprite* _pSprite)
{
	OG_SAFE_DELETE(_pSprite);
}


// create button.
IOGGuiButton* COGSpritePool::CreateButton ()
{
    return new COGGuiButton();
}


// desroy button.
void COGSpritePool::DestroyButton (IOGGuiButton* _pBtn)
{
    OG_SAFE_DELETE(_pBtn);
}


// create life bar.
IOGGuiLifebar* COGSpritePool::CreateLifebar ()
{
    return new COGGuiLifebar();
}


// desroy life bar.
void COGSpritePool::DestroyLifebar (IOGGuiLifebar* _pBar)
{
    OG_SAFE_DELETE(_pBar);
}


// create bonus bar.
IOGGuiBonusbar* COGSpritePool::CreateBonusbar ()
{
    return new COGGuiBonusbar();
}


// desroy bonus bar.
void COGSpritePool::DestroyBonusbar (IOGGuiBonusbar* _pBar)
{
    OG_SAFE_DELETE(_pBar);
}


// create weapon panel.
IOGGuiWeaponPanel* COGSpritePool::CreateWeaponPanel ()
{
    return new COGGuiWeaponPanel();
}


// desroy weapon panel.
void COGSpritePool::DestroyWeaponPanel (IOGGuiWeaponPanel* _pPanel)
{
    OG_SAFE_DELETE(_pPanel);
}
