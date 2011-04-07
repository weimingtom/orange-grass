/*
 *  OGSettingsReader.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGSETTINGSREADER_H_
#define OGSETTINGSREADER_H_

#include "IOGSettingsReader.h"
#include "tinyxml.h"


struct COGSettingsSource : public IOGSettingsSource
{
	TiXmlDocument* pSource;
	TiXmlHandle* pDoc;
};


struct COGGroupNode : public IOGGroupNode
{
	TiXmlHandle* pNode;
	TiXmlElement* pElement;
};


class COGSettingsReader : public IOGSettingsReader
{
public:
	COGSettingsReader();
	virtual ~COGSettingsReader();

	// open settings source.
	virtual IOGSettingsSource* OpenSource (const std::string& _File);

	// save settings source.
	virtual bool SaveSource (IOGSettingsSource* _pSource, const std::string& _File);

	// read group node.
	virtual IOGGroupNode* OpenGroupNode (IOGSettingsSource* _pSource, IOGGroupNode* pParent, const std::string& _Alias);

	// close group node.
	virtual void CloseGroupNode (IOGGroupNode* _pNode);

	// read next group node.
	virtual IOGGroupNode* ReadNextNode (IOGGroupNode* _pNode);

	// read string parameter.
	virtual std::string ReadStringParam (IOGGroupNode* _pGroup, const std::string& _Alias);

	// write string parameter.
	virtual void WriteStringParam (IOGGroupNode* _pGroup, const std::string& _Alias, const std::string& _Value);

	// read int parameter.
	virtual int ReadIntParam (IOGGroupNode* _pGroup, const std::string& _Alias);

	// write int parameter.
	virtual void WriteIntParam (IOGGroupNode* _pGroup, const std::string& _Alias, int _Value);

	// read float parameter.
	virtual float ReadFloatParam (IOGGroupNode* _pGroup, const std::string& _Alias);

	// write float parameter.
	virtual void WriteFloatParam (IOGGroupNode* _pGroup, const std::string& _Alias, float _Value);

	// read Vec2 parameter.
	virtual Vec2 ReadVec2Param (
		IOGGroupNode* _pGroup, 
		const std::string& _AliasX, 
		const std::string& _AliasY);

	// write Vec2 parameter.
	virtual void WriteVec2Param (
		IOGGroupNode* _pGroup, 
		const std::string& _AliasX, 
		const std::string& _AliasY,
		const Vec2& _Value);

	// read Vec3 parameter.
	virtual Vec3 ReadVec3Param (
		IOGGroupNode* _pGroup, 
		const std::string& _AliasX, 
		const std::string& _AliasY,
		const std::string& _AliasZ);

	// write Vec3 parameter.
	virtual void WriteVec3Param (
		IOGGroupNode* _pGroup, 
		const std::string& _AliasX, 
		const std::string& _AliasY,
		const std::string& _AliasZ,
		const Vec3& _Value);

	// read Vec4 parameter.
	virtual Vec4 ReadVec4Param (
		IOGGroupNode* _pGroup, 
		const std::string& _AliasX, 
		const std::string& _AliasY,
		const std::string& _AliasZ,
		const std::string& _AliasW);

	// write Vec4 parameter.
	virtual void WriteVec4Param (
		IOGGroupNode* _pGroup, 
		const std::string& _AliasX, 
		const std::string& _AliasY,
		const std::string& _AliasZ,
		const std::string& _AliasW,
		const Vec4& _Value);

	// close source.
	virtual void CloseSource (IOGSettingsSource* _pSource);
};


#endif
