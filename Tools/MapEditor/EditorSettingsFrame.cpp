#include <wx/wx.h>
#include "EditorSettingsFrame.h"
#include "sample.xpm"


BEGIN_EVENT_TABLE(CEditorSettingsFrame, wxMDIChildFrame)
END_EVENT_TABLE()


/// @brief Constructor.
/// @param parent - parent window.
/// @param title - window title.
/// @param pos - window position.
/// @param size - window size.
/// @param style - window style.
CEditorSettingsFrame::CEditorSettingsFrame(	wxMDIParentFrame *parent, 
										const wxString& title, 
										const wxPoint& pos,
										const wxSize& size, 
										long style) : wxMDIChildFrame(parent, wxID_ANY, title, pos, size, style)
{
    SetIcon(wxIcon(sample_xpm));
    m_pPanel = new wxPanel(this);

	m_pTree = new wxTreeCtrl(m_pPanel, wxID_ANY, wxDefaultPosition, wxSize(size.GetWidth()*0.95f, size.GetHeight()*0.7f));
    m_pTree->AddRoot(_T("Settings"));

    wxTreeItemId RangeRoot = m_pTree->AppendItem(m_pTree->GetRootItem(), _T("Level Range"), -1, -1, 0);
	m_pTree->AppendItem(RangeRoot, _T("Level Start"), -1, -1, new SettingsItem(SETMODE_LEVEL_START, _T("Level Start")));
	m_pTree->AppendItem(RangeRoot, _T("Level Finish"), -1, -1, new SettingsItem(SETMODE_LEVEL_FINISH, _T("Level Finish")));

	m_pTree->Expand(m_pTree->GetRootItem());
	m_pTree->Expand(RangeRoot);
	m_pTree->Connect(wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler(CEditorSettingsFrame::OnSettingsSwitch), NULL, this);
}


/// @brief Settings switching event handler
void CEditorSettingsFrame::OnSettingsSwitch ( wxTreeEvent& event )
{
	if ( event.GetItem() == m_pTree->GetRootItem() )
		return;

	SettingsItem* pData = (SettingsItem *)m_pTree->GetItemData(event.GetItem());
	if(pData)
	{
        switch (pData->type)
        {
        case SETMODE_LEVEL_START:
            {
                CommonToolEvent<ToolCmdEventData> cmd(EVENTID_TOOLCMD);
                ToolCmdEventData cmdData (CMD_SETTINGSMODE_LEVSTART, true);
                cmd.SetEventCustomData(cmdData);
	            GetEventHandlersTable()->FireEvent(EVENTID_TOOLCMD, &cmd);
            }
            break;

        case SETMODE_LEVEL_FINISH:
            {
                CommonToolEvent<ToolCmdEventData> cmd(EVENTID_TOOLCMD);
                ToolCmdEventData cmdData (CMD_SETTINGSMODE_LEVFINISH, true);
                cmd.SetEventCustomData(cmdData);
	            GetEventHandlersTable()->FireEvent(EVENTID_TOOLCMD, &cmd);
            }
            break;
        }
	}
}
