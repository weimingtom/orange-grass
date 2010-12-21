/*
 *  OGGuiBonusbar.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogguibonusbar.h"


COGGuiBonusbar::COGGuiBonusbar ()
{
	m_pResourceMgr = GetResourceMgr();
    m_pFrame = NULL;
    m_pCooldown = NULL;

    m_Entries.reserve(4);
    for (int i = 0; i < 4; ++i)
    {
        BonusEntry bonus;
        bonus.m_MaxVal = 0;
        bonus.m_Val = 0;
        bonus.m_pBonus = NULL;
        m_Entries.push_back(bonus);
    }
}


COGGuiBonusbar::~COGGuiBonusbar()
{
    Unload();
}


// Load graphics.
void COGGuiBonusbar::Load ()
{
    m_pFrame = m_pResourceMgr->GetSprite(OG_RESPOOL_GAME, "spec_hud");
    m_pCooldown = m_pResourceMgr->GetSprite(OG_RESPOOL_GAME, "greenline_hud");
    m_Size = Vec2(90.0f, 60.0f);
    m_Position = Vec2(0, 40);
}


// Unload graphics.
void COGGuiBonusbar::Unload ()
{
	m_pResourceMgr->ReleaseSprite(m_pFrame);
	m_pResourceMgr->ReleaseSprite(m_pCooldown);
}


// Update data.
void COGGuiBonusbar::SetData (unsigned int _Id, 
                              const std::string& _SprBonus, 
                              unsigned int _Val, 
                              unsigned int _MaxVal)
{
    BonusEntry& bonus = m_Entries[_Id];
    bonus.m_MaxVal = _MaxVal;
    bonus.m_Val = _Val;
    bonus.m_pBonus = m_pResourceMgr->GetSprite(OG_RESPOOL_GAME, _SprBonus);
}


// Render sprite.
void COGGuiBonusbar::Render ()
{
    Vec2 vOffset = Vec2(17.0f, 12.0f);
    Vec2 vCooldownOffset = Vec2(21.0f, 5.0f);

    unsigned int NumEntries = m_Entries.size();
    for (unsigned int i = 0; i < NumEntries; ++i)
    {
        BonusEntry& bonus = m_Entries[i];
        if (bonus.m_pBonus)
        {
            Vec2 vPos = m_Position + Vec2(0, (m_Size.y + 5) * i);
            m_pFrame->Render(m_Position + Vec2(0, (m_Size.y + 5) * i), m_Size);
            bonus.m_pBonus->Render(vPos + vOffset, Vec2(64.0f, 36.0f));
            if (bonus.m_MaxVal > 0)
            {
                float fPercent = (float)bonus.m_Val / (float)bonus.m_MaxVal;
                m_pCooldown->Render(vPos + vCooldownOffset, Vec2(56.0f * fPercent, 1.0f));
            }
        }
    }
}


// Reset data.
void COGGuiBonusbar::ResetData ()
{
    unsigned int NumEntries = m_Entries.size();
    for (unsigned int i = 0; i < NumEntries; ++i)
    {
        BonusEntry& bonus = m_Entries[i];
        bonus.m_pBonus = NULL;
        bonus.m_Val = bonus.m_MaxVal = 0;
    }
}
