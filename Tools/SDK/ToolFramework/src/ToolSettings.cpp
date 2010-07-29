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
    m_PosX = 0;
    m_PosY = 0;
    m_PosZ = 0;

    m_Yaw = 0;
    m_Pitch = 0;
    m_Roll = 0;
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
