#include <wx/wx.h>
#include "Editor.h"
#include "EditorFrame.h"


IMPLEMENT_APP(CEditorApp)


/// @brief Initializing handler.
/// @return true if success
bool CEditorApp::OnInit()
{
    CEditorFrame* pFrame = new CEditorFrame(NULL, wxID_ANY, "OG Editor", wxDefaultPosition, wxDefaultSize, wxSYSTEM_MENU | wxCLOSE_BOX | wxCAPTION | wxCLIP_CHILDREN);
	SetTopWindow(pFrame);
	pFrame->Centre();
	pFrame->Show();
    return true;
}
