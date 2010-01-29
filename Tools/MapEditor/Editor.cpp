#include <wx/wx.h>
#include "Editor.h"
#include "EditorFrame.h"


IMPLEMENT_APP(CEditorApp)


/// @brief Initializing handler.
/// @return true if success
bool CEditorApp::OnInit()
{
    (void) CEditorFrame::Create();
    return true;
}
