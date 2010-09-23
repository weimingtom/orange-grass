#ifndef RESOURCESWITCHEVENT_H_
#define RESOURCESWITCHEVENT_H_
#include "CommonToolEvent.h"
#include "ResourceGroup.h"


struct ResSwitchEventData
{
    ResSwitchEventData () {}
    ResSwitchEventData (const wxString& _res, const ResourceType& _type)
    {
        m_Resource = _res;
        m_ResourceType = _type;
    }

    wxString		m_Resource;
    ResourceType	m_ResourceType;
};


DECLARE_EVENT_TYPE( EVENTID_RESSWITCH, -1 )

typedef void (wxEvtHandler::*ResSwitchEventFunction)(CommonToolEvent<ResSwitchEventData> &);

#define ResSwitchEventHandler(func)                                 \
	(wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)\
	wxStaticCastEvent(ResSwitchEventFunction, &func)                    
 
#define EVT_RESSWITCH(id, fn)                                       \
	DECLARE_EVENT_TABLE_ENTRY( EVENTID_RESSWITCH, id, wxID_ANY,	    \
	(wxObjectEventFunction)(wxEventFunction)						\
	(wxCommandEventFunction) wxStaticCastEvent(ResSwitchEventFunction, &fn), (wxObject*) NULL ),

#endif