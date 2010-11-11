#ifndef EDITORFRAME_H_
#define EDITORFRAME_H_

#include <wx/aui/aui.h>
#include "wx/image.h"
#include "wx/imaglist.h"
#include "wx/bmpcbox.h"
#include "wx/htmllbox.h"
#include "wx/clrpicker.h"
#include "wx/treectrl.h"
#include "wx/slider.h"
#include <ToolFramework.h>
#include <vector>
#include "EditorCanvas.h"

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

    /// @brief Set Objects mode.
    void SetObjectsMode();

    /// @brief Set Adjust mode.
    void SetAdjustMode();

    /// @brief Set Settings mode.
    void SetSettingsMode();

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

	/// @brief Settings switching event handler
	void OnSettingsSwitch ( wxTreeEvent& event );

	/// @brief color event handler
	void OnColorChange(wxColourPickerEvent& event);

	/// @brief Light X direction slider event handler
	/// @param event - event struct
	void OnXDirSlider(wxScrollEvent& event);

	/// @brief Light Z direction slider event handler
	/// @param event - event struct
	void OnZDirSlider(wxScrollEvent& event);

	/// @brief fog color event handler
	void OnFogColorChange(wxColourPickerEvent& event);

	/// @brief Fog near slider event handler
	/// @param event - event struct
	void OnFogNearSlider(wxScrollEvent& event);

	/// @brief Fog far slider event handler
	/// @param event - event struct
	void OnFogFarSlider(wxScrollEvent& event);

	/// @brief Level load event handler
	/// @param event - event structute.
	void OnLevelLoadEvent(CommonToolEvent<LevelLoadEventData>& event);

	/// Create settings panel
	void CreateSettingsPanelControls(wxPanel* _pPanel);

	/// Create lighting panel
	void CreateLightingPanelControls(wxPanel* _pPanel);

	/// Fire update event.
	void FireUpdateEvent();

private:

    DECLARE_EVENT_TABLE()

    wxToolBar*				m_pToolBar;
    wxAuiManager			m_Manager;

	CEditorCanvas*			m_pCanvas;

    wxAuiNotebook*          m_pToolsNotebook;
	wxPanel*                m_pToolsPage1;
	wxPanel*                m_pToolsPage2;
	wxPanel*                m_pToolsPage3;

	wxTreeCtrl*				m_pSettingsTree;

	wxColourPickerCtrl*		m_pColorPicker;
	wxSlider*				m_pXDirSlider;
	wxSlider*				m_pZDirSlider;

	wxColourPickerCtrl*		m_pFogColorPicker;
	wxSlider*				m_pFogNearSlider;
	wxSlider*				m_pFogFarSlider;

    wxSimpleHtmlListBox*    m_pObjectsList;
    std::map<int, ResourceItem*> m_ItemList;
};


#endif
