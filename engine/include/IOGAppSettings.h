/*
 *  IOGAppSettings.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGAPPSETTINGS_H_
#define IOGAPPSETTINGS_H_

#include <string>


class IOGAppSettings
{
public:
	virtual ~IOGAppSettings() {}

	// read settings file.
	virtual bool Init (const std::string& _File) = 0;
};


#endif
