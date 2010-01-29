#include <wx/wx.h>
#include "Viewer.h"
#include "ViewerFrame.h"


IMPLEMENT_APP(CViewerApp)


/// @brief Initializing handler.
/// @return true if success
bool CViewerApp::OnInit()
{
    (void) CViewerFrame::Create();
    return true;
}
