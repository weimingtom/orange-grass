#include <wx/wx.h>
#include "ViewerToolFrame.h"
#include "sample.xpm"


BEGIN_EVENT_TABLE(CViewerToolFrame, wxMDIChildFrame)
      EVT_RESLOAD( wxID_ANY, CViewerToolFrame::OnLoadResource )
END_EVENT_TABLE()


/// @brief Constructor.
/// @param parent - parent window.
/// @param title - window title.
/// @param pos - window position.
/// @param size - window size.
/// @param style - window style.
CViewerToolFrame::CViewerToolFrame( wxMDIParentFrame *parent, 
                                    const wxString& title, 
                                    const wxPoint& pos,
                                    const wxSize& size, 
                                    long style) : wxMDIChildFrame(parent, wxID_ANY, title, pos, size, style)
{
    SetIcon(wxIcon(sample_xpm));
    m_pPanel = new wxPanel(this);
	m_pTree = new wxTreeCtrl(m_pPanel, wxID_ANY, wxDefaultPosition, wxSize(size.GetWidth(), size.GetHeight()));
    m_pTree->AddRoot(_T("Resources"));

	AddResourceGroup (RESTYPE_TEXTURE, wxT("Textures"));
	AddResourceGroup (RESTYPE_MODEL, wxT("Models"));

	m_pTree->Expand(m_pTree->GetRootItem());

	GetEventHandlersTable()->AddEventHandler(EVENTID_RESLOAD, this);
	m_pTree->Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( CViewerToolFrame::OnResourceSwitch ), NULL, this );
}


/// @brief Adding resource group
void CViewerToolFrame::AddResourceGroup ( ResourceType _type, const wxString& _name )
{
	ResourceGroup groupItem(_type, _name);
	groupItem.item = m_pTree->AppendItem(m_pTree->GetRootItem(), groupItem.name, -1, -1, 0);
	m_ResourceGroups.push_back(groupItem);
}


/// @brief Resource loading event handler
void CViewerToolFrame::OnLoadResource ( CommonToolEvent<ResLoadEventData>& event )
{
	const ResLoadEventData& evtData = event.GetEventCustomData();
    wxString resourceText = evtData.m_Resource;
	wxString resourceGroupText = evtData.m_ResourceGroup;

	std::vector<ResourceGroup>::const_iterator iter = m_ResourceGroups.begin();
	for (; iter != m_ResourceGroups.end(); ++iter)
	{
		if (resourceGroupText.CmpNoCase((*iter).name) == 0)
		{
			m_pTree->AppendItem((*iter).item, resourceText, -1, -1, new ResourceItem((*iter).type, resourceText) );
		}
	}
}


/// @brief Resource switching event handler
void CViewerToolFrame::OnResourceSwitch ( wxTreeEvent& event )
{
	if ( event.GetItem() == m_pTree->GetRootItem() )
		return;

	ResourceItem* pData = (ResourceItem *)m_pTree->GetItemData(event.GetItem());
	if(pData)
	{
		CommonToolEvent<ResSwitchEventData> cmd(EVENTID_RESSWITCH);
		cmd.SetEventCustomData(ResSwitchEventData(pData->name, pData->type));
		GetEventHandlersTable()->FireEvent(EVENTID_RESSWITCH, &cmd);
	}
}
