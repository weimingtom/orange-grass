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
#ifndef OGLEVEL_H_
#define OGLEVEL_H_

#include "IOGSettingsReader.h"


class COGLevel : public IOGLevel
{
public:
	COGLevel ();
	virtual ~COGLevel ();

    // Initialize
    virtual void Init (const std::string& _Alias, const std::string& _File);

	// load scene from file.
	virtual bool Load ();

	// Unload resource.
	virtual void Unload ();

	// get associated terrain.
	virtual IOGModel* GetTerrain ();

    // get resource load state
    OGResourceState GetLoadState () const {return m_LoadState;}

	// get level start position.
	virtual const OGVec3& GetStartPosition () const;

	// get level start finish.
	virtual const OGVec3& GetFinishPosition () const;

	// get level active width.
	virtual float GetActiveWidth () const {return m_fActiveWidth;}

	// set level start position.
	virtual void SetStartPosition (const OGVec3& _Pos);

	// set level start finish.
	virtual void SetFinishPosition (const OGVec3& _Pos);

	// set level active width.
	virtual void SetActiveWidth (float _fWidth) {m_fActiveWidth = _fWidth;}

	// save level.
	virtual bool Save ();

private:

	struct Cfg
	{
		std::string terrain_file;
		std::string scene_file;
	};

	// Load level configuration
	bool LoadConfig (COGLevel::Cfg& _cfg);

private:

    IOGModel*   m_pTerrain;
    OGVec3		m_vStartPos;
    OGVec3		m_vFinishPos;
    float		m_fActiveWidth;

    OGVec3		m_vLightDir;
    OGVec3		m_vLightAmbColor;
    OGVec3		m_vLightDifColor;
    OGVec3		m_vLightSpcColor;

    OGVec4		m_vFogColor;
    float		m_fFogStart;
    float		m_fFogEnd;
    float		m_fFogDensity;

    IOGSettingsReader*	m_pReader;
    std::string			m_SceneFile;

    std::string		m_ResourceFile;
    std::string		m_ResourceAlias;
    OGResourceState m_LoadState;
};

#endif
