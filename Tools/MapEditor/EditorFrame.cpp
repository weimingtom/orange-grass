#include "OrangeGrass.h"
#include <wx/wx.h>
#include <wx/gdicmn.h>
#include <wx/choicdlg.h>
#include "EditorFrame.h"
#include <ToolFramework.h>
#include "sample.xpm"
#include "..\include\Pathes.h"


#define ID_DEF_ABOUT		10000
#define ID_DEF_AABB			10002
#define ID_DEF_ADJUST		10003
#define ID_DEF_SETTINGS		10004
#define ID_DEF_OBJECTS		10005
#define ID_NOTEBOOK         10007
#define ID_TOOLSNOTEBOOK    10008
#define CTRLID_XDIRSLIDER	10009
#define CTRLID_ZDIRSLIDER	10010
#define CTRLID_FOGNEARSLIDER	10011
#define CTRLID_FOGFARSLIDER		10012
#define CTRLID_COLORSLIDER		10013
#define CTRLID_FOGCOLORSLIDER	10014

const int ID_TOOLBAR = 500;

static const long TOOLBAR_STYLE = wxTB_FLAT | wxTB_DOCKABLE | wxTB_TEXT;

struct SettingsItem : public wxTreeItemData
{
	SettingsItem (SettingsMode _type, const wxString& _name)
	{
		type = _type;
		name = _name;
	}

	SettingsMode	type;
	wxString		name;
};


BEGIN_EVENT_TABLE(CEditorFrame, wxFrame)
    EVT_MENU (wxID_EXIT,		CEditorFrame::OnExit)
    EVT_MENU (wxID_OPEN,		CEditorFrame::OnOpenLevel)
    EVT_MENU (wxID_SAVE,		CEditorFrame::OnSaveLevel)
    EVT_MENU (ID_DEF_ABOUT,		CEditorFrame::OnAboutDlg)
    EVT_MENU (ID_DEF_AABB,		CEditorFrame::OnBounds)
    EVT_RESLOAD(wxID_ANY,       CEditorFrame::OnLoadResource)
	EVT_LEVELLOAD(wxID_ANY,		CEditorFrame::OnLevelLoadEvent)
	EVT_COLOURPICKER_CHANGED(CTRLID_COLORSLIDER,	CEditorFrame::OnColorChange)
	EVT_COLOURPICKER_CHANGED(CTRLID_FOGCOLORSLIDER,	CEditorFrame::OnFogColorChange)
	EVT_COMMAND_SCROLL(CTRLID_XDIRSLIDER,			CEditorFrame::OnXDirSlider)
	EVT_COMMAND_SCROLL(CTRLID_ZDIRSLIDER,			CEditorFrame::OnZDirSlider)
	EVT_COMMAND_SCROLL(CTRLID_FOGNEARSLIDER,		CEditorFrame::OnFogNearSlider)
	EVT_COMMAND_SCROLL(CTRLID_FOGFARSLIDER,			CEditorFrame::OnFogFarSlider)
END_EVENT_TABLE()


/// @brief Constructor.
/// @param parent - parent window.
/// @param title - window title.
/// @param pos - window position.
/// @param size - window size.
/// @param style - window style.
CEditorFrame::CEditorFrame (wxWindow *parent, 
                            wxWindowID id,
                            const wxString & title,
                            const wxPoint & pos,
                            const wxSize & size,
                            long style)
{
	Create(parent, id, title, pos, size, style);
}


/// Destructor
CEditorFrame::~CEditorFrame()
{
	m_Manager.UnInit();
}


/// Create frame
bool CEditorFrame::Create(wxWindow * parent, 
                          wxWindowID id,
                          const wxString & title,
                          const wxPoint & pos,
                          const wxSize & size,
                          long style)
{
    int w, h;
    wxDisplaySize(&w, &h);
    wxSize appSize = wxSize(w*0.7, h*0.7);

    wxFrame::Create(parent, id, title, pos, appSize, style);

    SetIcon(wxIcon(sample_xpm));

    wxMenuBar* pMenuBar = new wxMenuBar ();
    wxMenu* pWindowMenu = new wxMenu ();
    wxMenu* pHelpMenu = new wxMenu ();
    pWindowMenu->Append(wxID_EXIT, wxT("&Close"));
    pWindowMenu->Append(ID_DEF_AABB, wxT("Show &Bounds"), wxT("Show bounds"), wxITEM_CHECK);
    pHelpMenu->Append(ID_DEF_ABOUT, wxT("&About"));
    pMenuBar->Append(pWindowMenu, wxT("&Editor"));
    pMenuBar->Append(pHelpMenu, wxT("&Help"));
    SetMenuBar(pMenuBar);

    SetToolBar(NULL);

    style &= ~(wxTB_HORIZONTAL | wxTB_VERTICAL | wxTB_BOTTOM | wxTB_RIGHT | wxTB_HORZ_LAYOUT);
    style |= wxTB_TOP;
    style |= wxTB_NO_TOOLTIPS;
    m_pToolBar = CreateToolBar(style, ID_TOOLBAR);
    PopulateToolbar(m_pToolBar);

    m_pCanvas = new CEditorCanvas(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

	m_pToolsNotebook = new wxAuiNotebook(this, ID_TOOLSNOTEBOOK, wxDefaultPosition, wxSize(200, appSize.y), 
		wxAUI_NB_DEFAULT_STYLE|wxNO_BORDER);
	m_pToolsPage1 = new wxPanel(m_pToolsNotebook, wxID_ANY);
	m_pToolsPage2 = new wxPanel(m_pToolsNotebook, wxID_ANY);
	m_pToolsPage3 = new wxPanel(m_pToolsNotebook, wxID_ANY);
	m_pToolsNotebook->AddPage(m_pToolsPage1, _("Level settings"));
	m_pToolsNotebook->AddPage(m_pToolsPage2, _("Game logic"));
	m_pToolsNotebook->AddPage(m_pToolsPage3, _("Lighting"));

    m_pObjectsList = new wxSimpleHtmlListBox();
    m_pObjectsList->Create(this, wxID_ANY, wxDefaultPosition, wxSize(148, appSize.y), 0, NULL, 0);
    m_pObjectsList->Connect(wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( CEditorFrame::OnResourceSwitch ), NULL, this);
    GetEventHandlersTable()->AddEventHandler(EVENTID_RESLOAD, this);

    m_Manager.SetManagedWindow(this);
    m_Manager.AddPane(m_pCanvas, wxAuiPaneInfo().CenterPane());
    m_Manager.AddPane(m_pObjectsList, wxAuiPaneInfo().Left().Layer(1).CloseButton(false).Resizable(false).Floatable(false).Caption(wxT("Objects")));
	m_Manager.AddPane(m_pToolsNotebook, wxAuiPaneInfo().Right().Layer(1).CloseButton(false).Resizable(false).Floatable(false).Caption(wxT("Settings")));
    m_Manager.Update();

    GetToolSettings()->SetEditMode(EDITMODE_OBJECTS);

	CreateSettingsPanelControls(m_pToolsPage1);
	CreateLightingPanelControls(m_pToolsPage3);

	GetEventHandlersTable()->AddEventHandler(EVENTID_LEVELLOAD, this);

    return true;
}


/// Create settings panel
void CEditorFrame::CreateSettingsPanelControls(wxPanel* _pPanel)
{
	wxSize panelSize = _pPanel->GetSize();

	wxSize szSettingsTree = wxSize(panelSize.GetWidth(), 150);
	wxPoint posSettingsTree = wxPoint(0, 0);
	m_pSettingsTree = new wxTreeCtrl(_pPanel, wxID_ANY, posSettingsTree, szSettingsTree);
    m_pSettingsTree->AddRoot(_T("Settings"));
    wxTreeItemId RangeRoot = m_pSettingsTree->AppendItem(m_pSettingsTree->GetRootItem(), _T("Level Range"), -1, -1, 0);
	m_pSettingsTree->AppendItem(RangeRoot, _T("Level Start"), -1, -1, new SettingsItem(SETMODE_LEVEL_START, _T("Level Start")));
	m_pSettingsTree->AppendItem(RangeRoot, _T("Level Finish"), -1, -1, new SettingsItem(SETMODE_LEVEL_FINISH, _T("Level Finish")));
	m_pSettingsTree->AppendItem(RangeRoot, _T("Level Width"), -1, -1, new SettingsItem(SETMODE_LEVEL_WIDTH, _T("Level Width")));
	m_pSettingsTree->Expand(m_pSettingsTree->GetRootItem());
	m_pSettingsTree->Expand(RangeRoot);
	m_pSettingsTree->Connect(wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler(CEditorFrame::OnSettingsSwitch), NULL, this);
}


/// Create lighting panel
void CEditorFrame::CreateLightingPanelControls(wxPanel* _pPanel)
{
	wxSize panelSize = _pPanel->GetSize();

	int rightBorder = panelSize.GetWidth()*0.85f;

	wxSize szClrDesc = wxSize(panelSize.GetWidth(), 160);
	wxPoint posClrDesc = wxPoint(0, 15);
	wxStaticBox* ClrDesc = new wxStaticBox(_pPanel, wxID_ANY, _T("Lighting:"), posClrDesc, szClrDesc);
	wxSize szClr = wxSize(rightBorder, 30);
	wxPoint posClr = wxPoint(posClrDesc.x + 5, posClrDesc.y + 15);
	m_pColorPicker = new wxColourPickerCtrl(_pPanel, CTRLID_COLORSLIDER, wxColor(0xFFFFFFFF), posClr, szClr, wxCLRP_DEFAULT_STYLE | wxCLRP_SHOW_LABEL);	m_pXDirSlider = new wxSlider(_pPanel, CTRLID_XDIRSLIDER, 0, -100, 100, wxPoint(posClrDesc.x + 5, posClrDesc.y + 60), wxSize(rightBorder, 40), wxSL_LABELS);	m_pZDirSlider = new wxSlider(_pPanel, CTRLID_ZDIRSLIDER, 0, -100, 100, wxPoint(posClrDesc.x + 5, posClrDesc.y + 105), wxSize(rightBorder, 40), wxSL_LABELS);
	wxSize szFogClrDesc = wxSize(panelSize.GetWidth(), 160);
	wxPoint posFogClrDesc = wxPoint(0, posClrDesc.y + szClrDesc.y + 15);
	wxStaticBox* FogClrDesc = new wxStaticBox(_pPanel, wxID_ANY, _T("Fog:"), posFogClrDesc, szFogClrDesc);
	wxSize szFogClr = wxSize(rightBorder, 30);
	wxPoint posFogClr = wxPoint(posFogClrDesc.x + 5, posFogClrDesc.y + 15);
	m_pFogColorPicker = new wxColourPickerCtrl(_pPanel, CTRLID_FOGCOLORSLIDER, wxColor(0xFFFFFFFF), posFogClr, szFogClr, wxCLRP_DEFAULT_STYLE | wxCLRP_SHOW_LABEL);	m_pFogNearSlider = new wxSlider(_pPanel, CTRLID_FOGNEARSLIDER, 0, -100, 100, wxPoint(posFogClrDesc.x + 5, posFogClrDesc.y + 60), wxSize(rightBorder, 40), wxSL_LABELS);	m_pFogFarSlider = new wxSlider(_pPanel, CTRLID_FOGFARSLIDER, 0, -100, 100, wxPoint(posFogClrDesc.x + 5, posFogClrDesc.y + 105), wxSize(rightBorder, 40), wxSL_LABELS);}


/// @brief App exit handler.
/// @param event - event structute.
void CEditorFrame::OnExit( wxCommandEvent& WXUNUSED(event) )
{
    Close(true);
}


/// @brief About dialog handler.
/// @param event - event structute.
void CEditorFrame::OnAboutDlg( wxCommandEvent& WXUNUSED(event) )
{
}


/// @brief Bounds switch handler.
/// @param event - event structute.
void CEditorFrame::OnBounds(wxCommandEvent& event)
{
    CommonToolEvent<ToolCmdEventData> cmd(EVENTID_TOOLCMD);
    ToolCmdEventData cmdData (CMD_AABB, event.IsChecked ());
    cmd.SetEventCustomData(cmdData);
	GetEventHandlersTable()->FireEvent(EVENTID_TOOLCMD, &cmd);
}


/// @brief Populate the toolbar.
/// @param toolBar - toolbar.
void CEditorFrame::PopulateToolbar(wxToolBarBase* toolBar)
{
    enum
    {
        Tool_open,
        Tool_save,
        Tool_Max
    };

    wxBitmap toolBarBitmaps[Tool_Max];

    toolBarBitmaps[Tool_open] = wxBitmap(wxT("Resources\\open.bmp"), wxBITMAP_TYPE_BMP);
    toolBarBitmaps[Tool_save] = wxBitmap(wxT("Resources\\save.bmp"), wxBITMAP_TYPE_BMP);

    int w = toolBarBitmaps[Tool_open].GetWidth();
    int h = toolBarBitmaps[Tool_open].GetHeight();

    toolBar->SetToolBitmapSize(wxSize(w, h));

    toolBar->AddTool(wxID_OPEN, wxT("Open"), toolBarBitmaps[Tool_open], wxT("Open level"), wxITEM_NORMAL);
    toolBar->AddTool(wxID_SAVE, wxT("Save"), toolBarBitmaps[Tool_save], wxT("Save level"), wxITEM_NORMAL);
    toolBar->AddSeparator();
    toolBar->Realize();
}


/// @brief Set Objects mode.
void CEditorFrame::SetObjectsMode()
{
	GetToolSettings()->SetEditMode(EDITMODE_OBJECTS);
	CommonToolEvent<ToolCmdEventData> cmd(EVENTID_TOOLCMD);
	ToolCmdEventData cmdData (CMD_EDITMODE_OBJECTS, true);
	cmd.SetEventCustomData(cmdData);
	GetEventHandlersTable()->FireEvent(EVENTID_TOOLCMD, &cmd);
}


/// @brief Set Adjust mode.
void CEditorFrame::SetAdjustMode()
{
	GetToolSettings()->SetEditMode(EDITMODE_ADJUST);
	CommonToolEvent<ToolCmdEventData> cmd(EVENTID_TOOLCMD);
	ToolCmdEventData cmdData (CMD_EDITMODE_ADJUST, true);
	cmd.SetEventCustomData(cmdData);
	GetEventHandlersTable()->FireEvent(EVENTID_TOOLCMD, &cmd);
}


/// @brief Set Settings mode.
void CEditorFrame::SetSettingsMode()
{
	GetToolSettings()->SetEditMode(EDITMODE_SETTINGS);
	CommonToolEvent<ToolCmdEventData> cmd(EVENTID_TOOLCMD);
	ToolCmdEventData cmdData (CMD_EDITMODE_SETTINGS, true);
	cmd.SetEventCustomData(cmdData);
	GetEventHandlersTable()->FireEvent(EVENTID_TOOLCMD, &cmd);
}


/// @brief Level open handler.
/// @param event - event structute.
void CEditorFrame::OnOpenLevel(wxCommandEvent& event)
{
	wxArrayString level_aliases;
	std::vector<std::string> LevelList;
	GetLevelManager()->GetLevelList(LevelList);
	std::vector<std::string>::iterator iter = LevelList.begin();
	for (; iter != LevelList.end(); ++iter)
	{
		level_aliases.Add(wxString((*iter)));
	}

	wxString n = wxGetSingleChoice(wxString(_T("Select level")), wxString(_T("Levels")), level_aliases, this);
	if (!n.empty())
	{
		CommonToolEvent<LevelLoadEventData> cmd(EVENTID_LEVELLOAD);
		LevelLoadEventData cmdData (n);
		cmd.SetEventCustomData(cmdData);
		GetEventHandlersTable()->FireEvent(EVENTID_LEVELLOAD, &cmd);
	}
}


/// @brief Level save handler.
/// @param event - event structute.
void CEditorFrame::OnSaveLevel(wxCommandEvent& event)
{
    CommonToolEvent<ToolCmdEventData> cmd(EVENTID_TOOLCMD);
    ToolCmdEventData cmdData (CMD_LEVEL_SAVE, true);
    cmd.SetEventCustomData(cmdData);
	GetEventHandlersTable()->FireEvent(EVENTID_TOOLCMD, &cmd);
}


/// @brief Resource loading event handler
void CEditorFrame::OnLoadResource ( CommonToolEvent<ResLoadEventData>& event )
{
	const ResLoadEventData& evtData = event.GetEventCustomData();
	std::string IconPath = GetResourceMgr()->GetResourcePath() + std::string("/") + std::string(evtData.m_ResourceIcon);
    wxString resourceText = evtData.m_Resource;
	wxString resourceGroupText = evtData.m_ResourceGroup;
	wxString resourceIconText = wxString::Format(_T("<img src=\"%s\" />"), IconPath.c_str());

	if (resourceGroupText.CmpNoCase(_T("Models")) == 0)
	{
		int n = m_pObjectsList->Append (resourceIconText);
		m_ItemList[n] = new ResourceItem(RESTYPE_MODEL, resourceText);
	}
}


/// @brief Resource switching event handler
void CEditorFrame::OnResourceSwitch ( wxCommandEvent& event )
{
    ResourceItem* pData = m_ItemList[event.GetSelection()];
	if(pData)
	{
		CommonToolEvent<ResSwitchEventData> cmd(EVENTID_RESSWITCH);
		cmd.SetEventCustomData(ResSwitchEventData(pData->name, pData->type));
		GetEventHandlersTable()->FireEvent(EVENTID_RESSWITCH, &cmd);

		SetObjectsMode();
	}
}


/// @brief Settings switching event handler
void CEditorFrame::OnSettingsSwitch ( wxTreeEvent& event )
{
	SetSettingsMode();

	if ( event.GetItem() == m_pSettingsTree->GetRootItem() )
		return;

	SettingsItem* pData = (SettingsItem *)m_pSettingsTree->GetItemData(event.GetItem());
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
void CEditorFrame::OnColorChange(wxColourPickerEvent& event)
{
	SetSettingsMode();

	IOGLevel* pCurLevel = (IOGLevel*)GetToolSettings()->GetLevel();
	if (pCurLevel)
	{
		wxColour clr = event.GetColour();
		GetRenderer()->GetLight()->SetMainLightColor(Vec4(
			clr.Red()/255.0f,
			clr.Green()/255.0f,
			clr.Blue()/255.0f, 1.0f));
	}

	FireUpdateEvent();
}


/// @brief Light X direction slider event handler
/// @param event - event struct
void CEditorFrame::OnXDirSlider(wxScrollEvent& event)
{
	SetSettingsMode();

	Vec3 vD = GetRenderer()->GetLight()->GetMainLightDirection();
	vD.x = (float)event.GetPosition() / 100.0f;
	vD.y = 1.0f;
	vD.z = (float)m_pZDirSlider->GetValue() / 100.0f;
	GetRenderer()->GetLight()->SetMainLightDirection(vD.normalized());

	FireUpdateEvent();
}


/// @brief Light Z direction slider event handler
/// @param event - event struct
void CEditorFrame::OnZDirSlider(wxScrollEvent& event)
{
	SetSettingsMode();

	Vec3 vD = GetRenderer()->GetLight()->GetMainLightDirection();
	vD.x = (float)m_pXDirSlider->GetValue() / 100.0f;
	vD.y = 1.0f;
	vD.z = (float)event.GetPosition() / 100.0f;
	GetRenderer()->GetLight()->SetMainLightDirection(vD.normalized());

	FireUpdateEvent();
}


/// @brief fog color event handler
void CEditorFrame::OnFogColorChange(wxColourPickerEvent& event)
{
	SetSettingsMode();

	FireUpdateEvent();
}


/// @brief Fog near slider event handler
/// @param event - event struct
void CEditorFrame::OnFogNearSlider(wxScrollEvent& event)
{
	SetSettingsMode();

	FireUpdateEvent();
}


/// @brief Fog far slider event handler
/// @param event - event struct
void CEditorFrame::OnFogFarSlider(wxScrollEvent& event)
{
	SetSettingsMode();

	FireUpdateEvent();
}


/// @brief Level load event handler
/// @param event - event structute.
void CEditorFrame::OnLevelLoadEvent ( CommonToolEvent<LevelLoadEventData>& event )
{
	IOGLevel* pCurLevel = GetLevelManager()->LoadLevel(std::string(event.GetEventCustomData().m_Path));
	Vec4 vC = GetRenderer()->GetLight()->GetMainLightColor();
	wxColour clr = wxColour(
		(unsigned char)(vC.x * 255.0f),
		(unsigned char)(vC.y * 255.0f),
		(unsigned char)(vC.z * 255.0f),
		255);
	m_pColorPicker->SetColour(clr);

	FireUpdateEvent();
}


/// Fire update event.
void CEditorFrame::FireUpdateEvent()
{
	CommonToolEvent<ToolCmdEventData> cmd(EVENTID_TOOLCMD);
	ToolCmdEventData cmdData (CMD_UPDATE, true);
	cmd.SetEventCustomData(cmdData);
	GetEventHandlersTable()->FireEvent(EVENTID_TOOLCMD, &cmd);
}
