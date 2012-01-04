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
