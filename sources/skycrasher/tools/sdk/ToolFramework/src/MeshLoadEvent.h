#ifndef MESHLOADINGEVENT_H_
#define MESHLOADINGEVENT_H_
#include <wx/treectrl.h>
#include "CommonToolEvent.h"


struct MeshLoadEventData
{
    MeshLoadEventData () {}
    MeshLoadEventData (const wxString& _name, unsigned int _id, const wxTreeItemId& _parentItem)
    {
        m_name = _name;
        m_id = _id;
        m_parentItem = _parentItem;
    }

    wxString m_name;
    unsigned int m_id;
    wxTreeItemId m_parentItem;
};


DECLARE_EVENT_TYPE( EVENTID_MESHLOAD, -1 )

typedef void (wxEvtHandler::*MeshLoadEventFunction)(CommonToolEvent<MeshLoadEventData> &);

#define MeshLoadEventHandler(func)                                   \
	(wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)\
	wxStaticCastEvent(MeshLoadEventFunction, &func)                    
 
#define EVT_MESHLOAD(id, fn)                                         \
	DECLARE_EVENT_TABLE_ENTRY( EVENTID_MESHLOAD, id, wxID_ANY,	    \
	(wxObjectEventFunction)(wxEventFunction)						\
	(wxCommandEventFunction) wxStaticCastEvent(MeshLoadEventFunction, &fn), (wxObject*) NULL ),


#endif