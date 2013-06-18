#include <wx/wx.h>
#include <wx/gdicmn.h>
#include "ViewerFrame.h"
#include <ToolFramework.h>
#include "sample.xpm"


#define ID_DEF_ABOUT		10000
#define ID_DEF_COORDGRID	10001
#define ID_DEF_AABB			10002
#define ID_DEF_DIFCOLOR		10003
#define ID_DEF_AMBCOLOR		10004
#define ID_DEF_SPCCOLOR		10005

const int ID_TOOLBAR = 500;

static const long TOOLBAR_STYLE = wxTB_FLAT | wxTB_DOCKABLE | wxTB_TEXT;


BEGIN_EVENT_TABLE(CViewerFrame, wxFrame)
    EVT_MENU(wxID_EXIT,                 CViewerFrame::OnExit)
    EVT_MENU(wxID_SAVE,                 CViewerFrame::OnSave)
    EVT_MENU(ID_DEF_COORDGRID,          CViewerFrame::OnCoordGrid)
    EVT_MENU(ID_DEF_AABB,               CViewerFrame::OnBounds)
    EVT_RESLOAD(wxID_ANY,               CViewerFrame::OnLoadResource )
    EVT_MTLLOAD(wxID_ANY,               CViewerFrame::OnLoadMaterial )
    EVT_MESHLOAD(wxID_ANY,              CViewerFrame::OnLoadMesh )
    EVT_COMMAND_SCROLL(ID_DEF_DIFCOLOR, CViewerFrame::OnDiffuseSlider)
    EVT_COMMAND_SCROLL(ID_DEF_AMBCOLOR, CViewerFrame::OnAmbientSlider)
    EVT_COMMAND_SCROLL(ID_DEF_SPCCOLOR, CViewerFrame::OnSpecularSlider)
END_EVENT_TABLE()


/// @brief Constructor.
/// @param parent - parent window.
/// @param title - window title.
/// @param pos - window position.
/// @param size - window size.
/// @param style - window style.
CViewerFrame::CViewerFrame( wxWindow *parent, 
						   wxWindowID id,
						   const wxString & title,
						   const wxPoint & pos,
						   const wxSize & size,
						   long style)
{
	Create(parent, id, title, pos, size, style);
}


/// Create frame
bool CViewerFrame::Create(wxWindow * parent, 
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
	pCoordItem->Check(true);
	pWindowMenu->Append(ID_DEF_AABB, _T("Show &Bounds"), _T("Show bounds"), wxITEM_CHECK);
	pHelpMenu->Append(ID_DEF_ABOUT, _T("&About"));
	pMenuBar->Append(pWindowMenu, _T("&Viewer"));
	pMenuBar->Append(pHelpMenu, _T("&Help"));
	SetMenuBar(pMenuBar);

	SetToolBar(NULL);

	style &= ~(wxTB_HORIZONTAL | wxTB_VERTICAL | wxTB_BOTTOM | wxTB_RIGHT | wxTB_HORZ_LAYOUT);
	style |= wxTB_TOP;
	style |= wxTB_NO_TOOLTIPS;
	m_pToolBar = CreateToolBar(style, ID_TOOLBAR);
	PopulateToolbar(m_pToolBar);

	m_pCanvas = new CViewerCanvas(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

	wxSize treeSize = wxSize(appSize.x * 0.2, appSize.y);
	m_pTree = new wxTreeCtrl(this, wxID_ANY, wxDefaultPosition, treeSize);
	m_pTree->AddRoot(_T("Resources"));
	AddResourceGroup (RESTYPE_MODEL, wxT("Static"));
	AddResourceGroup (RESTYPE_MODEL, wxT("Units"));
	AddResourceGroup (RESTYPE_MODEL, wxT("Bonuses"));
	m_pTree->Expand(m_pTree->GetRootItem());
	GetEventHandlersTable()->AddEventHandler(EVENTID_RESLOAD, this);
	GetEventHandlersTable()->AddEventHandler(EVENTID_MTLLOAD, this);
	GetEventHandlersTable()->AddEventHandler(EVENTID_MESHLOAD, this);
	m_pTree->Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( CViewerFrame::OnResourceSwitch ), NULL, this );

	m_pSettingsPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, treeSize);
	wxSize panelSize = m_pSettingsPanel->GetSize();
	wxStaticText* DifClrDesc = new wxStaticText(m_pSettingsPanel, wxID_ANY, _T("Diffuse:"), wxPoint(5, 30), wxDefaultSize);
	m_pDiffuseSlider = new wxSlider(m_pSettingsPanel, ID_DEF_DIFCOLOR, 0, 0, 100, wxPoint(50, 5), wxSize(panelSize.GetWidth()*0.65f, 50), wxSL_LABELS|wxSL_TICKS);    m_pDiffuseSlider->Enable(false);	wxStaticText* AmbClrDesc = new wxStaticText(m_pSettingsPanel, wxID_ANY, _T("Ambient:"), wxPoint(5, 85), wxDefaultSize);
	m_pAmbientSlider = new wxSlider(m_pSettingsPanel, ID_DEF_AMBCOLOR, 0, 0, 100, wxPoint(50, 60), wxSize(panelSize.GetWidth()*0.65f, 50), wxSL_LABELS|wxSL_TICKS);    m_pAmbientSlider->Enable(false);	wxStaticText* SpcClrDesc = new wxStaticText(m_pSettingsPanel, wxID_ANY, _T("Specular:"), wxPoint(5, 140), wxDefaultSize);
	m_pSpecularSlider = new wxSlider(m_pSettingsPanel, ID_DEF_SPCCOLOR, 0, 0, 100, wxPoint(50, 115), wxSize(panelSize.GetWidth()*0.65f, 50), wxSL_LABELS|wxSL_TICKS);    m_pSpecularSlider->Enable(false);
	m_Manager.SetManagedWindow(this);
	m_Manager.AddPane(m_pCanvas, wxAuiPaneInfo().CenterPane());
	m_Manager.AddPane(m_pTree, wxAuiPaneInfo().Left().Layer(1).CloseButton(false).Caption(wxT("Tools")));
	m_Manager.AddPane(m_pSettingsPanel, wxAuiPaneInfo().Right().Layer(1).CloseButton(false).Caption(wxT("Settings")));
	m_Manager.Update();

	return true;
}


/// Destructor
CViewerFrame::~CViewerFrame()
{
	m_Manager.UnInit();
}


/// @brief App exit handler.
/// @param event - event structute.
void CViewerFrame::OnExit( wxCommandEvent& WXUNUSED(event) )
{
	Close(true);
}


/// @brief Save button handler.
/// @param event - event structute.
void CViewerFrame::OnSave(wxCommandEvent& event)
{
	CommonToolEvent<ToolCmdEventData> cmd(EVENTID_TOOLCMD);
	ToolCmdEventData cmdData (CMD_ITEM_SAVE, true);
	cmd.SetEventCustomData(cmdData);
	GetEventHandlersTable()->FireEvent(EVENTID_TOOLCMD, &cmd);
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
		Tool_save,
		Tool_Max
	};

	wxBitmap toolBarBitmaps[Tool_Max];

	toolBarBitmaps[Tool_save] = wxBitmap(wxT("Resources\\save.bmp"), wxBITMAP_TYPE_BMP);

	int w = toolBarBitmaps[Tool_save].GetWidth();
	int h = toolBarBitmaps[Tool_save].GetHeight();

	toolBar->SetToolBitmapSize(wxSize(w, h));

	toolBar->AddTool(wxID_SAVE, _T("Save"),
		toolBarBitmaps[Tool_save], wxNullBitmap, wxITEM_NORMAL,
		_T("Save actor"), _T("Save the changes to actor"));
	toolBar->Realize();
}


/// @brief Adding resource group
void CViewerFrame::AddResourceGroup ( ResourceType _type, const wxString& _name )
{
	ResourceGroup groupItem(_type, _name);
	groupItem.item = m_pTree->AppendItem(m_pTree->GetRootItem(), groupItem.name, -1, -1, 0);
	m_ResourceGroups.push_back(groupItem);
}


/// @brief Resource loading event handler
void CViewerFrame::OnLoadResource ( CommonToolEvent<ResLoadEventData>& event )
{
	const ResLoadEventData& evtData = event.GetEventCustomData();
	wxString resourceText = evtData.m_Resource;
	wxString resourceGroupText = evtData.m_ResourceGroup;

	std::vector<ResourceGroup>::const_iterator iter = m_ResourceGroups.begin();
	for (; iter != m_ResourceGroups.end(); ++iter)
	{
		if (resourceGroupText.CmpNoCase((*iter).name) == 0)
		{
			m_pTree->AppendItem((*iter).item, resourceText, -1, -1, new ResourceItem(RESTYPE_MODEL, resourceText, (*iter).item) );
			m_pTree->Expand((*iter).item);
		}
	}
}


/// @brief Material loading event handler
void CViewerFrame::OnLoadMaterial ( CommonToolEvent<MtlLoadEventData>& event )
{
	const MtlLoadEventData& evtData = event.GetEventCustomData();
    m_pAmbientSlider->Enable(true);    m_pDiffuseSlider->Enable(true);    m_pSpecularSlider->Enable(true);    m_pAmbientSlider->SetValue((int)(evtData.m_amb * 100.0f));
    m_pDiffuseSlider->SetValue((int)(evtData.m_dif * 100.0f));
    m_pSpecularSlider->SetValue((int)(evtData.m_spc * 100.0f));
}


/// @brief Mesh loading event handler
void CViewerFrame::OnLoadMesh ( CommonToolEvent<MeshLoadEventData>& event )
{
	const MeshLoadEventData& evtData = event.GetEventCustomData();
    if (!m_pTree->ItemHasChildren(evtData.m_parentItem))
    {
        m_pTree->AppendItem(evtData.m_parentItem, evtData.m_name, -1, -1, new ResourceItem(RESTYPE_MESH, evtData.m_name, evtData.m_parentItem));
    }
}


/// @brief Resource switching event handler
void CViewerFrame::OnResourceSwitch ( wxTreeEvent& event )
{
	if ( event.GetItem() == m_pTree->GetRootItem() )
		return;

	ResourceItem* pData = (ResourceItem *)m_pTree->GetItemData(event.GetItem());
	if(pData)
	{
		CommonToolEvent<ResSwitchEventData> cmd(EVENTID_RESSWITCH);
		cmd.SetEventCustomData(ResSwitchEventData(pData));
		GetEventHandlersTable()->FireEvent(EVENTID_RESSWITCH, &cmd);
	}
}


/// @brief Diffuse color slider event handler
/// @param event - event struct
void CViewerFrame::OnDiffuseSlider(wxScrollEvent& event)
{
    float fDif = (float)m_pDiffuseSlider->GetValue() / 100.0f;

    CommonToolEvent<MtlAdjustEventData> cmd(EVENTID_MTLADJUST);
    cmd.SetEventCustomData(MtlAdjustEventData(MTLTYPE_DIF, fDif));
    GetEventHandlersTable()->FireEvent(EVENTID_MTLADJUST, &cmd);
}


/// @brief Ambient color slider event handler
/// @param event - event struct
void CViewerFrame::OnAmbientSlider(wxScrollEvent& event)
{
    float fAmb = (float)m_pAmbientSlider->GetValue() / 100.0f;

    CommonToolEvent<MtlAdjustEventData> cmd(EVENTID_MTLADJUST);
    cmd.SetEventCustomData(MtlAdjustEventData(MTLTYPE_AMB, fAmb));
    GetEventHandlersTable()->FireEvent(EVENTID_MTLADJUST, &cmd);
}


/// @brief Specular color slider event handler
/// @param event - event struct
void CViewerFrame::OnSpecularSlider(wxScrollEvent& event)
{
    float fSpc = (float)m_pSpecularSlider->GetValue() / 100.0f;

    CommonToolEvent<MtlAdjustEventData> cmd(EVENTID_MTLADJUST);
    cmd.SetEventCustomData(MtlAdjustEventData(MTLTYPE_SPC, fSpc));
    GetEventHandlersTable()->FireEvent(EVENTID_MTLADJUST, &cmd);
}
