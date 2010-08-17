/*
 *  ogresource.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGRESOURCE_H_
#define OGRESOURCE_H_

#include "IOGCoreHelpers.h"
#include <string>


// maximal path length
#define OG_MAX_PATH		2048

// Resource types
enum OGResourceTypes
{
    OG_RES_UNKNOWN,
    OG_RES_TEXTURE,
    OG_RES_MESH,
    OG_RES_ANIMATEDMESH,
    OG_RES_MODEL,
    OG_RES_TERRAIN,
    OG_RES_LEVEL,
};


// Resource loading state
enum OGResourceState
{
    OG_RESSTATE_UNKNOWN,
    OG_RESSTATE_DEFINED,
    OG_RESSTATE_LOADING,
    OG_RESSTATE_LOADED,
};


// Base resource class
class COGResource
{
public:
    // Constructor
    COGResource ();

    // Destructor
    virtual ~COGResource ();

    // Initialize
    void Init (const std::string& _Alias, const std::string& _File);

    // Load resource (actual loading goes here)
    virtual bool Load () = 0;

	// Unload resource.
	virtual void Unload () = 0;

    // get resource file name
    const std::string& GetResourceFile () const;

    // get resource alias
    const std::string& GetResourceAlias () const;

    // get resource load state
    OGResourceState GetLoadState () const;

    // get resource type
    OGResourceTypes GetResourceType () const;

protected:

    std::string		m_ResourceFile;
    std::string		m_ResourceAlias;
    OGResourceTypes m_ResourceType;
    OGResourceState m_LoadState;
};

#endif