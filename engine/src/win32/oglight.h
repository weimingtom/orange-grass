/*
 *  oglight.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGLIGHT_H_
#define OGLIGHT_H_

#include "IOGLight.h"
#include <vector>


class COGLight : public IOGLight
{
public:
	COGLight ();
	virtual ~COGLight ();

	// set light color.
	virtual void SetMainLightColor (const Vec4& _vColor);
	
	// get light color.
	virtual const Vec4& GetMainLightColor () const { return m_vColor; }
	
	// set light direction.
	virtual void SetMainLightDirection (const Vec3& _vDirection);
	
	// get light direction.
	virtual const Vec3& GetMainLightDirection () const { return m_vDirection; }

	// add light.
	virtual IOGPointLight* CreatePointLight ();

	// add light.
	virtual void DestroyPointLight (IOGPointLight* _pLight);

	// get light.
	virtual IOGPointLight* GetPointLight (unsigned int _Id);

private:

	Vec3	m_vDirection;
	Vec4	m_vColor;

    std::vector<IOGPointLight*> m_Lights;
};

#endif
