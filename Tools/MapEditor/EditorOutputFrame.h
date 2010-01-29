#ifndef EDITOROUTPUTFRAME_H_
#define EDITOROUTPUTFRAME_H_

#include "EditorCanvas.h"


class CEditorOutputFrame: public wxMDIChildFrame
{
public:

    /// @brief Constructor.
    /// @param parent - parent window.
    /// @param title - window title.
    /// @param pos - window position.
    /// @param size - window size.
    /// @param style - window style.
    CEditorOutputFrame (    wxMDIParentFrame *parent, 
                            const wxString& title, 
                            const wxPoint& pos,
                            const wxSize& size, 
                            long style = wxDEFAULT_FRAME_STYLE);

private:

    DECLARE_EVENT_TABLE()

    CEditorCanvas*      m_pCanvas;
};

#endif