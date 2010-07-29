#ifndef EDITORSETTINGSFRAME_H_
#define EDITORSETTINGSFRAME_H_

#include "wx/clrpicker.h"
#include <ToolFramework.h>
#include <vector>


/// @brief Application's tool window frame.
class CEditorSettingsFrame : public wxMDIChildFrame
{
public:

    /// @brief Constructor.
    /// @param parent - parent window.
    /// @param title - window title.
    /// @param pos - window position.
    /// @param size - window size.
    /// @param style - window style.
    CEditorSettingsFrame ( wxMDIParentFrame *parent, 
						const wxString& title, 
						const wxPoint& pos,
						const wxSize& size, 
						long style = wxCAPTION);

private:

    DECLARE_EVENT_TABLE()

    wxPanel*    m_pPanel;
};

#endif