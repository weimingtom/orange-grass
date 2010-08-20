#include <wx/wx.h>
#include "EditorSettingsFrame.h"
#include "sample.xpm"
#include "OrangeGrass.h"


#define CTRLID_XDIRSLIDER		10001
#define CTRLID_ZDIRSLIDER		10002


BEGIN_EVENT_TABLE(CEditorSettingsFrame, wxMDIChildFrame)
	EVT_LEVELLOAD(wxID_ANY, CEditorSettingsFrame::OnLevelLoadEvent)
    EVT_COLOURPICKER_CHANGED(wxID_ANY, CEditorSettingsFrame::OnColorChange)
    EVT_COMMAND_SCROLL(CTRLID_XDIRSLIDER, CEditorSettingsFrame::OnXDirSlider)
    EVT_COMMAND_SCROLL(CTRLID_ZDIRSLIDER, CEditorSettingsFrame::OnZDirSlider)
END_EVENT_TABLE()

IOGLevel* pCurLevel = NULL;


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

	wxSize szTree = wxSize(size.GetWidth()*0.95f, size.GetHeight()*0.5f);
	wxPoint posTree = wxPoint(0, 0);
	m_pTree = new wxTreeCtrl(m_pPanel, wxID_ANY, posTree, szTree);
    m_pTree->AddRoot(_T("Settings"));

    wxTreeItemId RangeRoot = m_pTree->AppendItem(m_pTree->GetRootItem(), _T("Level Range"), -1, -1, 0);
	m_pTree->AppendItem(RangeRoot, _T("Level Start"), -1, -1, new SettingsItem(SETMODE_LEVEL_START, _T("Level Start")));
	m_pTree->AppendItem(RangeRoot, _T("Level Finish"), -1, -1, new SettingsItem(SETMODE_LEVEL_FINISH, _T("Level Finish")));
	m_pTree->AppendItem(RangeRoot, _T("Level Width"), -1, -1, new SettingsItem(SETMODE_LEVEL_WIDTH, _T("Level Width")));

	m_pTree->Expand(m_pTree->GetRootItem());
	m_pTree->Expand(RangeRoot);
	m_pTree->Connect(wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler(CEditorSettingsFrame::OnSettingsSwitch), NULL, this);

	wxSize szClrDesc = wxSize(size.GetWidth()*0.95f, 160);
	wxPoint posClrDesc = wxPoint(0, posTree.y + szTree.y + 15);
	wxStaticBox* ClrDesc = new wxStaticBox(m_pPanel, wxID_ANY, _T("Lighting:"), posClrDesc, szClrDesc);

	wxSize szClr = wxSize(size.GetWidth()*0.85f, 30);
	wxPoint posClr = wxPoint(posClrDesc.x + 5, posClrDesc.y + 15);
	m_pColorPicker = new wxColourPickerCtrl(m_pPanel, wxID_ANY, wxColor(0xFFFFFFFF),
		posClr, szClr, wxCLRP_DEFAULT_STYLE | wxCLRP_SHOW_LABEL);
	m_pXDirSlider = new wxSlider(m_pPanel, CTRLID_XDIRSLIDER,
		0, -100, 100, wxPoint(posClrDesc.x + 5, posClrDesc.y + 60), wxSize(size.GetWidth()*0.85f, 40), wxSL_LABELS);	m_pZDirSlider = new wxSlider(m_pPanel, CTRLID_ZDIRSLIDER,
		0, -100, 100, wxPoint(posClrDesc.x + 5, posClrDesc.y + 105), wxSize(size.GetWidth()*0.85f, 40), wxSL_LABELS);
	GetEventHandlersTable()->AddEventHandler(EVENTID_LEVELLOAD, this);
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

        case SETMODE_LEVEL_WIDTH:
            {
                CommonToolEvent<ToolCmdEventData> cmd(EVENTID_TOOLCMD);
                ToolCmdEventData cmdData (CMD_SETTINGSMODE_LEVWIDTH, true);
                cmd.SetEventCustomData(cmdData);
	            GetEventHandlersTable()->FireEvent(EVENTID_TOOLCMD, &cmd);
            }
            break;
        }
	}
}


/// @brief color event handler
void CEditorSettingsFrame::OnColorChange(wxColourPickerEvent& event)
{
	IOGLevel* pCurLevel = (IOGLevel*)GetToolSettings()->GetLevel();
	if (pCurLevel)
	{
		wxColour clr = event.GetColour();
		GetSceneGraph()->GetLight()->SetColor(Vec4(
			clr.Red()/255.0f,
			clr.Green()/255.0f,
			clr.Blue()/255.0f,
			1.0f));
	}
}


/// @brief Light X direction slider event handler
/// @param event - event struct
void CEditorSettingsFrame::OnXDirSlider(wxScrollEvent& event)
{
	Vec4 vD = GetSceneGraph()->GetLight()->GetDirection();
	vD.x = (float)event.GetPosition() / 100.0f;
	vD.y = 1.0f;
	vD.z = (float)m_pZDirSlider->GetValue() / 100.0f;
	GetSceneGraph()->GetLight()->SetDirection(vD.normalized());

	CommonToolEvent<ToolCmdEventData> cmd(EVENTID_TOOLCMD);
    ToolCmdEventData cmdData (CMD_UPDATE, true);
    cmd.SetEventCustomData(cmdData);
	GetEventHandlersTable()->FireEvent(EVENTID_TOOLCMD, &cmd);
}


/// @brief Light Z direction slider event handler
/// @param event - event struct
void CEditorSettingsFrame::OnZDirSlider(wxScrollEvent& event)
{
	Vec4 vD = GetSceneGraph()->GetLight()->GetDirection();
	vD.x = (float)m_pXDirSlider->GetValue() / 100.0f;
	vD.y = 1.0f;
	vD.z = (float)event.GetPosition() / 100.0f;
	GetSceneGraph()->GetLight()->SetDirection(vD.normalized());

	CommonToolEvent<ToolCmdEventData> cmd(EVENTID_TOOLCMD);
    ToolCmdEventData cmdData (CMD_UPDATE, true);
    cmd.SetEventCustomData(cmdData);
	GetEventHandlersTable()->FireEvent(EVENTID_TOOLCMD, &cmd);
}


/// @brief Level load event handler
/// @param event - event structute.
void CEditorSettingsFrame::OnLevelLoadEvent ( CommonToolEvent<LevelLoadEventData>& event )
{
	pCurLevel = GetLevelManager()->LoadLevel(std::string(event.GetEventCustomData().m_Path));
	Vec4 vC = GetSceneGraph()->GetLight()->GetColor();
	wxColour clr = wxColour(
		(unsigned char)(vC.x * 255.0f),
		(unsigned char)(vC.y * 255.0f),
		(unsigned char)(vC.z * 255.0f),
		255);
	m_pColorPicker->SetColour(clr);

    CommonToolEvent<ToolCmdEventData> cmd(EVENTID_TOOLCMD);
    ToolCmdEventData cmdData (CMD_UPDATE, true);
    cmd.SetEventCustomData(cmdData);
	GetEventHandlersTable()->FireEvent(EVENTID_TOOLCMD, &cmd);
}
