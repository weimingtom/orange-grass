#ifndef TOOLSETTINGS_H_
#define TOOLSETTINGS_H_

#include <wx\colour.h>

enum TerrainEditMode
{
	EDITMODE_NO,
	EDITMODE_HEIGHT,
	EDITMODE_COLOR,
	EDITMODE_OBJECTS
};


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

	/// @brief Get primary color.
	const wxColor& GetPrimaryColor () const {return m_PrimaryColor;}

	/// @brief Set primary color.
	void SetPrimaryColor (const wxColor& _color) {m_PrimaryColor = _color;}

	/// @brief Get secondary color.
	const wxColor& GetSecondaryColor () const {return m_SecondaryColor;}

	/// @brief Set secondary color.
	void SetSecondaryColor (const wxColor& _color) {m_SecondaryColor = _color;}

	/// @brief Get color brush size.
	int GetColorBrushSize () const {return m_BrushSize;}

	/// @brief Get color brush size min and max values.
	void GetColorBrushSizeMinMax (int& _min, int& _max) const;

	/// @brief Set color brush size.
	void SetColorBrushSize (int _size) {m_BrushSize = _size;}

	/// @brief Get heightmap brush size.
	int GetHeightmapBrushSize () const {return m_HeightBrushSize;}

	/// @brief Get heightmap brush size min and max values.
	void GetHeightmapBrushSizeMinMax (int& _min, int& _max) const;

	/// @brief Set heightmap brush size.
	void SetHeightmapBrushSize (int _size) {m_HeightBrushSize = _size;}

	/// @brief Get heightmap extrude strength value.
	float GetHeightmapAddValue () const {return m_fHeightAddValue;}

	/// @brief Get heightmap extrude strength min and max values.
	void GetHeightmapAddMinMax (float& _min, float& _max) const;

	/// @brief Set heightmap extrude strength value.
	void SetHeightmapAddValue (float _val) {m_fHeightAddValue = _val;}

	/// @brief Get heighmap smoothing.
	bool GetHeightmapSmoothing () const {return m_bHeightSmoothing;}

	/// @brief Get heighmap smoothing.
	void SetHeightmapSmoothing (bool _bSmoothing) {m_bHeightSmoothing = _bSmoothing;}

private:

	TerrainEditMode	m_EditMode;

	wxColor			m_PrimaryColor;
	wxColor			m_SecondaryColor;
	int				m_BrushSize;
	int				m_BrushSizeMin;
	int				m_BrushSizeMax;
	
	int				m_HeightBrushSize;
	int				m_HeightBrushSizeMin;
	int				m_HeightBrushSizeMax;
	float			m_fHeightAddValue;
	float			m_fHeightAddMin;
	float			m_fHeightAddMax;
	bool			m_bHeightSmoothing;
};


/// @brief Creating Settings object
ToolSettings* GetToolSettings ();

#endif