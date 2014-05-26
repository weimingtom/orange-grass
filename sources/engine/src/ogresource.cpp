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
#include "ogresource.h"
#include <stdio.h>
#include <string.h>


// Constructor
COGResource::COGResource ()
{
    m_LoadState = OG_RESSTATE_UNKNOWN;
}


// Initialize
void COGResource::Init (const std::string& _Alias, const std::string& _File, OGResourcePool _Pool)
{
    m_LoadState = OG_RESSTATE_DEFINED;
    m_ResourceAlias = _Alias;
    m_ResourceFile = _File;
	m_ResourcePool = _Pool;
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
