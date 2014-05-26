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
#include "ToolSettings.h"
#include <windows.h>

static ToolSettings* g_pToolSettings = NULL;


/// @brief Constructor.
ToolSettings::ToolSettings ()
{
	ResetDefaults ();
}


/// @brief Reset all settings to default values.
void ToolSettings::ResetDefaults ()
{
	m_EditMode = EDITMODE_NO;
	m_pLevel = NULL;
}


/// @brief Creating Settings object
ToolSettings* GetToolSettings ()
{
	if (g_pToolSettings == NULL)
	{
		g_pToolSettings = new ToolSettings ();
	}
	return g_pToolSettings;
}


/*!***************************************************************************
 @Function			GetResourcePathASCII
 @Output            _pOutPath output path string
 @Input				_PathLength max. path length
 @Description		Returns the full path to resources
 ****************************************************************************/
void GetResourcePathASCII(char* _pOutPath, int _PathLength)
{
    GetModuleFileName ( NULL, _pOutPath, _PathLength );
    int pos = (int)strlen( _pOutPath );
    while ( --pos )
    {
        if ( _pOutPath [ pos ] == '\\') 
        {
            _pOutPath [ pos ] = '\0';
            break;
        }
        else
            _pOutPath [ pos + 1 ] = ' ';
    }
}
