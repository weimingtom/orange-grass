#ifndef EDITOROBJECTSFRAME_H_
#define EDITOROBJECTSFRAME_H_

#include "wx/image.h"
#include "wx/imaglist.h"
#include "wx/bmpcbox.h"
#include "wx/htmllbox.h"
#include <ToolFramework.h>
#include <vector>


/// @brief Application's tool window frame.
class CEditorObjectsFrame : public wxMDIChildFrame
{
public:

    /// @brief Constructor.
    /// @param parent - parent window.
    /// @param title - window title.
    /// @param pos - window position.
    /// @param size - window size.
    /// @param style - window style.
    CEditorObjectsFrame (	wxMDIParentFrame *parent, 
							const wxString& title, 
							const wxPoint& pos,
							const wxSize& size, 
							long style = wxCAPTION);

private:

	/// @brief Resource loading event handler
	void OnLoadResource ( CommonToolEvent<ResLoadEventData>& event );

	/// @brief Resource switching event handler
	void OnResourceSwitch ( wxCommandEvent& event );

private:

	DECLARE_EVENT_TABLE()

    wxPanel*    m_pPanel;
    wxSimpleHtmlListBox*    m_pObjectsList;
    std::map<int, ResourceItem*> m_ItemList;
};

#endif