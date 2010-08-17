#ifndef EDITORSETTINGSFRAME_H_
#define EDITORSETTINGSFRAME_H_

#include "wx/clrpicker.h"
#include "wx/treectrl.h"
#include <ToolFramework.h>
#include <vector>


struct SettingsItem : public wxTreeItemData
{
	SettingsItem (SettingsMode _type, const wxString& _name)
	{
		type = _type;
		name = _name;
	}

	SettingsMode	type;
	wxString		name;
};


/// @brief Application's tool window frame.
class CEditorSettingsFrame : public wxMDIChildFrame
{
public:

    /// @brief Constructor.
    /// @param parent - parent window.
    /// @param title - window title.
    /// @param pos - window position.
    /// @param size - window size.
    /// @param style - window style.
    CEditorSettingsFrame ( wxMDIParentFrame *parent, 
						const wxString& title, 
						const wxPoint& pos,
						const wxSize& size, 
						long style = wxCAPTION);

    /// @brief Settings switching event handler
    void OnSettingsSwitch ( wxTreeEvent& event );

private:

    DECLARE_EVENT_TABLE()

    wxPanel*        m_pPanel;
    wxTreeCtrl*     m_pTree;
};

#endif