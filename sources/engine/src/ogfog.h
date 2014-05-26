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
#ifndef OGFOG_H_
#define OGFOG_H_

#include "IOGFog.h"


class COGFog : public IOGFog
{
public:
	COGFog ();
	virtual ~COGFog ();

	// set light color.
	virtual void SetColor (const OGVec4& _vColor);
	
	// get light color.
	virtual const OGVec4& GetColor () const {return m_Color;}

	// set fog start.
	virtual void SetStart (float _fStart);

	// set fog end.
	virtual void SetEnd (float _fEnd);

	// set fog density.
	virtual void SetDensity (float _fDensity);

	// set fog enabled status.
	virtual void SetEnabled (bool _bEnable);

	// get fog start.
	virtual float GetStart () const {return m_fStart;}

	// get fog end.
	virtual float GetEnd () const {return m_fEnd;}

	// get fog density.
	virtual float GetDensity () const {return m_fDensity;}

	// get fog enabled status.
    virtual bool IsEnabled () const {return m_bEnabled;}

private:

	OGVec4	m_Color;
	float	m_fStart;
	float	m_fEnd;
	float	m_fDensity;
    bool    m_bEnabled;
};

#endif
