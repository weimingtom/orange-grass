#ifndef EDITORFRAME_H_
#define EDITORFRAME_H_

#include <wx/aui/aui.h>
#include "wx/image.h"
#include "wx/imaglist.h"
#include "wx/bmpcbox.h"
#include "wx/htmllbox.h"
#include <ToolFramework.h>
#include <vector>
#include "EditorCanvas.h"
//#include "EditorOutputFrame.h"
//#include "EditorObjectsFrame.h"
//#include "EditorAdjustFrame.h"
//#include "EditorSettingsFrame.h"
//#include "EditorInfoFrame.h"

#define wxDWSTitleStr _("OG Editor")

/// @brief Application's parent window frame.
class CEditorFrame : public wxFrame
{
public:
    /// @brief Constructor.
    /// @param parent - parent window.
    /// @param title - window title.
    /// @param pos - window position.
    /// @param size - window size.
    /// @param style - window style.
	CEditorFrame (  wxWindow *parent, 
		wxWindowID id = wxID_ANY,
		const wxString & title = wxDWSTitleStr,
		const wxPoint & pos = wxDefaultPosition,
		const wxSize & size = wxDefaultSize,
		long style = wxDEFAULT_FRAME_STYLE);

	/// Destructor
	virtual ~CEditorFrame();

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

    /// @brief Bounds switch handler.
    /// @param event - event structute.
    void OnBounds(wxCommandEvent& event);

private:

    /// @brief Populate the toolbar.
    /// @param toolBar - toolbar.
    void PopulateToolbar(wxToolBarBase* toolBar);

    /// @brief Objects dialog handler.
    /// @param event - event structute.
    void OnObjectsDlg(wxCommandEvent& event);

    /// @brief Adjust dialog handler.
    /// @param event - event structute.
    void OnAdjustDlg(wxCommandEvent& event);

    /// @brief Settings dialog handler.
    /// @param event - event structute.
    void OnSettingsDlg(wxCommandEvent& event);

    /// @brief Level open handler.
    /// @param event - event structute.
    void OnOpenLevel(wxCommandEvent& event);

    /// @brief Level save handler.
    /// @param event - event structute.
    void OnSaveLevel(wxCommandEvent& event);

    /// @brief Resource loading event handler
	void OnLoadResource ( CommonToolEvent<ResLoadEventData>& event );

	/// @brief Resource switching event handler
	void OnResourceSwitch ( wxCommandEvent& event );

private:

    DECLARE_EVENT_TABLE()

    //CEditorOutputFrame*		m_pOutputFrame;
    //CEditorObjectsFrame*	m_pObjectsFrame;
    //CEditorAdjustFrame*	    m_pAdjustFrame;
    //CEditorSettingsFrame*	m_pSettingsFrame;
    //CEditorInfoFrame*		m_pInfoFrame;

    wxToolBar*				m_pToolBar;
    wxAuiManager			m_Manager;
    CEditorCanvas*			m_pCanvas;
    wxAuiNotebook*          m_pNotebook;
	wxPanel *               m_pPage1;
	wxPanel *               m_pPage2;

    wxSimpleHtmlListBox*    m_pObjectsList;
    std::map<int, ResourceItem*> m_ItemList;

    wxPanel*                m_pLogPanel;
	wxListBox*	            m_pLogBox;
};


#endif
