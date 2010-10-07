#include <wx/wx.h>
#include "Viewer.h"
#include "ViewerFrame.h"


IMPLEMENT_APP(CViewerApp)


/// @brief Initializing handler.
/// @return true if success
bool CViewerApp::OnInit()
{
    CViewerFrame* pFrame = new CViewerFrame(NULL);
	SetTopWindow(pFrame);
	pFrame->Centre();
	pFrame->Show();
    return true;
}
