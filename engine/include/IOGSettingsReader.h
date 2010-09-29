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

	// read group node.
	virtual IOGGroupNode* OpenGroupNode (IOGSettingsSource* _pSource, IOGGroupNode* pParent, const std::string& _Alias) = 0;

	// close group node.
	virtual void CloseGroupNode (IOGGroupNode* _pNode) = 0;

	// read next group node.
	virtual IOGGroupNode* ReadNextNode (IOGGroupNode* _pNode) = 0;

	// read string parameter.
	virtual std::string ReadStringParam (IOGGroupNode* _pGroup, const std::string& _Alias) = 0;

	// read int parameter.
	virtual int ReadIntParam (IOGGroupNode* _pGroup, const std::string& _Alias) = 0;

	// read float parameter.
	virtual float ReadFloatParam (IOGGroupNode* _pGroup, const std::string& _Alias) = 0;

	// close source.
	virtual void CloseSource (IOGSettingsSource* _pSource) = 0;
};


#endif
