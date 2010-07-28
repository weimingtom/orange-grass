#ifndef VIEWERTOOLFRAME_H_
#define VIEWERTOOLFRAME_H_

#include "wx/treectrl.h"
#include <ToolFramework.h>
#include <vector>


/// @brief Application's tool window frame.
class CViewerToolFrame: public wxMDIChildFrame
{
public:

    /// @brief Constructor.
    /// @param parent - parent window.
    /// @param title - window title.
    /// @param pos - window position.
    /// @param size - window size.
    /// @param style - window style.
    CViewerToolFrame (  wxMDIParentFrame *parent, 
                        const wxString& title, 
                        const wxPoint& pos,
                        const wxSize& size, 
                        long style = wxCAPTION);

private:

	/// @brief Resource loading event handler
	void OnLoadResource ( CommonToolEvent<ResLoadEventData>& event );

	/// @brief Resource switching event handler
	void OnResourceSwitch ( wxTreeEvent& event );

	/// @brief Adding resource group
	void AddResourceGroup ( ResourceType _type, const wxString& _name );

private:

    DECLARE_EVENT_TABLE()

    wxPanel*    m_pPanel;
    wxTreeCtrl* m_pTree;
	std::vector<ResourceGroup>	m_ResourceGroups;
	std::vector<ResourceItem>	m_ResourceItems;
};

#endif