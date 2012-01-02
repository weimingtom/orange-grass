#include <wx/wx.h>
#include "Viewer.h"
#include "ViewerFrame.h"
#include "OrangeGrass.h"


IMPLEMENT_APP(CViewerApp)


/// @brief Initializing handler.
/// @return true if success
bool CViewerApp::OnInit()
{
    char path[OG_MAX_PATH];
    GetResourcePathASCII(path, OG_MAX_PATH);
    std::string strPath = std::string(path) + std::string("/../assets/");
    StartOrangeGrass(strPath, false);

    CViewerFrame* pFrame = new CViewerFrame(NULL);
	SetTopWindow(pFrame);
	pFrame->Centre();
	pFrame->Show();

    return true;
}
