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
	m_PrimaryColor = wxColor(110, 250, 30);
	m_SecondaryColor = wxColor(200, 200, 30);
	m_BrushSize = 5;
	m_BrushSizeMin = 1;
	m_BrushSizeMax = 10;
	m_HeightBrushSize = 5;
	m_HeightBrushSizeMin = 1;
	m_HeightBrushSizeMax = 10;
	m_fHeightAddValue = 10.0f;
	m_fHeightAddMin = 1.0f;
	m_fHeightAddMax = 50.0f;
	m_bHeightSmoothing = true;
}


/// @brief Get color brush size min and max values.
void ToolSettings::GetColorBrushSizeMinMax (int& _min, int& _max) const
{
	_min = m_BrushSizeMin;
	_max = m_BrushSizeMax;
}


/// @brief Get heightmap brush size min and max values.
void ToolSettings::GetHeightmapBrushSizeMinMax (int& _min, int& _max) const
{
	_min = m_HeightBrushSizeMin;
	_max = m_HeightBrushSizeMax;
}


/// @brief Get heightmap extrude strength min and max values.
void ToolSettings::GetHeightmapAddMinMax (float& _min, float& _max) const
{
	_min = m_fHeightAddMin;
	_max = m_fHeightAddMax;
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
