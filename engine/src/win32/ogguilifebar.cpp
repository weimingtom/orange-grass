/*
 *  OGGuiLifebar.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogguilifebar.h"


COGGuiLifebar::COGGuiLifebar ()
{
	m_pResourceMgr = GetResourceMgr();
    m_pFrame = NULL;
    m_pBar = NULL;

    m_Val = 0;
    m_MaxVal = 0;
}


COGGuiLifebar::~COGGuiLifebar()
{
    Unload();
}


// Load graphics.
void COGGuiLifebar::Load ()
{
    m_pFrame = m_pResourceMgr->GetSprite(OG_RESPOOL_GAME, "life_hud");
    m_pBar = m_pResourceMgr->GetSprite(OG_RESPOOL_GAME, "greenbar_hud");
    m_Size = Vec2(256.0f, 32.0f);
    m_Position = Vec2(0, 0);
}


// Unload graphics.
void COGGuiLifebar::Unload ()
{
	m_pResourceMgr->ReleaseSprite(m_pFrame);
	m_pResourceMgr->ReleaseSprite(m_pBar);
}


// Update data.
void COGGuiLifebar::UpdateData (unsigned int _Val, unsigned int _MaxVal)
{
    m_Val = _Val;
    m_MaxVal = _MaxVal;
}


// Render sprite.
void COGGuiLifebar::Render ()
{
    float fMaxBars = 42.0f;
    float fLifePercent = (float)m_Val / (float)m_MaxVal;
    unsigned int NumBars = (unsigned int)(fLifePercent * fMaxBars);
    Vec2 vOffset = Vec2(17.0f, 10.0f);

    for (unsigned int i = 0; i < NumBars; ++i)
    {
        Vec2 vSize = Vec2(4.0f, 19.0f);
        if (i == 41 || i == 40)
        {
            vSize.y = 14.0f;
        }
        m_pBar->Render(Vec2(vOffset.x + i * 5, vOffset.y), vSize);
    }

    m_pFrame->Render(m_Position, m_Size);

}
