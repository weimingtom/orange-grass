#ifndef VIEWEROUTPUTFRAME_H_
#define VIEWEROUTPUTFRAME_H_

#include "ViewerCanvas.h"


class CViewerOutputFrame: public wxMDIChildFrame
{
public:

    /// @brief Constructor.
    /// @param parent - parent window.
    /// @param title - window title.
    /// @param pos - window position.
    /// @param size - window size.
    /// @param style - window style.
    CViewerOutputFrame (    wxMDIParentFrame *parent, 
                            const wxString& title, 
                            const wxPoint& pos,
                            const wxSize& size, 
                            long style = wxDEFAULT_FRAME_STYLE);

private:

    DECLARE_EVENT_TABLE()

    CViewerCanvas*      m_pCanvas;
};

#endif