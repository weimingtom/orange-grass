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
#include "Geometry.h"
#include "Mathematics.h"


class COGLight : public IOGLight
{
public:
	COGLight ();
	virtual ~COGLight ();

	// set light color.
	virtual void SetColor (const Vec4& _vColor);
	
	// get light color.
	virtual const Vec4& GetColor () const { return m_vColor; }
	
	// set light direction.
	virtual void SetDirection (const Vec4& _vDirection);
	
	// get light direction.
	virtual const Vec4& GetDirection () const { return m_vDirection; }
		
	// apply lighting.
	virtual void Apply ();
	
private:

	Vec4		m_vDirection;
	Vec4		m_vColor;
};

#endif
