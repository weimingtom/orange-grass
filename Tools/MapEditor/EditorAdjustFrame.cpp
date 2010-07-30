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

	//wxStaticBox* YawDesc = new wxStaticBox(m_pPanel, wxID_ANY, _T("Set object Yaw:"), wxPoint(10, 10), wxSize(140, 70));
	//m_pYawSlider = new wxSlider(m_pPanel, CTRLID_YAWSLIDER,
	//	0, 0, 360, wxPoint(20, 30), wxSize(120, 40), wxSL_LABELS);

	//wxStaticBox* PitchDesc = new wxStaticBox(m_pPanel, wxID_ANY, _T("Set object Pitch:"), wxPoint(10, 90), wxSize(140, 70));
	//m_pPitchSlider = new wxSlider(m_pPanel, CTRLID_PITCHSLIDER,
	//	0, 0, 360, wxPoint(20, 110), wxSize(120, 40), wxSL_LABELS);

	//m_pSmoothenCheck = new wxCheckBox(m_pPanel, CTRLID_HMSMOOTHCHECK, _T("Enable smooting"), wxPoint(20, 170));
}


/// @brief Yaw slider event handler
/// @param event - event struct
void CEditorAdjustFrame::OnYawSlider(wxScrollEvent& event)
{
	GetToolSettings()->SetYaw((float)event.GetPosition());
}


/// @brief Pitch slider event handler
/// @param event - event struct
void CEditorAdjustFrame::OnPitchSlider(wxScrollEvent& event)
{
	GetToolSettings()->SetPitch((float)event.GetPosition());
}


/// @brief Height smoothing enable checkbox event handler
/// @param event - event struct
void CEditorAdjustFrame::OnSmoothenCheck(wxCommandEvent& event)
{
	bool bCheck = event.IsChecked();
}
