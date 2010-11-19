#include <wx/wx.h>
#include <wx/gdicmn.h>
#include "EffectViewerFrame.h"
#include <ToolFramework.h>
#include "sample.xpm"


#define ID_DEF_ABOUT		10000
#define ID_DEF_COORDGRID	10001
#define ID_DEF_AABB			10002

const int ID_TOOLBAR = 500;

static const long TOOLBAR_STYLE = wxTB_FLAT | wxTB_DOCKABLE | wxTB_TEXT;


BEGIN_EVENT_TABLE(CEffectViewerFrame, wxFrame)
EVT_MENU (wxID_EXIT,    CEffectViewerFrame::OnExit)
EVT_MENU (ID_DEF_ABOUT, CEffectViewerFrame::OnAboutDlg)
EVT_MENU (ID_DEF_COORDGRID, CEffectViewerFrame::OnCoordGrid)
EVT_MENU (ID_DEF_AABB, CEffectViewerFrame::OnBounds)
EVT_RESLOAD( wxID_ANY, CEffectViewerFrame::OnLoadResource )
END_EVENT_TABLE()


/// @brief Constructor.
/// @param parent - parent window.
/// @param title - window title.
/// @param pos - window position.
/// @param size - window size.
/// @param style - window style.
CEffectViewerFrame::CEffectViewerFrame( wxWindow *parent, 
						   wxWindowID id,
						   const wxString & title,
						   const wxPoint & pos,
						   const wxSize & size,
						   long style)
{
	Create(parent, id, title, pos, size, style);
}


/// Create frame
bool CEffectViewerFrame::Create(wxWindow * parent, 
						  wxWindowID id,
						  const wxString & title,
						  const wxPoint & pos,
						  const wxSize & size,
						  long style)
{
    int w, h;
    wxDisplaySize(&w, &h);
    wxSize appSize = wxSize(w*0.5, h*0.5);

	wxFrame::Create(parent, id, title, pos, appSize, style);

	SetIcon(wxIcon(sample_xpm));

	wxMenuBar* pMenuBar = new wxMenuBar ();
	wxMenu* pWindowMenu = new wxMenu ();
	wxMenu* pHelpMenu = new wxMenu ();
	pWindowMenu->Append(wxID_EXIT, _T("&Close"));
	wxMenuItem* pCoordItem = pWindowMenu->Append(ID_DEF_COORDGRID, _T("&Show coord. grid"), _T("Show coord. grid"), wxITEM_CHECK);
	pCoordItem->Check(false);
	pWindowMenu->Append(ID_DEF_AABB, _T("Show &Bounds"), _T("Show bounds"), wxITEM_CHECK);
	pHelpMenu->Append(ID_DEF_ABOUT, _T("&About"));
	pMenuBar->Append(pWindowMenu, _T("&EffectViewer"));
	pMenuBar->Append(pHelpMenu, _T("&Help"));
	SetMenuBar(pMenuBar);

	SetToolBar(NULL);

	style &= ~(wxTB_HORIZONTAL | wxTB_VERTICAL | wxTB_BOTTOM | wxTB_RIGHT | wxTB_HORZ_LAYOUT);
	style |= wxTB_TOP;
	style |= wxTB_NO_TOOLTIPS;
	m_pToolBar = CreateToolBar(style, ID_TOOLBAR);
	PopulateToolbar(m_pToolBar);

	m_pCanvas = new CEffectViewerCanvas(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

	wxSize treeSize = wxSize(appSize.x * 0.2, appSize.y);
	m_pTree = new wxTreeCtrl(this, wxID_ANY, wxDefaultPosition, treeSize);
	m_pTree->AddRoot(_T("Resources"));
	m_pTree->Expand(m_pTree->GetRootItem());
	GetEventHandlersTable()->AddEventHandler(EVENTID_RESLOAD, this);
	m_pTree->Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( CEffectViewerFrame::OnResourceSwitch ), NULL, this );

	m_Manager.SetManagedWindow(this);
	m_Manager.AddPane(m_pCanvas, wxAuiPaneInfo().CenterPane());
	m_Manager.AddPane(m_pTree, wxAuiPaneInfo().Left().Layer(1).CloseButton(false).Caption(wxT("Tools")));
	m_Manager.Update();

	return true;
}


/// Destructor
CEffectViewerFrame::~CEffectViewerFrame()
{
	m_Manager.UnInit();
}


/// @brief App exit handler.
/// @param event - event structute.
void CEffectViewerFrame::OnExit( wxCommandEvent& WXUNUSED(event) )
{
	Close(true);
}


/// @brief About dialog handler.
/// @param event - event structute.
void CEffectViewerFrame::OnAboutDlg( wxCommandEvent& WXUNUSED(event) )
{
}


/// @brief Coord. grid switch handler.
/// @param event - event structute.
void CEffectViewerFrame::OnCoordGrid(wxCommandEvent& event)
{
	CommonToolEvent<ToolCmdEventData> cmd(EVENTID_TOOLCMD);
	ToolCmdEventData cmdData (CMD_COORDGRID, event.IsChecked ());
	cmd.SetEventCustomData(cmdData);
	GetEventHandlersTable()->FireEvent(EVENTID_TOOLCMD, &cmd);
}


/// @brief Bounds switch handler.
/// @param event - event structute.
void CEffectViewerFrame::OnBounds(wxCommandEvent& event)
{
	CommonToolEvent<ToolCmdEventData> cmd(EVENTID_TOOLCMD);
	ToolCmdEventData cmdData (CMD_AABB, event.IsChecked ());
	cmd.SetEventCustomData(cmdData);
	GetEventHandlersTable()->FireEvent(EVENTID_TOOLCMD, &cmd);
}


/// @brief Populate the toolbar.
/// @param toolBar - toolbar.
void CEffectViewerFrame::PopulateToolbar(wxToolBarBase* toolBar)
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


/// @brief Adding resource group
void CEffectViewerFrame::AddResourceGroup ( ResourceType _type, const wxString& _name )
{
	ResourceGroup groupItem(_type, _name);
	groupItem.item = m_pTree->AppendItem(m_pTree->GetRootItem(), groupItem.name, -1, -1, 0);
	m_ResourceGroups.push_back(groupItem);
}


/// @brief Resource loading event handler
void CEffectViewerFrame::OnLoadResource ( CommonToolEvent<ResLoadEventData>& event )
{
	const ResLoadEventData& evtData = event.GetEventCustomData();
	wxString resourceText = evtData.m_Resource;

	m_pTree->AppendItem(m_pTree->GetRootItem(), resourceText, -1, -1, new ResourceItem(RESTYPE_MODEL, resourceText) );
	m_pTree->Expand(m_pTree->GetRootItem());
}


/// @brief Resource switching event handler
void CEffectViewerFrame::OnResourceSwitch ( wxTreeEvent& event )
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
