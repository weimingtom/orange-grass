#include <wx/wx.h>
#include "EditorHeightmapFrame.h"
#include "sample.xpm"

#define CTRLID_HMADDSLIDER		10001
#define CTRLID_HMBRUSHSLIDER	10002
#define CTRLID_HMSMOOTHCHECK	10003

BEGIN_EVENT_TABLE(CEditorHeightmapFrame, wxMDIChildFrame)
    EVT_COMMAND_SCROLL(CTRLID_HMADDSLIDER, CEditorHeightmapFrame::OnHMAddSlider)
    EVT_COMMAND_SCROLL(CTRLID_HMBRUSHSLIDER, CEditorHeightmapFrame::OnHMBrushSlider)
    EVT_CHECKBOX(CTRLID_HMSMOOTHCHECK, CEditorHeightmapFrame::OnSmoothenCheck)
END_EVENT_TABLE()


/// @brief Constructor.
/// @param parent - parent window.
/// @param title - window title.
/// @param pos - window position.
/// @param size - window size.
/// @param style - window style.
CEditorHeightmapFrame::CEditorHeightmapFrame(	wxMDIParentFrame *parent, 
												const wxString& title, 
												const wxPoint& pos,
												const wxSize& size, 
												long style) : wxMDIChildFrame(parent, wxID_ANY, title, pos, size, style)
{
    SetIcon(wxIcon(sample_xpm));
    m_pPanel = new wxPanel(this);
	
	ToolSettings* pTool = GetToolSettings();
	float fAddMin, fAddMax;
	pTool->GetHeightmapAddMinMax (fAddMin, fAddMax);
	int BrushMin, BrushMax;
	pTool->GetHeightmapBrushSizeMinMax (BrushMin, BrushMax);

	wxStaticBox* HMAddDesc = new wxStaticBox(m_pPanel, wxID_ANY, _T("Set extrusion strength:"), wxPoint(10, 10), wxSize(170, 70));
	m_pHMAddSlider = new wxSlider(m_pPanel, CTRLID_HMADDSLIDER,
		(int)pTool->GetHeightmapAddValue(), (int)fAddMin, (int)fAddMax, wxPoint(20, 30), wxSize(150, 40), wxSL_LABELS);

	wxStaticBox* HMBrushDesc = new wxStaticBox(m_pPanel, wxID_ANY, _T("Set brush size:"), wxPoint(10, 90), wxSize(170, 70));
	m_pHMBrushSizeSlider = new wxSlider(m_pPanel, CTRLID_HMBRUSHSLIDER,
		pTool->GetHeightmapBrushSize(), BrushMin, BrushMax, wxPoint(20, 110), wxSize(150, 40), wxSL_LABELS);

    m_pSmoothenCheck = new wxCheckBox(m_pPanel, CTRLID_HMSMOOTHCHECK, _T("Enable smooting"), wxPoint(20, 170));
}


/// @brief Height addition slider event handler
/// @param event - event struct
void CEditorHeightmapFrame::OnHMAddSlider(wxScrollEvent& event)
{
	GetToolSettings()->SetHeightmapAddValue((float)event.GetPosition());
}


/// @brief Height brush size slider event handler
/// @param event - event struct
void CEditorHeightmapFrame::OnHMBrushSlider(wxScrollEvent& event)
{
	GetToolSettings()->SetHeightmapBrushSize(event.GetPosition());
}


/// @brief Height smoothing enable checkbox event handler
/// @param event - event struct
void CEditorHeightmapFrame::OnSmoothenCheck(wxCommandEvent& event)
{
	GetToolSettings()->SetHeightmapSmoothing(event.IsChecked());
}
