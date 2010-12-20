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


class COGLightMgr : public IOGLightMgr
{
public:
	COGLightMgr ();
	virtual ~COGLightMgr ();
    
    // destroy all lights.
    virtual void Clear ();

	// add light.
	virtual IOGLight* CreateLight ();

	// destroy light.
	virtual void DestroyLight (IOGLight* _pLight);

	// get light.
	virtual IOGLight* GetLight (unsigned int _Id);

private:

    std::vector<IOGLight*> m_Lights;
};

#endif
