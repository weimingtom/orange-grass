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
#include "Game.h"
#include "ogspritepool.h"
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
