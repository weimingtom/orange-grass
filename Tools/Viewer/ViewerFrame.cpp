#include <wx/wx.h>
#include "ViewerFrame.h"
#include <ToolFramework.h>
#include "sample.xpm"


#define ID_DEF_ABOUT		10000
#define ID_DEF_COORDGRID	10001
#define ID_DEF_AABB			10002

const int ID_TOOLBAR = 500;

static const long TOOLBAR_STYLE = wxTB_FLAT | wxTB_DOCKABLE | wxTB_TEXT;


BEGIN_EVENT_TABLE(CViewerFrame, wxMDIParentFrame)
    EVT_MENU (wxID_EXIT,    CViewerFrame::OnExit)
    EVT_MENU (ID_DEF_ABOUT, CViewerFrame::OnAboutDlg)
    EVT_MENU (ID_DEF_COORDGRID, CViewerFrame::OnCoordGrid)
    EVT_MENU (ID_DEF_AABB, CViewerFrame::OnBounds)
END_EVENT_TABLE()


/// @brief Factory method.
/// @return Pointer to a created frame.
CViewerFrame* CViewerFrame::Create()
{
    wxString str = wxT("OG Model Viewer");

    CViewerFrame* pFrame = new CViewerFrame(NULL, str, wxDefaultPosition, wxSize(640, 480));

    wxMenuBar* pMenuBar = new wxMenuBar ();
    wxMenu* pWindowMenu = new wxMenu ();
    wxMenu* pHelpMenu = new wxMenu ();
    pWindowMenu->Append(wxID_EXIT, _T("&Close"));
    pWindowMenu->Append(ID_DEF_COORDGRID, _T("&Show coord. grid"), _T("Show coord. grid"), wxITEM_CHECK);
    pWindowMenu->Append(ID_DEF_AABB, _T("Show &Bounds"), _T("Show bounds"), wxITEM_CHECK);
    pHelpMenu->Append(ID_DEF_ABOUT, _T("&About"));
    pMenuBar->Append(pWindowMenu, _T("&Viewer"));
    pMenuBar->Append(pHelpMenu, _T("&Help"));
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
CViewerFrame::CViewerFrame( wxWindow *parent, 
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

    m_pToolFrame = new CViewerToolFrame (this, _T("Tools"), wxDefaultPosition, wxSize(80, 395));
    m_pToolFrame->Show(true);

    m_pOutputFrame = new CViewerOutputFrame (this, _T("3D View"), wxPoint(125, 0), wxSize(480, 320));
    m_pOutputFrame->Show(true);
}


/// @brief App exit handler.
/// @param event - event structute.
void CViewerFrame::OnExit( wxCommandEvent& WXUNUSED(event) )
{
    Close(true);
}


/// @brief About dialog handler.
/// @param event - event structute.
void CViewerFrame::OnAboutDlg( wxCommandEvent& WXUNUSED(event) )
{
}


/// @brief Coord. grid switch handler.
/// @param event - event structute.
void CViewerFrame::OnCoordGrid(wxCommandEvent& event)
{
    CommonToolEvent<ToolCmdEventData> cmd(EVENTID_TOOLCMD);
    ToolCmdEventData cmdData (CMD_COORDGRID, event.IsChecked ());
    cmd.SetEventCustomData(cmdData);
	GetEventHandlersTable()->FireEvent(EVENTID_TOOLCMD, &cmd);
}


/// @brief Bounds switch handler.
/// @param event - event structute.
void CViewerFrame::OnBounds(wxCommandEvent& event)
{
    CommonToolEvent<ToolCmdEventData> cmd(EVENTID_TOOLCMD);
    ToolCmdEventData cmdData (CMD_AABB, event.IsChecked ());
    cmd.SetEventCustomData(cmdData);
	GetEventHandlersTable()->FireEvent(EVENTID_TOOLCMD, &cmd);
}


/// @brief Populate the toolbar.
/// @param toolBar - toolbar.
void CViewerFrame::PopulateToolbar(wxToolBarBase* toolBar)
{
    enum
    {
        Tool_open,
        Tool_help,
        Tool_Max
    };

    wxBitmap toolBarBitmaps[Tool_Max];

    toolBarBitmaps[Tool_open] = wxBitmap(wxT("Resources\\open.bmp"), wxBITMAP_TYPE_BMP);
    toolBarBitmaps[Tool_help] = wxBitmap(wxT("Resources\\help.bmp"), wxBITMAP_TYPE_BMP);

    int w = toolBarBitmaps[Tool_open].GetWidth();
    int h = toolBarBitmaps[Tool_open].GetHeight();

    toolBar->SetToolBitmapSize(wxSize(w, h));

    toolBar->AddTool(wxID_OPEN, _T("Open"),
                     toolBarBitmaps[Tool_open], wxNullBitmap, wxITEM_NORMAL,
                     _T("Open file"), _T("This is help for open file tool"));
    toolBar->AddSeparator();
    toolBar->AddTool(wxID_HELP, _T("Help"), toolBarBitmaps[Tool_help], _T("Help button"), wxITEM_CHECK);
    toolBar->Realize();
}
