#ifndef EDITORADJUSTFRAME_H_
#define EDITORADJUSTFRAME_H_

#include "wx/slider.h"
#include <ToolFramework.h>
#include <vector>


/// @brief Application's tool window frame.
class CEditorAdjustFrame : public wxMDIChildFrame
{
public:

    /// @brief Constructor.
    /// @param parent - parent window.
    /// @param title - window title.
    /// @param pos - window position.
    /// @param size - window size.
    /// @param style - window style.
    CEditorAdjustFrame ( wxMDIParentFrame *parent, 
							const wxString& title, 
							const wxPoint& pos,
							const wxSize& size, 
							long style = wxCAPTION);

private:

	/// @brief Yaw slider event handler
	/// @param event - event struct
	void OnYawSlider(wxScrollEvent& event);

	/// @brief Pitch slider event handler
	/// @param event - event struct
	void OnPitchSlider(wxScrollEvent& event);

	/// @brief Height smoothing enable checkbox event handler
	/// @param event - event struct
	void OnSmoothenCheck(wxCommandEvent& event);

private:

    DECLARE_EVENT_TABLE()

    wxPanel*    m_pPanel;
	wxSlider*	m_pYawSlider;
	wxSlider*	m_pPitchSlider;
	wxCheckBox*	m_pSmoothenCheck;
};

#endif