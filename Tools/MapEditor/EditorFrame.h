#ifndef EDITORFRAME_H_
#define EDITORFRAME_H_

#include "EditorOutputFrame.h"
#include "EditorObjectsFrame.h"
#include "EditorInfoFrame.h"


/// @brief Application's parent window frame.
class CEditorFrame: public wxMDIParentFrame
{
public:
    
    /// @brief Factory method.
    /// @return Pointer to a created frame.
    static CEditorFrame* Create();

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

    /// @brief Constructor.
    /// @param parent - parent window.
    /// @param title - window title.
    /// @param pos - window position.
    /// @param size - window size.
    /// @param style - window style.
    CEditorFrame (  wxWindow *parent, 
                    const wxString& title, 
                    const wxPoint& pos,
                    const wxSize& size, 
                    long style = wxDEFAULT_FRAME_STYLE);

    /// @brief Populate the toolbar.
    /// @param toolBar - toolbar.
    void PopulateToolbar(wxToolBarBase* toolBar);

    /// @brief Objects dialog handler.
    /// @param event - event structute.
    void OnObjectsDlg(wxCommandEvent& event);

    /// @brief Level open handler.
    /// @param event - event structute.
    void OnOpenLevel(wxCommandEvent& event);

    /// @brief Level save handler.
    /// @param event - event structute.
    void OnSaveLevel(wxCommandEvent& event);

private:

    DECLARE_EVENT_TABLE()

    CEditorOutputFrame*		m_pOutputFrame;
    CEditorObjectsFrame*	m_pObjectsFrame;
    CEditorInfoFrame*		m_pInfoFrame;
    wxToolBar*				m_pToolBar;
};


#endif
