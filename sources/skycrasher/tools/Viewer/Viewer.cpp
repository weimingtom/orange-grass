#include <wx/wx.h>
#include "Viewer.h"
#include "ViewerFrame.h"
#include "Game.h"


IMPLEMENT_APP(CViewerApp)


/// @brief Initializing handler.
/// @return true if success
bool CViewerApp::OnInit()
{
    char path[OG_MAX_PATH];
    GetResourcePathASCII(path, OG_MAX_PATH);
    std::string strPath = std::string(path) + std::string("/../assets/");
    StartOrangeGrass(strPath, false);
    StartGameCore();

    m_pFrame = new CViewerFrame(NULL);
	SetTopWindow(m_pFrame);
	m_pFrame->Centre();
	m_pFrame->Show();

    return true;
}


/// @brief Destroying handler.
/// @return code
int CViewerApp::OnExit()
{
    FinishGameCore();
    FinishOrangeGrass();
    return 0;
}
