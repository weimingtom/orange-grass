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
		pGroup->pNode = new TiXmlHandle(((COGSettingsSource*)_pSource)->pDoc->Child ( pGroup->name.c_str(), pGroup->index ));
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
    TiXmlHandle* pNewNode = new TiXmlHandle(((COGGroupNode*)_pNode->pParent)->pNode->Child ( _pNode->name.c_str(), _pNode->index + 1 ));
    if (pNewNode->Node())
    {
        COGGroupNode* pNode = (COGGroupNode*)_pNode;
    	OG_SAFE_DELETE(pNode->pNode);
        pNode->pNode = pNewNode;
        pNode->index++;
        pNode->pElement = pNode->pNode->Element();
		return pNode;
    }
	else
	{
		OG_SAFE_DELETE(pNewNode);
		CloseGroupNode(_pNode);
		return NULL;
	}
}


// read string parameter.
std::string COGSettingsReader::ReadStringParam (IOGGroupNode* _pGroup, const std::string& _Alias)
{
	COGGroupNode* pNode = (COGGroupNode*)_pGroup;
	if (!pNode->pElement)
		return std::string("");

	return std::string(pNode->pElement->Attribute (_Alias.c_str()));
}


// read int parameter.
int COGSettingsReader::ReadIntParam (IOGGroupNode* _pGroup, const std::string& _Alias)
{
	int val = 0;
	COGGroupNode* pNode = (COGGroupNode*)_pGroup;
	if (!pNode->pElement)
		return val;

	pNode->pElement->Attribute (_Alias.c_str(), &val);
	return val;
}


// read float parameter.
float COGSettingsReader::ReadFloatParam (IOGGroupNode* _pGroup, const std::string& _Alias)
{
	double val = 0.0;
	COGGroupNode* pNode = (COGGroupNode*)_pGroup;
	if (!pNode->pElement)
		return 0.0f;

	pNode->pElement->Attribute (_Alias.c_str(), &val);
	return (float)val;
}


// read Vec2 parameter.
Vec2 COGSettingsReader::ReadVec2Param (
							IOGGroupNode* _pGroup, 
							const std::string& _AliasX, 
							const std::string& _AliasY)
{
	Vec2 vOut;
	vOut.x = ReadFloatParam(_pGroup, _AliasX);
	vOut.y = ReadFloatParam(_pGroup, _AliasY);
	return vOut;
}


// read Vec3 parameter.
Vec3 COGSettingsReader::ReadVec3Param (
							IOGGroupNode* _pGroup, 
							const std::string& _AliasX, 
							const std::string& _AliasY,
							const std::string& _AliasZ)
{
	Vec3 vOut;
	vOut.x = ReadFloatParam(_pGroup, _AliasX);
	vOut.y = ReadFloatParam(_pGroup, _AliasY);
	vOut.z = ReadFloatParam(_pGroup, _AliasZ);
	return vOut;
}


// read Vec4 parameter.
Vec4 COGSettingsReader::ReadVec4Param (
							IOGGroupNode* _pGroup, 
							const std::string& _AliasX, 
							const std::string& _AliasY,
							const std::string& _AliasZ,
							const std::string& _AliasW)
{
	Vec4 vOut;
	vOut.x = ReadFloatParam(_pGroup, _AliasX);
	vOut.y = ReadFloatParam(_pGroup, _AliasY);
	vOut.z = ReadFloatParam(_pGroup, _AliasZ);
	vOut.w = ReadFloatParam(_pGroup, _AliasW);
	return vOut;
}
