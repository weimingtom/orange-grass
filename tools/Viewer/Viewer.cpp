#include <wx/wx.h>
#include "Viewer.h"
#include "ViewerFrame.h"
#include "OrangeGrass.h"


IMPLEMENT_APP(CViewerApp)


/// @brief Initializing handler.
/// @return true if success
bool CViewerApp::OnInit()
{
	StartOrangeGrass();

    CViewerFrame* pFrame = new CViewerFrame(NULL);
	SetTopWindow(pFrame);
	pFrame->Centre();
	pFrame->Show();

    return true;
}
