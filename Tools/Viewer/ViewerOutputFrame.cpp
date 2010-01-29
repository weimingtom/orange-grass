#include <wx/wx.h>
#include "ViewerOutputFrame.h"
#include "sample.xpm"


BEGIN_EVENT_TABLE(CViewerOutputFrame, wxMDIChildFrame)
END_EVENT_TABLE()


/// @brief Constructor.
/// @param parent - parent window.
/// @param title - window title.
/// @param pos - window position.
/// @param size - window size.
/// @param style - window style.
CViewerOutputFrame::CViewerOutputFrame( wxMDIParentFrame *parent, 
                                        const wxString& title, 
                                        const wxPoint& pos,
                                        const wxSize& size, 
                                        long style) : wxMDIChildFrame(parent, wxID_ANY, title, pos, size, style)
{
    SetIcon(wxIcon(sample_xpm));

    m_pCanvas = new CViewerCanvas(this, wxID_ANY, pos, size);
}
