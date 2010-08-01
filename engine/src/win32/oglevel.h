/*
 *  OGLevel.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGLEVEL_H_
#define OGLEVEL_H_

#include "IOGModel.h"
#include "IOGTerrain.h"
#include "ogresource.h"


class COGLevel : public IOGLevel, public COGResource
{
public:
	COGLevel ();
	virtual ~COGLevel ();

	// load scene from file.
	virtual bool Load ();

	// get associated terrain.
	virtual IOGTerrain* GetTerrain ();

private:

    IOGTerrain* m_pTerrain;
};

#endif
