#ifndef OGRESOURCE_H_
#define OGRESOURCE_H_

#include "IOGCoreHelpers.h"


// maximal path length
#define OG_MAX_PATH		260

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
    void Init (const char* _pAlias, const char* _pFile);

    // Load resource (actual loading goes here)
    virtual bool Load () = 0;

    // get resource file name
    const char* GetResourceFile () const;

    // get resource alias
    const char* GetResourceAlias () const;

    // get resource icon
    const char* GetResourceIcon () const;

    // set resource icon
    void SetResourceIcon (const char* _pIcon);

    // get resource load state
    OGResourceState GetLoadState () const;

    // get resource type
    OGResourceTypes GetResourceType () const;

protected:

    char	m_pResourceFile[OG_MAX_PATH];
    char	m_pResourceAlias[OG_MAX_PATH];
    char	m_pResourceIcon[OG_MAX_PATH];
    OGResourceTypes m_ResourceType;
    OGResourceState m_LoadState;
};

#endif