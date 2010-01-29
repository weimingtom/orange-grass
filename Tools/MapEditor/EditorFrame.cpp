#include <wx/wx.h>
#include "EditorFrame.h"
#include <ToolFramework.h>
#include "sample.xpm"


#define ID_DEF_ABOUT		10000
#define ID_DEF_AABB			10002
#define ID_DEF_HEIGHTMAP	10003
#define ID_DEF_COLOR		10004
#define ID_DEF_OBJECTS		10005

const int ID_TOOLBAR = 500;

static const long TOOLBAR_STYLE = wxTB_FLAT | wxTB_DOCKABLE | wxTB_TEXT;


BEGIN_EVENT_TABLE(CEditorFrame, wxMDIParentFrame)
    EVT_MENU (wxID_EXIT,		CEditorFrame::OnExit)
    EVT_MENU (wxID_OPEN,		CEditorFrame::OnOpenLevel)
    EVT_MENU (wxID_SAVE,		CEditorFrame::OnSaveLevel)
    EVT_MENU (ID_DEF_ABOUT,		CEditorFrame::OnAboutDlg)
    EVT_MENU (ID_DEF_HEIGHTMAP,	CEditorFrame::OnHeightmapDlg)
    EVT_MENU (ID_DEF_COLOR,		CEditorFrame::OnColorDlg)
    EVT_MENU (ID_DEF_OBJECTS,	CEditorFrame::OnObjectsDlg)
    EVT_MENU (ID_DEF_AABB,		CEditorFrame::OnBounds)
END_EVENT_TABLE()


/// @brief Factory method.
/// @return Pointer to a created frame.
CEditorFrame* CEditorFrame::Create()
{
    CEditorFrame* pFrame = new CEditorFrame(NULL, wxT("OG Level Editor"), wxDefaultPosition, wxSize(840, 640));

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

    m_pInfoFrame = new CEditorInfoFrame (this, wxT("Info"), wxPoint(0, 395), wxSize(820, 140));
    m_pInfoFrame->Show(true);

    m_pOutputFrame = new CEditorOutputFrame (this, wxT("3D View"), wxPoint(0, 0), wxSize(620, 395));
    m_pOutputFrame->Show(true);

    m_pHeightFrame = new CEditorHeightmapFrame (this, wxT("Heightmap"), wxPoint(620, 0), wxSize(200, 395));
    m_pHeightFrame->Show(false);

    m_pColorFrame = new CEditorColorFrame (this, wxT("Color"), wxPoint(620, 0), wxSize(200, 395));
    m_pColorFrame->Show(false);

    m_pObjectsFrame = new CEditorObjectsFrame (this, wxT("Objects"), wxPoint(620, 0), wxSize(200, 395));
    m_pObjectsFrame->Show(false);
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
        Tool_ed_hm,
        Tool_ed_color,
        Tool_ed_obj,
        Tool_Max
    };

    wxBitmap toolBarBitmaps[Tool_Max];

    toolBarBitmaps[Tool_open] = wxBitmap(wxT("Resources\\open.bmp"), wxBITMAP_TYPE_BMP);
    toolBarBitmaps[Tool_save] = wxBitmap(wxT("Resources\\save.bmp"), wxBITMAP_TYPE_BMP);
    toolBarBitmaps[Tool_help] = wxBitmap(wxT("Resources\\help.bmp"), wxBITMAP_TYPE_BMP);
    toolBarBitmaps[Tool_ed_hm] = wxBitmap(wxT("Resources\\ed_hm.bmp"), wxBITMAP_TYPE_BMP);
    toolBarBitmaps[Tool_ed_color] = wxBitmap(wxT("Resources\\ed_color.bmp"), wxBITMAP_TYPE_BMP);
    toolBarBitmaps[Tool_ed_obj] = wxBitmap(wxT("Resources\\ed_obj.bmp"), wxBITMAP_TYPE_BMP);

    int w = toolBarBitmaps[Tool_open].GetWidth();
    int h = toolBarBitmaps[Tool_open].GetHeight();

    toolBar->SetToolBitmapSize(wxSize(w, h));

    toolBar->AddTool(wxID_OPEN, wxT("Open"), toolBarBitmaps[Tool_open], wxT("Open level"), wxITEM_NORMAL);
    toolBar->AddTool(wxID_SAVE, wxT("Save"), toolBarBitmaps[Tool_save], wxT("Save level"), wxITEM_NORMAL);
    toolBar->AddSeparator();
    toolBar->AddTool(ID_DEF_HEIGHTMAP, wxT("Heightmap"), toolBarBitmaps[Tool_ed_hm], wxT("Heightmap"), wxITEM_NORMAL);
    toolBar->AddTool(ID_DEF_COLOR, wxT("Color"), toolBarBitmaps[Tool_ed_color], wxT("Color"), wxITEM_NORMAL);
    toolBar->AddTool(ID_DEF_OBJECTS, wxT("Objects"), toolBarBitmaps[Tool_ed_obj], wxT("Objects"), wxITEM_NORMAL);
    toolBar->Realize();
}


/// @brief Heightmap dialog handler.
/// @param event - event structute.
void CEditorFrame::OnHeightmapDlg(wxCommandEvent& event)
{
    m_pHeightFrame->Show(true);
    m_pColorFrame->Show(false);
    m_pObjectsFrame->Show(false);
	GetToolSettings()->SetEditMode(EDITMODE_HEIGHT);
}


/// @brief Color dialog handler.
/// @param event - event structute.
void CEditorFrame::OnColorDlg(wxCommandEvent& event)
{
    m_pHeightFrame->Show(false);
    m_pColorFrame->Show(true);
    m_pObjectsFrame->Show(false);
	GetToolSettings()->SetEditMode(EDITMODE_COLOR);
}


/// @brief Objects dialog handler.
/// @param event - event structute.
void CEditorFrame::OnObjectsDlg(wxCommandEvent& event)
{
    m_pHeightFrame->Show(false);
    m_pColorFrame->Show(false);
    m_pObjectsFrame->Show(true);
	GetToolSettings()->SetEditMode(EDITMODE_OBJECTS);
}


/// @brief Level open handler.
/// @param event - event structute.
void CEditorFrame::OnOpenLevel(wxCommandEvent& event)
{
    wxDirDialog dialog(this, _T("Select level folder"), _T(""), wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
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
}
