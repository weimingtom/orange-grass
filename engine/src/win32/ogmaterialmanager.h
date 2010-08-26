/*
 *  OGMaterialManager.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGMATERIALMANAGER_H_
#define OGMATERIALMANAGER_H_

#include "IOGMaterialManager.h"
#include <map>


class COGMaterialManager : public IOGMaterialManager
{
public:
	COGMaterialManager ();
	virtual ~COGMaterialManager ();
		
	// initialize materials.
	virtual bool Init ();

	// get material.
	virtual IOGMaterial* GetMaterial (const std::string& _Alias);

	// get material.
	virtual IOGMaterial* GetMaterial (OGMaterialType _Type);

    // parse material type
	static OGMaterialType ParseMaterialType (const std::string& _Type);

private:

	std::map<OGMaterialType, IOGMaterial*>	m_MaterialsList;
};

#endif
