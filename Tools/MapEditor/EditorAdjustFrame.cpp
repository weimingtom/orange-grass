#include <wx/wx.h>
#include "EditorAdjustFrame.h"
#include "sample.xpm"

#define CTRLID_YAWSLIDER		10001
#define CTRLID_PITCHSLIDER	    10002
#define CTRLID_HMSMOOTHCHECK	10003

BEGIN_EVENT_TABLE(CEditorAdjustFrame, wxMDIChildFrame)
    EVT_COMMAND_SCROLL(CTRLID_YAWSLIDER, CEditorAdjustFrame::OnYawSlider)
    EVT_COMMAND_SCROLL(CTRLID_PITCHSLIDER, CEditorAdjustFrame::OnPitchSlider)
    EVT_CHECKBOX(CTRLID_HMSMOOTHCHECK, CEditorAdjustFrame::OnSmoothenCheck)
END_EVENT_TABLE()


/// @brief Constructor.
/// @param parent - parent window.
/// @param title - window title.
/// @param pos - window position.
/// @param size - window size.
/// @param style - window style.
CEditorAdjustFrame::CEditorAdjustFrame(	wxMDIParentFrame *parent, 
												const wxString& title, 
												const wxPoint& pos,
												const wxSize& size, 
												long style) : wxMDIChildFrame(parent, wxID_ANY, title, pos, size, style)
{
    SetIcon(wxIcon(sample_xpm));
    m_pPanel = new wxPanel(this);
	
	ToolSettings* pTool = GetToolSettings();
}


/// @brief Yaw slider event handler
/// @param event - event struct
void CEditorAdjustFrame::OnYawSlider(wxScrollEvent& event)
{
}


/// @brief Pitch slider event handler
/// @param event - event struct
void CEditorAdjustFrame::OnPitchSlider(wxScrollEvent& event)
{
}


/// @brief Height smoothing enable checkbox event handler
/// @param event - event struct
void CEditorAdjustFrame::OnSmoothenCheck(wxCommandEvent& event)
{
}
