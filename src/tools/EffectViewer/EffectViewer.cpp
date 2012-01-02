#include <wx/wx.h>
#include "EffectViewer.h"
#include "EffectViewerFrame.h"
#include "OrangeGrass.h"


IMPLEMENT_APP(CEffectViewerApp)


/// @brief Initializing handler.
/// @return true if success
bool CEffectViewerApp::OnInit()
{
    char path[OG_MAX_PATH];
    GetResourcePathASCII(path, OG_MAX_PATH);
    std::string strPath = std::string(path) + std::string("/../assets/");
    StartOrangeGrass(strPath, false);

    CEffectViewerFrame* pFrame = new CEffectViewerFrame(NULL);
	SetTopWindow(pFrame);
	pFrame->Centre();
	pFrame->Show();

	return true;
}
