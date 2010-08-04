#include <wx/wx.h>
#include <wx/gdicmn.h>
#include "EditorFrame.h"
#include <ToolFramework.h>
#include "sample.xpm"
#include "..\include\Pathes.h"


#define ID_DEF_ABOUT		10000
#define ID_DEF_AABB			10002
#define ID_DEF_ADJUST		10003
#define ID_DEF_SETTINGS		10004
#define ID_DEF_OBJECTS		10005

const int ID_TOOLBAR = 500;

static const long TOOLBAR_STYLE = wxTB_FLAT | wxTB_DOCKABLE | wxTB_TEXT;


BEGIN_EVENT_TABLE(CEditorFrame, wxMDIParentFrame)
    EVT_MENU (wxID_EXIT,		CEditorFrame::OnExit)
    EVT_MENU (wxID_OPEN,		CEditorFrame::OnOpenLevel)
    EVT_MENU (wxID_SAVE,		CEditorFrame::OnSaveLevel)
    EVT_MENU (ID_DEF_ABOUT,		CEditorFrame::OnAboutDlg)
    EVT_MENU (ID_DEF_OBJECTS,	CEditorFrame::OnObjectsDlg)
    EVT_MENU (ID_DEF_ADJUST,	CEditorFrame::OnAdjustDlg)
    EVT_MENU (ID_DEF_SETTINGS,	CEditorFrame::OnSettingsDlg)
    EVT_MENU (ID_DEF_AABB,		CEditorFrame::OnBounds)
END_EVENT_TABLE()


/// @brief Factory method.
/// @return Pointer to a created frame.
CEditorFrame* CEditorFrame::Create()
{
    int w, h;
    wxDisplaySize(&w, &h);

    wxSize appSize = wxSize(w*0.8, h*0.8);
    wxPoint appPos = wxPoint((w-w*0.8)/2, (h-h*0.8)/2);
    CEditorFrame* pFrame = new CEditorFrame(NULL, wxT("OG Level Editor"), appPos, appSize);

    wxMenuBar* pMenuBar = new wxMenuBar ();
    wxMenu* pWindowMenu = new wxMenu ();
    wxMenu* pHelpMenu = new wxMenu ();
    pWindowMenu->Append(wxID_EXIT, wxT("&Close"));
    pWindowMenu->Append(ID_DEF_AABB, wxT("Show &Bounds"), wxT("Show bounds"), wxITEM_CHECK);
    pHelpMenu->Append(ID_DEF_ABOUT, wxT("&About"));
    pMenuBar->Append(pWindowMenu, wxT("&Editor"));
    pMenuBar->Append(pHelpMenu, wxT("&Help"));
    pFrame->SetMenuBar(pMenuBar);
    pFrame->Show(true);

    return pFrame;
}


/// @brief Constructor.
/// @param parent - parent window.
/// @param title - window title.
/// @param pos - window position.
/// @param size - window size.
/// @param style - window style.
CEditorFrame::CEditorFrame( wxWindow *parent, 
                            const wxString& title, 
                            const wxPoint& pos,
                            const wxSize& size, 
                            long style) : wxMDIParentFrame(parent, wxID_ANY, title, pos, size, style)
{
    SetIcon(wxIcon(sample_xpm));

    SetToolBar(NULL);

    style &= ~(wxTB_HORIZONTAL | wxTB_VERTICAL | wxTB_BOTTOM | wxTB_RIGHT | wxTB_HORZ_LAYOUT);
    style |= wxTB_TOP;
    style |= wxTB_NO_TOOLTIPS;
    m_pToolBar = CreateToolBar(style, ID_TOOLBAR);
    PopulateToolbar(m_pToolBar);

	wxSize ifSize = wxSize(size.GetWidth()*0.99, size.GetHeight()*0.19);
	wxPoint ifPos = wxPoint(0, size.GetHeight()*0.7);
    m_pInfoFrame = new CEditorInfoFrame (this, wxT("Info"), ifPos, ifSize);
    m_pInfoFrame->Show(true);

	wxSize ofSize = wxSize(size.GetWidth() - 185, size.GetHeight()*0.7);
    wxPoint ofPos = wxPoint(172, 0);
    m_pOutputFrame = new CEditorOutputFrame (this, wxT("3D View"), ofPos, ofSize);
    m_pOutputFrame->Show(true);

	wxSize tfSize = wxSize(170, size.GetHeight()*0.7);
    wxPoint tfPos = wxPoint(0, 0);
    m_pObjectsFrame = new CEditorObjectsFrame (this, wxT("Objects"), tfPos, tfSize);
    m_pObjectsFrame->Show(true);

	wxSize afSize = wxSize(170, size.GetHeight()*0.7);
    wxPoint afPos = wxPoint(0, 0);
    m_pAdjustFrame = new CEditorAdjustFrame (this, wxT("Adjust"), afPos, afSize);
    m_pAdjustFrame->Show(false);

	wxSize sfSize = wxSize(170, size.GetHeight()*0.7);
    wxPoint sfPos = wxPoint(0, 0);
    m_pSettingsFrame = new CEditorSettingsFrame (this, wxT("Settings"), sfPos, sfSize);
    m_pSettingsFrame->Show(false);

	GetToolSettings()->SetEditMode(EDITMODE_OBJECTS);
}


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
        Tool_help,
        Tool_ed_obj,
        Tool_ed_adj,
        Tool_ed_set,
        Tool_Max
    };

    wxBitmap toolBarBitmaps[Tool_Max];

    toolBarBitmaps[Tool_open] = wxBitmap(wxT("Resources\\open.bmp"), wxBITMAP_TYPE_BMP);
    toolBarBitmaps[Tool_save] = wxBitmap(wxT("Resources\\save.bmp"), wxBITMAP_TYPE_BMP);
    toolBarBitmaps[Tool_help] = wxBitmap(wxT("Resources\\help.bmp"), wxBITMAP_TYPE_BMP);
    toolBarBitmaps[Tool_ed_obj] = wxBitmap(wxT("Resources\\ed_obj.bmp"), wxBITMAP_TYPE_BMP);
    toolBarBitmaps[Tool_ed_adj] = wxBitmap(wxT("Resources\\ed_adj.bmp"), wxBITMAP_TYPE_BMP);
    toolBarBitmaps[Tool_ed_set] = wxBitmap(wxT("Resources\\ed_set.bmp"), wxBITMAP_TYPE_BMP);

    int w = toolBarBitmaps[Tool_open].GetWidth();
    int h = toolBarBitmaps[Tool_open].GetHeight();

    toolBar->SetToolBitmapSize(wxSize(w, h));

    toolBar->AddTool(wxID_OPEN, wxT("Open"), toolBarBitmaps[Tool_open], wxT("Open level"), wxITEM_NORMAL);
    toolBar->AddTool(wxID_SAVE, wxT("Save"), toolBarBitmaps[Tool_save], wxT("Save level"), wxITEM_NORMAL);
    toolBar->AddSeparator();
    toolBar->AddTool(ID_DEF_OBJECTS, wxT("Objects"), toolBarBitmaps[Tool_ed_obj], wxT("Objects"), wxITEM_NORMAL);
    toolBar->AddTool(ID_DEF_ADJUST, wxT("Adjust"), toolBarBitmaps[Tool_ed_adj], wxT("Adjust"), wxITEM_NORMAL);
    toolBar->AddTool(ID_DEF_SETTINGS, wxT("Settings"), toolBarBitmaps[Tool_ed_set], wxT("Settings"), wxITEM_NORMAL);
    toolBar->Realize();
}


/// @brief Objects dialog handler.
/// @param event - event structute.
void CEditorFrame::OnObjectsDlg(wxCommandEvent& event)
{
    m_pObjectsFrame->Show(true);
    m_pAdjustFrame->Show(false);
    m_pSettingsFrame->Show(false);
	GetToolSettings()->SetEditMode(EDITMODE_OBJECTS);

    CommonToolEvent<ToolCmdEventData> cmd(EVENTID_TOOLCMD);
    ToolCmdEventData cmdData (CMD_EDITMODE_OBJECTS, true);
    cmd.SetEventCustomData(cmdData);
	GetEventHandlersTable()->FireEvent(EVENTID_TOOLCMD, &cmd);
}


/// @brief Adjust dialog handler.
/// @param event - event structute.
void CEditorFrame::OnAdjustDlg(wxCommandEvent& event)
{
    m_pObjectsFrame->Show(false);
    m_pAdjustFrame->Show(true);
    m_pSettingsFrame->Show(false);
	GetToolSettings()->SetEditMode(EDITMODE_ADJUST);

    CommonToolEvent<ToolCmdEventData> cmd(EVENTID_TOOLCMD);
    ToolCmdEventData cmdData (CMD_EDITMODE_ADJUST, true);
    cmd.SetEventCustomData(cmdData);
	GetEventHandlersTable()->FireEvent(EVENTID_TOOLCMD, &cmd);
}


/// @brief Settings dialog handler.
/// @param event - event structute.
void CEditorFrame::OnSettingsDlg(wxCommandEvent& event)
{
    m_pObjectsFrame->Show(false);
    m_pAdjustFrame->Show(false);
    m_pSettingsFrame->Show(true);
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
    char ResPath[2048];
	GetResourcePathASCII(ResPath, 2048);
	sprintf(ResPath, "%sGameResources\\Levels", ResPath);

    wxDirDialog dialog(this, _T("Select level folder"), _T(ResPath), wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
    if (dialog.ShowModal() == wxID_OK)
    {
        wxLogMessage(_T("Selected path: %s"), dialog.GetPath().c_str());

		CommonToolEvent<LevelLoadEventData> cmd(EVENTID_LEVELLOAD);
	    LevelLoadEventData cmdData (dialog.GetPath());
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
