#include <wx/wx.h>
#include "Editor.h"
#include "EditorFrame.h"
#include "OrangeGrass.h"


IMPLEMENT_APP(CEditorApp)


/// @brief Initializing handler.
/// @return true if success
bool CEditorApp::OnInit()
{
    char path[OG_MAX_PATH];
    GetResourcePathASCII(path, OG_MAX_PATH);
    std::string strPath = std::string(path) + std::string("/../assets/");
    StartOrangeGrass(strPath, false);

    CEditorFrame* pFrame = new CEditorFrame(
		NULL, wxID_ANY, "OG Editor", wxDefaultPosition, wxDefaultSize, 
		wxSYSTEM_MENU | wxCLOSE_BOX | wxCAPTION | wxCLIP_CHILDREN);
	SetTopWindow(pFrame);
	pFrame->Centre();
	pFrame->Show();

	return true;
}