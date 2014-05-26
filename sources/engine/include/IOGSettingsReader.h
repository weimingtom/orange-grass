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
#ifndef IOGSETTINGSREADER_H_
#define IOGSETTINGSREADER_H_

#include <string>
#include "IOGMath.h"
#include "IOGRenderer.h"


struct IOGSettingsSource
{
	std::string name;
};


struct IOGGroupNode
{
	IOGSettingsSource* pSource;
	IOGGroupNode* pParent;
	std::string name;
	int index;
};


class IOGSettingsReader
{
public:
	virtual ~IOGSettingsReader() {}

	// open settings source.
	virtual IOGSettingsSource* OpenSource (const std::string& _File) = 0;

	// save settings source.
	virtual bool SaveSource (IOGSettingsSource* _pSource, const std::string& _File) = 0;

	// read group node.
	virtual IOGGroupNode* OpenGroupNode (IOGSettingsSource* _pSource, IOGGroupNode* pParent, const std::string& _Alias) = 0;

	// close group node.
	virtual void CloseGroupNode (IOGGroupNode* _pNode) = 0;

	// read next group node.
	virtual IOGGroupNode* ReadNextNode (IOGGroupNode* _pNode) = 0;

	// read string parameter.
	virtual std::string ReadStringParam (IOGGroupNode* _pGroup, const std::string& _Alias) = 0;

	// write string parameter.
	virtual void WriteStringParam (IOGGroupNode* _pGroup, const std::string& _Alias, const std::string& _Value) = 0;

	// read int parameter.
	virtual int ReadIntParam (IOGGroupNode* _pGroup, const std::string& _Alias) = 0;

	// write int parameter.
	virtual void WriteIntParam (IOGGroupNode* _pGroup, const std::string& _Alias, int _Value) = 0;

	// read float parameter.
	virtual float ReadFloatParam (IOGGroupNode* _pGroup, const std::string& _Alias) = 0;

	// write float parameter.
	virtual void WriteFloatParam (IOGGroupNode* _pGroup, const std::string& _Alias, float _Value) = 0;

	// read OGVec2 parameter.
	virtual OGVec2 ReadVec2Param (
		IOGGroupNode* _pGroup, 
		const std::string& _AliasX, 
		const std::string& _AliasY) = 0;

	// write OGVec2 parameter.
	virtual void WriteVec2Param (
		IOGGroupNode* _pGroup, 
		const std::string& _AliasX, 
		const std::string& _AliasY,
		const OGVec2& _Value) = 0;

	// read OGVec3 parameter.
	virtual OGVec3 ReadVec3Param (
		IOGGroupNode* _pGroup, 
		const std::string& _AliasX, 
		const std::string& _AliasY,
		const std::string& _AliasZ) = 0;

	// write OGVec3 parameter.
	virtual void WriteVec3Param (
		IOGGroupNode* _pGroup, 
		const std::string& _AliasX, 
		const std::string& _AliasY,
		const std::string& _AliasZ,
		const OGVec3& _Value) = 0;

	// read OGVec4 parameter.
	virtual OGVec4 ReadVec4Param (
		IOGGroupNode* _pGroup, 
		const std::string& _AliasX, 
		const std::string& _AliasY,
		const std::string& _AliasZ,
		const std::string& _AliasW) = 0;

	// write OGVec4 parameter.
	virtual void WriteVec4Param (
		IOGGroupNode* _pGroup, 
		const std::string& _AliasX, 
		const std::string& _AliasY,
		const std::string& _AliasZ,
		const std::string& _AliasW,
		const OGVec4& _Value) = 0;

	// close source.
	virtual void CloseSource (IOGSettingsSource* _pSource) = 0;
};


#endif
