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


COGLight::COGLight ()
{
    m_Lights.reserve(8);
}


COGLight::~COGLight ()
{
}


// set light color.
void COGLight::SetMainLightColor (const Vec4& _vColor)
{
	//m_vColor = _vColor;
	m_vColor = Vec4(0.5f, 0.5f, 0.4f, 1.0f);
}


// set light direction.
void COGLight::SetMainLightDirection (const Vec3& _vDirection)
{
	m_vDirection = _vDirection;
}


// add light.
IOGPointLight* COGLight::CreatePointLight ()
{
    if (m_Lights.size() < 8)
    {
        IOGPointLight* pLight = new IOGPointLight;
        m_Lights.push_back(pLight);
        return pLight;
    }
    return NULL;
}


// add light.
void COGLight::DestroyPointLight (IOGPointLight* _pLight)
{
	std::vector<IOGPointLight*>::iterator iter = std::find(m_Lights.begin(), m_Lights.end(), _pLight);
	if (iter != m_Lights.end())
	{
		OG_SAFE_DELETE((*iter));
		m_Lights.erase(iter);
	}
}


// get light.
IOGPointLight* COGLight::GetPointLight (unsigned int _Id)
{
    if (m_Lights.size() <= _Id)
    {
        return NULL;
    }

    return m_Lights[_Id];
}
