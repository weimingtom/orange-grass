/*
 *  OGFog.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
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
	virtual void SetColor (const Vec4& _vColor);
	
	// get light color.
	virtual const Vec4& GetColor () const {return m_Color;}

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

	Vec4	m_Color;
	float	m_fStart;
	float	m_fEnd;
	float	m_fDensity;
    bool    m_bEnabled;
};

#endif
