#ifndef RESOURCELOADINGEVENT_H_
#define RESOURCELOADINGEVENT_H_
#include "CommonToolEvent.h"


struct ResLoadEventData
{
    ResLoadEventData () {}
    ResLoadEventData (const wxString& _res, const wxString& _group, const wxString& _icon)
    {
        m_Resource = _res;
        m_ResourceGroup = _group;
        m_ResourceIcon = _icon;
    }

    wxString	m_Resource;
    wxString	m_ResourceGroup;
    wxString	m_ResourceIcon;
};


DECLARE_EVENT_TYPE( EVENTID_RESLOAD, -1 )

typedef void (wxEvtHandler::*ResLoadEventFunction)(CommonToolEvent<ResLoadEventData> &);

#define ResLoadEventHandler(func)                                   \
	(wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)\
	wxStaticCastEvent(ResLoadEventFunction, &func)                    
 
#define EVT_RESLOAD(id, fn)                                         \
	DECLARE_EVENT_TABLE_ENTRY( EVENTID_RESLOAD, id, wxID_ANY,	    \
	(wxObjectEventFunction)(wxEventFunction)						\
	(wxCommandEventFunction) wxStaticCastEvent(ResLoadEventFunction, &fn), (wxObject*) NULL ),


#endif