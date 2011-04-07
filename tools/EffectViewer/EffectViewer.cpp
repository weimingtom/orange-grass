#include <wx/wx.h>
#include "EffectViewer.h"
#include "EffectViewerFrame.h"
#include "OrangeGrass.h"


IMPLEMENT_APP(CEffectViewerApp)


/// @brief Initializing handler.
/// @return true if success
bool CEffectViewerApp::OnInit()
{
	StartOrangeGrass();

    CEffectViewerFrame* pFrame = new CEffectViewerFrame(NULL);
	SetTopWindow(pFrame);
	pFrame->Centre();
	pFrame->Show();

	FinishOrangeGrass();

	return true;
}
