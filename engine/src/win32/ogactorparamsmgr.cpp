/*
 *  OGActorParamsMgr.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogactorparamsmgr.h"
#include "Pathes.h"
#include "tinyxml.h"


COGActorParamsMgr::COGActorParamsMgr ()
{
}


COGActorParamsMgr::~COGActorParamsMgr ()
{
	std::map<std::string, IOGActorParams*>::iterator iter = m_ParamsList.begin();
	for( ; iter != m_ParamsList.end(); ++iter )
	{
		OG_SAFE_DELETE (iter->second);
	}	
}


// load from config file.
bool COGActorParamsMgr::Init ()
{
	std::string file_path;
	file_path = GetResourceMgr()->GetResourcePath() + std::string("/actors.xml");

    TiXmlDocument* pXmlSettings = new TiXmlDocument ("actors.xml");
	if (!pXmlSettings->LoadFile (file_path.c_str()))
	{
		OG_SAFE_DELETE(pXmlSettings);
        return false;
	}

    TiXmlHandle* hDoc = new TiXmlHandle (pXmlSettings);
    TiXmlHandle hParamsRoot = hDoc->FirstChild ( "Actors" );

	int index = 0;
    TiXmlHandle ParamsHandle = hParamsRoot.Child ( "Actor", index );
    while (ParamsHandle.Node ())
    {
        TiXmlElement* pElement = ParamsHandle.Element();

		std::string alias = std::string(pElement->Attribute ("alias"));
		std::string file = std::string(pElement->Attribute ("file"));
		std::string path = GetResourceMgr()->GetResourcePath() + std::string("/") + file;
		LoadParamsConfig(alias, path);

        ParamsHandle = hParamsRoot.Child ( "Actor", ++index );
    }

	OG_SAFE_DELETE(hDoc);
	OG_SAFE_DELETE(pXmlSettings);
	return true;
}


// get params by alias.
IOGActorParams* COGActorParamsMgr::GetParams (const std::string& _Alias)
{
	IOGActorParams* pParam = m_ParamsList[_Alias];
	if (pParam)
	{
		return pParam;
	}
    return NULL;
}


// Load actor params configuration
bool COGActorParamsMgr::LoadParamsConfig (const std::string& _Alias, const std::string& _Path)
{
	TiXmlDocument* pXmlSettings = new TiXmlDocument (_Alias.c_str());
	if (!pXmlSettings->LoadFile (_Path.c_str()))
	{
		OG_SAFE_DELETE(pXmlSettings);
        return false;
	}

	IOGActorParams* pParam = new IOGActorParams;
	pParam->alias = _Alias;

    TiXmlHandle* hDoc = new TiXmlHandle (pXmlSettings);
    TiXmlHandle hParamsRoot = hDoc->FirstChild("Params");

    TiXmlHandle PhysicsParamsHandle = hParamsRoot.FirstChild("Physics");
    if (PhysicsParamsHandle.Node ())
    {
        TiXmlElement* pElement = PhysicsParamsHandle.Element();

		double MaxSpeed = 0;
		pElement->Attribute ("max_speed", &MaxSpeed);
		pParam->physics.fMaxSpeed = (float)MaxSpeed;
    }
    TiXmlHandle ActorsParamsHandle = hParamsRoot.FirstChild("Actor");
    if (ActorsParamsHandle.Node ())
    {
        TiXmlElement* pElement = ActorsParamsHandle.Element();

		pParam->model_alias = std::string(pElement->Attribute ("model"));
		pParam->type = ParseActorType(std::string(pElement->Attribute ("type")));
		pParam->icon = std::string(pElement->Attribute ("icon"));
    }

	m_ParamsList[_Alias] = pParam;

	OG_SAFE_DELETE(hDoc);
	OG_SAFE_DELETE(pXmlSettings);
	return true;
}


// get params list.
void COGActorParamsMgr::GetParamsList (std::list<IOGActorParams*>& _List)
{
	_List.clear();
	std::map<std::string, IOGActorParams*>::iterator iter = m_ParamsList.begin();
	for( ; iter != m_ParamsList.end(); ++iter )
	{
		_List.push_back(iter->second);
	}	
}
