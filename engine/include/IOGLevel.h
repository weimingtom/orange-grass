/*
 *  IOGLevel.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGLEVEL_H_
#define IOGLEVEL_H_

#include "IOGModel.h"
#include "IOGTerrain.h"


class IOGLevel
{
public:
	virtual ~IOGLevel () {}
		
	// get associated terrain.
	virtual IOGTerrain* GetTerrain () = 0;
		
	// get level start position.
	virtual const Vec3& GetStartPosition () const = 0;
		
	// get level start finish.
	virtual const Vec3& GetFinishPosition () const = 0;
	
	// save level.
	virtual bool Save () = 0;
};

#endif
