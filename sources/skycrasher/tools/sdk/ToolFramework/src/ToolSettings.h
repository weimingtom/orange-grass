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
#ifndef TOOLSETTINGS_H_
#define TOOLSETTINGS_H_

#include <wx\colour.h>
#include <string>


enum TerrainEditMode
{
	EDITMODE_NO,
	EDITMODE_ADJUST,
	EDITMODE_SETTINGS,
	EDITMODE_OBJECTS
};


enum SettingsMode
{
    SETMODE_NONE = -1,
    SETMODE_LEVEL_START,
    SETMODE_LEVEL_FINISH,
    SETMODE_LEVEL_WIDTH
};


/*!***************************************************************************
 @Function			GetResourcePathASCII
 @Output            _pOutPath output path string
 @Input				_PathLength max. path length
 @Description		Returns the full path to resources
 ****************************************************************************/
void GetResourcePathASCII(char* _pOutPath, int _PathLength);


class ToolSettings
{
public:
	/// @brief Constructor.
	ToolSettings ();

	/// @brief Reset all settings to default values.
	void ResetDefaults ();

	/// @brief Get edit mode.
	TerrainEditMode GetEditMode () const {return m_EditMode;}

	/// @brief Set edit mode.
	void SetEditMode (TerrainEditMode _mode) {m_EditMode = _mode;}

	/// @brief Set level.
	void SetLevel (void* _pLevel) {m_pLevel = _pLevel;}

	/// @brief Get level.
	void* GetLevel () {return m_pLevel;}

private:

	TerrainEditMode	m_EditMode;
	void*			m_pLevel;
};


/// @brief Creating Settings object
ToolSettings* GetToolSettings ();

#endif