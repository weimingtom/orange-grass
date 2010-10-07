#ifndef VIEWERFRAME_H_
#define VIEWERFRAME_H_

#include <wx/aui/aui.h>
#include <ToolFramework.h>
#include <vector>
#include "ViewerCanvas.h"

#define wxDWSTitleStr _("OG Viewer")

/// @brief Application's parent window frame.
class CViewerFrame: public wxFrame
{
public:

    /// @brief Constructor.
    /// @param parent - parent window.
    /// @param title - window title.
    /// @param pos - window position.
    /// @param size - window size.
    /// @param style - window style.
	CViewerFrame (  wxWindow *parent, 
		wxWindowID id = wxID_ANY,
		const wxString & title = wxDWSTitleStr,
		const wxPoint & pos = wxDefaultPosition,
		const wxSize & size = wxDefaultSize,
		long style = wxDEFAULT_FRAME_STYLE);

	/// Destructor
	virtual ~CViewerFrame();

	/// Create frame
	bool Create(wxWindow * parent, 
		wxWindowID id = wxID_ANY,
		const wxString & title = wxDWSTitleStr,
		const wxPoint & pos = wxDefaultPosition,
		const wxSize & size = wxDefaultSize,
		long style = wxDEFAULT_FRAME_STYLE);

    /// @brief App exit handler.
    /// @param event - event structute.
    void OnExit(wxCommandEvent& event);

    /// @brief About dialog handler.
    /// @param event - event structute.
    void OnAboutDlg(wxCommandEvent& event);

    /// @brief Coord. grid switch handler.
    /// @param event - event structute.
    void OnCoordGrid(wxCommandEvent& event);

    /// @brief Bounds switch handler.
    /// @param event - event structute.
    void OnBounds(wxCommandEvent& event);

private:

    /// @brief Populate the toolbar.
    /// @param toolBar - toolbar.
    void PopulateToolbar(wxToolBarBase* toolBar);

	/// @brief Resource loading event handler
	void OnLoadResource ( CommonToolEvent<ResLoadEventData>& event );

	/// @brief Resource switching event handler
	void OnResourceSwitch ( wxTreeEvent& event );

	/// @brief Adding resource group
	void AddResourceGroup ( ResourceType _type, const wxString& _name );

private:

    DECLARE_EVENT_TABLE()

    wxToolBar*					m_pToolBar;
	wxAuiManager				m_Manager;
    CViewerCanvas*				m_pCanvas;

	wxTreeCtrl*					m_pTree;
	std::vector<ResourceGroup>	m_ResourceGroups;
	std::vector<ResourceItem>	m_ResourceItems;
};


#endif

