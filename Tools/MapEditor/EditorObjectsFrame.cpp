#include <wx/wx.h>
#include "EditorObjectsFrame.h"
#include "sample.xpm"


BEGIN_EVENT_TABLE(CEditorObjectsFrame, wxMDIChildFrame)
      EVT_RESLOAD( wxID_ANY, CEditorObjectsFrame::OnLoadResource )
END_EVENT_TABLE()


/// @brief Constructor.
/// @param parent - parent window.
/// @param title - window title.
/// @param pos - window position.
/// @param size - window size.
/// @param style - window style.
CEditorObjectsFrame::CEditorObjectsFrame(	wxMDIParentFrame *parent, 
											const wxString& title, 
											const wxPoint& pos,
											const wxSize& size, 
											long style) : wxMDIChildFrame(parent, wxID_ANY, title, pos, size, style)
{
    SetIcon(wxIcon(sample_xpm));
    m_pPanel = new wxPanel(this);

    m_pObjectsList = new wxSimpleHtmlListBox();
	m_pObjectsList->Create(m_pPanel, wxID_ANY, wxDefaultPosition, wxSize(size.GetWidth()*0.9, size.GetHeight()*0.8), 0, NULL, 0);

	m_pObjectsList->Connect(wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( CEditorObjectsFrame::OnResourceSwitch ), NULL, this);
	GetEventHandlersTable()->AddEventHandler(EVENTID_RESLOAD, this);
}


/// @brief Resource loading event handler
void CEditorObjectsFrame::OnLoadResource ( CommonToolEvent<ResLoadEventData>& event )
{
	const ResLoadEventData& evtData = event.GetEventCustomData();
    wxString resourceText = evtData.m_Resource;
	wxString resourceGroupText = evtData.m_ResourceGroup;
	wxString resourceIconText = wxString::Format(_T("<img src=\"%s\" />"), evtData.m_ResourceIcon);

	if (resourceGroupText.CmpNoCase(_T("Models")) == 0)
	{
		m_pObjectsList->Append (resourceIconText);
	}
}


/// @brief Resource switching event handler
void CEditorObjectsFrame::OnResourceSwitch ( wxCommandEvent& event )
{
	return;
}
