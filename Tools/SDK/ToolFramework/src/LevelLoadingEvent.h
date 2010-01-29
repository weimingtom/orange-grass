#ifndef LEVELLOADINGEVENT_H_
#define LEVELLOADINGEVENT_H_
#include "CommonToolEvent.h"


struct LevelLoadEventData
{
    LevelLoadEventData () {}
    LevelLoadEventData (const wxString& _path)
    {
        m_Path = _path;
    }

    wxString	m_Path;
};


DECLARE_EVENT_TYPE( EVENTID_LEVELLOAD, -1 )

typedef void (wxEvtHandler::*LevelLoadEventFunction)(CommonToolEvent<LevelLoadEventData> &);

#define LevelLoadEventHandler(func)                                 \
	(wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)\
	wxStaticCastEvent(LevelLoadEventFunction, &func)                    
 
#define EVT_LEVELLOAD(id, fn)                                       \
	DECLARE_EVENT_TABLE_ENTRY( EVENTID_LEVELLOAD, id, wxID_ANY,	    \
	(wxObjectEventFunction)(wxEventFunction)						\
	(wxCommandEventFunction) wxStaticCastEvent(LevelLoadEventFunction, &fn), (wxObject*) NULL ),


#endif