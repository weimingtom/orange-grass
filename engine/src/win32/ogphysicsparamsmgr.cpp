/*
 *  OGPhysicsParamsMgr.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogphysicsparamsmgr.h"
#include "Pathes.h"
#include "tinyxml.h"


COGPhysicsParamsMgr::COGPhysicsParamsMgr ()
{
}


COGPhysicsParamsMgr::~COGPhysicsParamsMgr ()
{
}


// load from config file.
bool COGPhysicsParamsMgr::Init ()
{
    return true;
}


// get params by alias.
IOGPhysicalParams* COGPhysicsParamsMgr::GetParams (const std::string& _Alias)
{
    return NULL;
}
