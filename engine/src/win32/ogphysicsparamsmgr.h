/*
 *  OGPhysicsParamsMgr.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGPHYSICSPARAMSMGR_H_
#define OGPHYSICSPARAMSMGR_H_

#include "IOGPhysicalObject.h"
#include <map>


class COGPhysicsParamsMgr
{
public:
	COGPhysicsParamsMgr ();
	virtual ~COGPhysicsParamsMgr ();

	// load from config file.
	virtual bool Init ();
	
	// get params by alias.
	virtual IOGPhysicalParams* GetParams (const std::string& _Alias);

private:

    std::map<std::string, IOGPhysicalParams*>	m_ParamsList;
};

#endif
