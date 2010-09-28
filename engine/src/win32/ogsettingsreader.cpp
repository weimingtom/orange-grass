/*
 *  OGSettingsReader.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogsettingsreader.h"


COGSettingsReader::COGSettingsReader()
{
}


COGSettingsReader::~COGSettingsReader()
{
}

// open settings source.
IOGSettingsSource* COGSettingsReader::OpenSource (const std::string& _File)
{
	COGSettingsSource* pSource = new COGSettingsSource;

    pSource->pSource = new TiXmlDocument (_File.c_str());
	if (!pSource->pSource->LoadFile (_File.c_str()))
	{
		OG_SAFE_DELETE((TiXmlDocument*)pSource->pSource);
        return NULL;
	}

    pSource->pDoc = new TiXmlHandle (pSource->pSource);
	return pSource;
}


// close source.
void COGSettingsReader::CloseSource (IOGSettingsSource* _pSource)
{
	COGSettingsSource* pSource = (COGSettingsSource*)_pSource;

	OG_SAFE_DELETE(pSource->pDoc);
	OG_SAFE_DELETE(pSource->pSource);
	OG_SAFE_DELETE(pSource);
}


// read group node.
IOGGroupNode* COGSettingsReader::OpenGroupNode (
	IOGSettingsSource* _pSource, 
	IOGGroupNode* _pParent, 
	const std::string& _Alias)
{
	COGGroupNode* pGroup = new COGGroupNode;
	pGroup->index = 0;
	pGroup->name = _Alias;
	if (_pParent)
	{
		pGroup->pParent = _pParent;
		pGroup->pNode = new TiXmlHandle(((COGGroupNode*)pGroup->pParent)->pNode->Child ( pGroup->name.c_str(), pGroup->index ));
		pGroup->pElement = pGroup->pNode->Element();
	}
	else
	{
		pGroup->pParent = NULL;
		pGroup->pElement = NULL;
		pGroup->pNode = ((COGSettingsSource*)_pSource)->pDoc->Child ( pGroup->name.c_str(), pGroup->index ));
	}
	return pGroup;
}


// close group node.
void COGSettingsReader::CloseGroupNode (IOGGroupNode* _pNode)
{
	COGGroupNode* pGroup = (COGGroupNode*)_pNode;
	OG_SAFE_DELETE(pGroup->pNode);
	OG_SAFE_DELETE(pGroup);
}


// read next group node.
IOGGroupNode* COGSettingsReader::ReadNextNode (IOGGroupNode* _pNode)
{
}


// read string parameter.
std::string COGSettingsReader::ReadStringParam (IOGGroupNode* _pGroup, const std::string& _Alias)
{
	return std::string("");
}


// read int parameter.
int COGSettingsReader::ReadIntParam (const std::string& _Alias)
{
	return 0;
}


// read float parameter.
float COGSettingsReader::ReadFloatParam (const std::string& _Alias)
{
	return 0.0f;
}
