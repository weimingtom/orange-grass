#include <wx/wx.h>
#include "EffectViewer.h"
#include "EffectViewerFrame.h"


IMPLEMENT_APP(CEffectViewerApp)


/// @brief Initializing handler.
/// @return true if success
bool CEffectViewerApp::OnInit()
{
    CEffectViewerFrame* pFrame = new CEffectViewerFrame(NULL);
	SetTopWindow(pFrame);
	pFrame->Centre();
	pFrame->Show();
    return true;
}
