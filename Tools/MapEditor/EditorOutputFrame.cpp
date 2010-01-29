#include <wx/wx.h>
#include "EditorOutputFrame.h"
#include "sample.xpm"


BEGIN_EVENT_TABLE(CEditorOutputFrame, wxMDIChildFrame)
END_EVENT_TABLE()


/// @brief Constructor.
/// @param parent - parent window.
/// @param title - window title.
/// @param pos - window position.
/// @param size - window size.
/// @param style - window style.
CEditorOutputFrame::CEditorOutputFrame( wxMDIParentFrame *parent, 
                                        const wxString& title, 
                                        const wxPoint& pos,
                                        const wxSize& size, 
                                        long style) : wxMDIChildFrame(parent, wxID_ANY, title, pos, size, style)
{
    SetIcon(wxIcon(sample_xpm));

    m_pCanvas = new CEditorCanvas(this, wxID_ANY, pos, size);
}
