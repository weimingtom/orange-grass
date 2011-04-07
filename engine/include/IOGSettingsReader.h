/*
 *  IOGSettingsReader.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGSETTINGSREADER_H_
#define IOGSETTINGSREADER_H_

#include <string>
#include "Mathematics.h"
#include "IOGActorParams.h"
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

	// read Vec2 parameter.
	virtual Vec2 ReadVec2Param (
		IOGGroupNode* _pGroup, 
		const std::string& _AliasX, 
		const std::string& _AliasY) = 0;

	// write Vec2 parameter.
	virtual void WriteVec2Param (
		IOGGroupNode* _pGroup, 
		const std::string& _AliasX, 
		const std::string& _AliasY,
		const Vec2& _Value) = 0;

	// read Vec3 parameter.
	virtual Vec3 ReadVec3Param (
		IOGGroupNode* _pGroup, 
		const std::string& _AliasX, 
		const std::string& _AliasY,
		const std::string& _AliasZ) = 0;

	// write Vec3 parameter.
	virtual void WriteVec3Param (
		IOGGroupNode* _pGroup, 
		const std::string& _AliasX, 
		const std::string& _AliasY,
		const std::string& _AliasZ,
		const Vec3& _Value) = 0;

	// read Vec4 parameter.
	virtual Vec4 ReadVec4Param (
		IOGGroupNode* _pGroup, 
		const std::string& _AliasX, 
		const std::string& _AliasY,
		const std::string& _AliasZ,
		const std::string& _AliasW) = 0;

	// write Vec4 parameter.
	virtual void WriteVec4Param (
		IOGGroupNode* _pGroup, 
		const std::string& _AliasX, 
		const std::string& _AliasY,
		const std::string& _AliasZ,
		const std::string& _AliasW,
		const Vec4& _Value) = 0;

	// close source.
	virtual void CloseSource (IOGSettingsSource* _pSource) = 0;
};


#endif
