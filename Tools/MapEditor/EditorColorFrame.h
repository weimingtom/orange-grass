#ifndef EDITORCOLORFRAME_H_
#define EDITORCOLORFRAME_H_

#include "wx/clrpicker.h"
#include <ToolFramework.h>
#include <vector>


/// @brief Application's tool window frame.
class CEditorColorFrame : public wxMDIChildFrame
{
public:

    /// @brief Constructor.
    /// @param parent - parent window.
    /// @param title - window title.
    /// @param pos - window position.
    /// @param size - window size.
    /// @param style - window style.
    CEditorColorFrame ( wxMDIParentFrame *parent, 
						const wxString& title, 
						const wxPoint& pos,
						const wxSize& size, 
						long style = wxDEFAULT_FRAME_STYLE);

private:
	
	/// @brief Primary color event handler
	void OnPrimaryColorChange(wxColourPickerEvent& event);
	
	/// @brief Secondary color event handler
	void OnSecondaryColorChange(wxColourPickerEvent& event);

private:

    DECLARE_EVENT_TABLE()

    wxPanel*    m_pPanel;
    wxColourPickerCtrl*	m_pPrimaryColorPicker;
    wxColourPickerCtrl*	m_pSecondaryColorPicker;
};

#endif