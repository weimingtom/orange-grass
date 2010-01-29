#include <wx/wx.h>
#include "EditorInfoFrame.h"
#include "sample.xpm"


BEGIN_EVENT_TABLE(CEditorInfoFrame, wxMDIChildFrame)
END_EVENT_TABLE()


/// @brief Constructor.
/// @param parent - parent window.
/// @param title - window title.
/// @param pos - window position.
/// @param size - window size.
/// @param style - window style.
CEditorInfoFrame::CEditorInfoFrame(	wxMDIParentFrame *parent, 
										const wxString& title, 
										const wxPoint& pos,
										const wxSize& size, 
										long style) : wxMDIChildFrame(parent, wxID_ANY, title, pos, size, style)
{
    SetIcon(wxIcon(sample_xpm));
    m_pPanel = new wxPanel(this);

	wxSizer *sizerDown = new wxStaticBoxSizer(new wxStaticBox( m_pPanel, wxID_ANY, _T("&Log window"), wxPoint(1, 1), wxSize(670, 90)), wxVERTICAL);

    m_pLogBox = new wxListBox(m_pPanel, wxID_ANY, wxPoint(10, 20), wxSize(660, 70));
    sizerDown->Add(m_pLogBox, 1, wxGROW | wxALL, 5);
    sizerDown->SetMinSize(660, 70);
    ListBoxLogger* m_logTarget = new ListBoxLogger(m_pLogBox, wxLog::GetActiveTarget());
    wxLog::SetActiveTarget(m_logTarget);
}
