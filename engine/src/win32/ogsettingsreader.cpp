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
	m_ActorTypeLookup["static"] = OG_ACTOR_STATIC;
	m_ActorTypeLookup["land_bot"] = OG_ACTOR_LANDBOT;
	m_ActorTypeLookup["air_bot"] = OG_ACTOR_AIRBOT;
	m_ActorTypeLookup["player"] = OG_ACTOR_PLAYER;
	m_ActorTypeLookup["plasma_missile"] = OG_ACTOR_PLASMAMISSILE;
	m_ActorTypeLookup["missile"] = OG_ACTOR_MISSILE;
	m_ActorTypeLookup["bonus"] = OG_ACTOR_BONUS;
	m_ActorTypeLookup["gaussray"] = OG_ACTOR_GAUSSRAY;

	m_BlendTypeLookup["solid"] = OG_BLEND_SOLID;
	m_BlendTypeLookup["test"] = OG_BLEND_ALPHATEST;
	m_BlendTypeLookup["blend"] = OG_BLEND_ALPHABLEND;
	m_BlendTypeLookup["add"] = OG_BLEND_ALPHAADD;
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
		OG_SAFE_DELETE(pSource->pSource);
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
	pGroup->pSource = _pSource;
	if (_pParent)
	{
		pGroup->pParent = _pParent;
		pGroup->pNode = new TiXmlHandle(((COGGroupNode*)pGroup->pParent)->pNode->Child ( pGroup->name.c_str(), pGroup->index ));
		pGroup->pElement = pGroup->pNode->Element();
		if (pGroup->pElement == NULL)
		{
			OG_SAFE_DELETE(pGroup->pNode);
			OG_SAFE_DELETE(pGroup);
			return NULL;
		}
	}
	else
	{
		pGroup->pParent = NULL;
		pGroup->pNode = new TiXmlHandle(((COGSettingsSource*)_pSource)->pDoc->Child ( pGroup->name.c_str(), pGroup->index ));
		pGroup->pElement = pGroup->pNode->Element();
		if (pGroup->pElement == NULL)
		{
			OG_SAFE_DELETE(pGroup->pNode);
			OG_SAFE_DELETE(pGroup);
			return NULL;
		}
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


// save settings source.
bool COGSettingsReader::SaveSource (IOGSettingsSource* _pSource, const std::string& _File)
{
	COGSettingsSource* pSource = (COGSettingsSource*)_pSource;
	return pSource->pSource->SaveFile(_File.c_str());
}


// write string parameter.
void COGSettingsReader::WriteStringParam (IOGGroupNode* _pGroup, const std::string& _Alias, const std::string& _Value)
{
	COGGroupNode* pNode = (COGGroupNode*)_pGroup;
	if (!pNode->pElement)
		return;

	pNode->pElement->SetAttribute (_Alias.c_str(), _Value.c_str());
}


// write int parameter.
void COGSettingsReader::WriteIntParam (IOGGroupNode* _pGroup, const std::string& _Alias, int _Value)
{
	COGGroupNode* pNode = (COGGroupNode*)_pGroup;
	if (!pNode->pElement)
		return;

	pNode->pElement->SetAttribute (_Alias.c_str(), _Value);
}


// write float parameter.
void COGSettingsReader::WriteFloatParam (IOGGroupNode* _pGroup, const std::string& _Alias, float _Value)
{
	COGGroupNode* pNode = (COGGroupNode*)_pGroup;
	if (!pNode->pElement)
		return;

	pNode->pElement->SetDoubleAttribute (_Alias.c_str(), (double)_Value);
}


// write Vec2 parameter.
void COGSettingsReader::WriteVec2Param (
							IOGGroupNode* _pGroup, 
							const std::string& _AliasX, 
							const std::string& _AliasY,
							const Vec2& _Value)
{
	WriteFloatParam(_pGroup, _AliasX, _Value.x);
	WriteFloatParam(_pGroup, _AliasY, _Value.y);
}


// write Vec3 parameter.
void COGSettingsReader::WriteVec3Param (
							IOGGroupNode* _pGroup, 
							const std::string& _AliasX, 
							const std::string& _AliasY,
							const std::string& _AliasZ,
							const Vec3& _Value)
{
	WriteFloatParam(_pGroup, _AliasX, _Value.x);
	WriteFloatParam(_pGroup, _AliasY, _Value.y);
	WriteFloatParam(_pGroup, _AliasZ, _Value.z);
}


// write Vec4 parameter.
void COGSettingsReader::WriteVec4Param (
							IOGGroupNode* _pGroup, 
							const std::string& _AliasX, 
							const std::string& _AliasY,
							const std::string& _AliasZ,
							const std::string& _AliasW,
							const Vec4& _Value)
{
	WriteFloatParam(_pGroup, _AliasX, _Value.x);
	WriteFloatParam(_pGroup, _AliasY, _Value.y);
	WriteFloatParam(_pGroup, _AliasZ, _Value.z);
	WriteFloatParam(_pGroup, _AliasW, _Value.w);
}


// read actor type parameter.
OGActorType COGSettingsReader::ReadActorTypeParam (IOGGroupNode* _pGroup, const std::string& _Alias)
{
	std::string ActorTypeStr = ReadStringParam(_pGroup, _Alias);

    std::map<std::string, OGActorType>::const_iterator iter = m_ActorTypeLookup.find(ActorTypeStr);
    if (iter != m_ActorTypeLookup.end())
    {
        return iter->second;
    }
    return OG_ACTOR_NONE;
}


// write actor type parameter.
void COGSettingsReader::WriteActorTypeParam (IOGGroupNode* _pGroup, const std::string& _Alias, OGActorType _Value)
{
	std::string ActorTypeStr;
    std::map<std::string, OGActorType>::const_iterator iter = m_ActorTypeLookup.begin();
	for (; iter != m_ActorTypeLookup.end(); ++iter)
	{
		if (iter->second == _Value)
		{
			ActorTypeStr = iter->first;
			break;
		}
	}
	
	WriteStringParam(_pGroup, _Alias, ActorTypeStr);
}


// read blend type parameter.
OGBlendType COGSettingsReader::ReadBlendTypeParam (IOGGroupNode* _pGroup, const std::string& _Alias)
{
	std::string BlendTypeStr = ReadStringParam(_pGroup, _Alias);

    std::map<std::string, OGBlendType>::const_iterator iter = m_BlendTypeLookup.find(BlendTypeStr);
    if (iter != m_BlendTypeLookup.end())
    {
        return iter->second;
    }
    return OG_BLEND_NO;
}


// write blend type parameter.
void COGSettingsReader::WriteBlendTypeParam (IOGGroupNode* _pGroup, const std::string& _Alias, OGBlendType _Value)
{
	std::string BlendTypeStr;
    std::map<std::string, OGBlendType>::const_iterator iter = m_BlendTypeLookup.begin();
	for (; iter != m_BlendTypeLookup.end(); ++iter)
	{
		if (iter->second == _Value)
		{
			BlendTypeStr = iter->first;
			break;
		}
	}
	
	WriteStringParam(_pGroup, _Alias, BlendTypeStr);
}
