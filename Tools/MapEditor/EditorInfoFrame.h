#ifndef EDITORINFOFRAME_H_
#define EDITORINFOFRAME_H_

#include <ToolFramework.h>


/// @brief Application's info window frame.
class CEditorInfoFrame : public wxMDIChildFrame
{
public:

    /// @brief Constructor.
    /// @param parent - parent window.
    /// @param title - window title.
    /// @param pos - window position.
    /// @param size - window size.
    /// @param style - window style.
    CEditorInfoFrame ( wxMDIParentFrame *parent, 
						const wxString& title, 
						const wxPoint& pos,
						const wxSize& size, 
						long style = wxDEFAULT_FRAME_STYLE);

	/// @brief Destructor
	virtual ~CEditorInfoFrame();

private:

    DECLARE_EVENT_TABLE()

    wxPanel*    m_pPanel;
	wxListBox*	m_pLogBox;
};

#endif