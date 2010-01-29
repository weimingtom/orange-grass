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

    m_pObjectsList = new wxBitmapComboBox();
    m_pObjectsList->Create(m_pPanel, wxID_ANY, wxEmptyString,
                       wxDefaultPosition, wxDefaultSize,
                       0, NULL,
                       wxCB_READONLY);

	GetEventHandlersTable()->AddEventHandler(EVENTID_RESLOAD, this);
}


/// @brief Resource loading event handler
void CEditorObjectsFrame::OnLoadResource ( CommonToolEvent<ResLoadEventData>& event )
{
	const ResLoadEventData& evtData = event.GetEventCustomData();
    wxString resourceText = evtData.m_Resource;
	wxString resourceGroupText = evtData.m_ResourceGroup;
	wxString resourceIconText = evtData.m_ResourceIcon;

	if (resourceGroupText.CmpNoCase(_T("Models")) == 0)
	{
		wxBitmap bmp = wxBitmap (resourceIconText, wxBITMAP_TYPE_BMP);
		m_pObjectsList->Append (resourceText, bmp);
	}
}
