#include "ToolSettings.h"

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
