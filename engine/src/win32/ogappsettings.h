/*
 *  OGAppSettings.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGAPPSETTINGS_H_
#define OGAPPSETTINGS_H_

#include "IOGAppSettings.h"
#include "IOGSettingsReader.h"
#include "IOGGlobalVarsTable.h"


class COGAppSettings : public IOGAppSettings
{
public:
	COGAppSettings();
	virtual ~COGAppSettings();

	// read settings file.
	virtual bool Init (const std::string& _File);

private:

	// read screen mode settings file.
	bool InitScreenMode ();

private:

	bool				m_bInitialized;
	IOGSettingsReader*	m_pReader;
	IOGGlobalVarsTable*	m_pGlobalVars;
};


#endif
