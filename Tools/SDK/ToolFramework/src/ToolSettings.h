#ifndef TOOLSETTINGS_H_
#define TOOLSETTINGS_H_

#include <wx\colour.h>


enum TerrainEditMode
{
	EDITMODE_NO,
	EDITMODE_ADJUST,
	EDITMODE_SETTINGS,
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

	/// @brief Get object x position.
	float GetPosX () const {return m_PosX;}

	/// @brief Set object x position.
	void SetPosX (float _PosX) {m_PosX = _PosX;}

	/// @brief Get object y position.
	float GetPosY () const {return m_PosY;}

	/// @brief Set object y position.
	void SetPosY (float _PosY) {m_PosY = _PosY;}

	/// @brief Get object z position.
	float GetPosZ () const {return m_PosZ;}

	/// @brief Set object z position.
	void SetPosZ (float _PosZ) {m_PosZ = _PosZ;}

	/// @brief Get object yaw.
	float GetYaw () const {return m_Yaw;}

	/// @brief Set object yaw.
	void SetYaw (float _Yaw) {m_Yaw = _Yaw;}

	/// @brief Get object pitch.
	float GetPitch () const {return m_Pitch;}

	/// @brief Set object pitch.
	void SetPitch (float _Pitch) {m_Pitch = _Pitch;}

	/// @brief Get object Roll.
	float GetRoll () const {return m_Roll;}

	/// @brief Set object Roll.
	void SetRoll (float _Roll) {m_Roll = _Roll;}

private:

	TerrainEditMode	m_EditMode;

    float   m_PosX;
    float   m_PosY;
    float   m_PosZ;

    float   m_Yaw;
    float   m_Pitch;
    float   m_Roll;
};


/// @brief Creating Settings object
ToolSettings* GetToolSettings ();

#endif