/*
 *  oglight.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "oglight.h"
#include <algorithm>


COGLightMgr::COGLightMgr ()
{
    m_Lights.reserve(8);
}


COGLightMgr::~COGLightMgr ()
{
}


// add light.
IOGLight* COGLightMgr::CreateLight ()
{
    if (m_Lights.size() < 8)
    {
        IOGLight* pLight = new IOGLight;
        m_Lights.push_back(pLight);
        return pLight;
    }
    return NULL;
}


// destroy light.
void COGLightMgr::DestroyLight (IOGLight* _pLight)
{
	std::vector<IOGLight*>::iterator iter = std::find(m_Lights.begin(), m_Lights.end(), _pLight);
	if (iter != m_Lights.end())
	{
		OG_SAFE_DELETE((*iter));
		m_Lights.erase(iter);
	}
}


// get light.
IOGLight* COGLightMgr::GetLight (unsigned int _Id)
{
    if (m_Lights.size() <= _Id)
    {
        return NULL;
    }

    return m_Lights[_Id];
}
