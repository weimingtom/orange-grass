#define _CRT_SECURE_NO_WARNINGS
#include "ogresource.h"
#include <stdio.h>
#include <string.h>


// Constructor
COGResource::COGResource ()
{
    m_LoadState = OG_RESSTATE_UNKNOWN;
	memset(m_pResourceIcon, 0, OG_MAX_PATH);
	memset(m_pResourceAlias, 0, OG_MAX_PATH);
	memset(m_pResourceFile, 0, OG_MAX_PATH);
}


// Initialize
void COGResource::Init (const char* _pAlias, const char* _pFile)
{
    m_LoadState = OG_RESSTATE_DEFINED;
    sprintf(m_pResourceAlias, _pAlias);
    sprintf(m_pResourceFile, _pFile);
}


// Destructor
COGResource::~COGResource ()
{
    m_LoadState = OG_RESSTATE_UNKNOWN;
}


// get resource file name
const char* COGResource::GetResourceFile () const
{
    return m_pResourceFile;
}


// get resource alias
const char* COGResource::GetResourceAlias () const
{
    return m_pResourceAlias;
}


// get resource icon
const char* COGResource::GetResourceIcon () const
{
    return m_pResourceIcon;
}


// set resource icon
void COGResource::SetResourceIcon (const char* _pIcon)
{
    sprintf(m_pResourceIcon, _pIcon);
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
