#ifndef VIEWERFRAME_H_
#define VIEWERFRAME_H_

#include "ViewerToolFrame.h"
#include "ViewerOutputFrame.h"


/// @brief Application's parent window frame.
class CViewerFrame: public wxMDIParentFrame
{
public:
    
    /// @brief Factory method.
    /// @return Pointer to a created frame.
    static CViewerFrame* Create();

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

    /// @brief Constructor.
    /// @param parent - parent window.
    /// @param title - window title.
    /// @param pos - window position.
    /// @param size - window size.
    /// @param style - window style.
    CViewerFrame (  wxWindow *parent, 
                    const wxString& title, 
                    const wxPoint& pos,
                    const wxSize& size, 
                    long style = wxDEFAULT_FRAME_STYLE);

    /// @brief Populate the toolbar.
    /// @param toolBar - toolbar.
    void PopulateToolbar(wxToolBarBase* toolBar);

private:

    DECLARE_EVENT_TABLE()

    CViewerToolFrame*			m_pToolFrame;
    CViewerOutputFrame*			m_pOutputFrame;
    wxToolBar*					m_pToolBar;
};


#endif

