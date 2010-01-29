#include <wx/wx.h>
#include "EditorColorFrame.h"
#include "sample.xpm"


#define CTRLID_PRIMARYCOLOR		10001
#define CTRLID_SECONDARYCOLOR	10002


BEGIN_EVENT_TABLE(CEditorColorFrame, wxMDIChildFrame)
    EVT_COLOURPICKER_CHANGED(CTRLID_PRIMARYCOLOR, CEditorColorFrame::OnPrimaryColorChange)
    EVT_COLOURPICKER_CHANGED(CTRLID_SECONDARYCOLOR, CEditorColorFrame::OnSecondaryColorChange)
END_EVENT_TABLE()


/// @brief Constructor.
/// @param parent - parent window.
/// @param title - window title.
/// @param pos - window position.
/// @param size - window size.
/// @param style - window style.
CEditorColorFrame::CEditorColorFrame(	wxMDIParentFrame *parent, 
										const wxString& title, 
										const wxPoint& pos,
										const wxSize& size, 
										long style) : wxMDIChildFrame(parent, wxID_ANY, title, pos, size, style)
{
    SetIcon(wxIcon(sample_xpm));
    m_pPanel = new wxPanel(this);

	wxStaticBox* PrimClrDesc = new wxStaticBox(m_pPanel, wxID_ANY, _T("Select primary color (LMB):"), wxPoint(10, 10), wxSize(170, 60));
	wxStaticBox* SecClrDesc = new wxStaticBox(m_pPanel, wxID_ANY, _T("Select secondary color (RMB):"), wxPoint(10, 80), wxSize(170, 60));

	m_pPrimaryColorPicker = new wxColourPickerCtrl(m_pPanel, CTRLID_PRIMARYCOLOR, GetToolSettings()->GetPrimaryColor(),
		wxPoint(20, 30), wxSize(80, 30),
		wxCLRP_DEFAULT_STYLE | wxCLRP_SHOW_LABEL);

    m_pSecondaryColorPicker = new wxColourPickerCtrl(m_pPanel, CTRLID_SECONDARYCOLOR, GetToolSettings()->GetSecondaryColor(),
		wxPoint(20, 100), wxSize(80, 30),
		wxCLRP_DEFAULT_STYLE | wxCLRP_SHOW_LABEL);
}


/// @brief Primary color event handler
void CEditorColorFrame::OnPrimaryColorChange(wxColourPickerEvent& event)
{
	GetToolSettings()->SetPrimaryColor(event.GetColour());
}


/// @brief Secondary color event handler
void CEditorColorFrame::OnSecondaryColorChange(wxColourPickerEvent& event)
{
	GetToolSettings()->SetSecondaryColor(event.GetColour());
}
