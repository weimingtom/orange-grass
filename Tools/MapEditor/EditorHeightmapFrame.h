#ifndef EDITORHEIGHTMAPFRAME_H_
#define EDITORHEIGHTMAPFRAME_H_

#include "wx/slider.h"
#include <ToolFramework.h>
#include <vector>


/// @brief Application's tool window frame.
class CEditorHeightmapFrame : public wxMDIChildFrame
{
public:

    /// @brief Constructor.
    /// @param parent - parent window.
    /// @param title - window title.
    /// @param pos - window position.
    /// @param size - window size.
    /// @param style - window style.
    CEditorHeightmapFrame ( wxMDIParentFrame *parent, 
							const wxString& title, 
							const wxPoint& pos,
							const wxSize& size, 
							long style = wxDEFAULT_FRAME_STYLE);

private:

	/// @brief Height addition slider event handler
	/// @param event - event struct
	void OnHMAddSlider(wxScrollEvent& event);

	/// @brief Height brush size slider event handler
	/// @param event - event struct
	void OnHMBrushSlider(wxScrollEvent& event);

	/// @brief Height smoothing enable checkbox event handler
	/// @param event - event struct
	void OnSmoothenCheck(wxCommandEvent& event);

private:

    DECLARE_EVENT_TABLE()

    wxPanel*    m_pPanel;
	wxSlider*	m_pHMAddSlider;
	wxSlider*	m_pHMBrushSizeSlider;
	wxCheckBox*	m_pSmoothenCheck;
};

#endif