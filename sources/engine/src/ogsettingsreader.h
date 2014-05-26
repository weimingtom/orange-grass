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
#ifndef OGSETTINGSREADER_H_
#define OGSETTINGSREADER_H_

#include "IOGSettingsReader.h"
#include "tinyxml/tinyxml.h"


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

	// read OGVec2 parameter.
	virtual OGVec2 ReadVec2Param (
		IOGGroupNode* _pGroup, 
		const std::string& _AliasX, 
		const std::string& _AliasY);

	// write OGVec2 parameter.
	virtual void WriteVec2Param (
		IOGGroupNode* _pGroup, 
		const std::string& _AliasX, 
		const std::string& _AliasY,
		const OGVec2& _Value);

	// read OGVec3 parameter.
	virtual OGVec3 ReadVec3Param (
		IOGGroupNode* _pGroup, 
		const std::string& _AliasX, 
		const std::string& _AliasY,
		const std::string& _AliasZ);

	// write OGVec3 parameter.
	virtual void WriteVec3Param (
		IOGGroupNode* _pGroup, 
		const std::string& _AliasX, 
		const std::string& _AliasY,
		const std::string& _AliasZ,
		const OGVec3& _Value);

	// read OGVec4 parameter.
	virtual OGVec4 ReadVec4Param (
		IOGGroupNode* _pGroup, 
		const std::string& _AliasX, 
		const std::string& _AliasY,
		const std::string& _AliasZ,
		const std::string& _AliasW);

	// write OGVec4 parameter.
	virtual void WriteVec4Param (
		IOGGroupNode* _pGroup, 
		const std::string& _AliasX, 
		const std::string& _AliasY,
		const std::string& _AliasZ,
		const std::string& _AliasW,
		const OGVec4& _Value);

	// close source.
	virtual void CloseSource (IOGSettingsSource* _pSource);
};


#endif
