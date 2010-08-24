/*
 *  ogresource.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogresource.h"
#include <stdio.h>
#include <string.h>


// Constructor
COGResource::COGResource ()
{
    m_LoadState = OG_RESSTATE_UNKNOWN;
}


// Initialize
void COGResource::Init (const std::string& _Alias, const std::string& _File)
{
    m_LoadState = OG_RESSTATE_DEFINED;
    m_ResourceAlias = _Alias;
    m_ResourceFile = _File;
}


// Destructor
COGResource::~COGResource ()
{
    m_LoadState = OG_RESSTATE_UNKNOWN;
}


// get resource file name
const std::string& COGResource::GetResourceFile () const
{
    return m_ResourceFile;
}


// get resource alias
const std::string& COGResource::GetResourceAlias () const
{
    return m_ResourceAlias;
}


// get resource load state
OGResourceState COGResource::GetLoadState () const
{
    return m_LoadState;
}


// get resource type
OGResourceTypes COGResource::GetResourceType () const
{
    return m_ResourceType;
}
