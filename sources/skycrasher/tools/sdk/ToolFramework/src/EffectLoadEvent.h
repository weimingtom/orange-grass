#ifndef EFFECTLOADINGEVENT_H_
#define EFFECTLOADINGEVENT_H_
#include "CommonToolEvent.h"


struct EffectLoadEventData
{
    EffectLoadEventData () {}
    EffectLoadEventData (void* _pData)
    {
        m_pData = _pData;
    }

    void* m_pData;
};


DECLARE_EVENT_TYPE( EVENTID_EFFECTLOAD, -1 )

typedef void (wxEvtHandler::*EffectLoadEventFunction)(CommonToolEvent<EffectLoadEventData> &);

#define EffectLoadEventHandler(func)                                   \
	(wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)\
	wxStaticCastEvent(EffectLoadEventFunction, &func)                    
 
#define EVT_EFFECTLOAD(id, fn)                                         \
	DECLARE_EVENT_TABLE_ENTRY( EVENTID_EFFECTLOAD, id, wxID_ANY,	    \
	(wxObjectEventFunction)(wxEventFunction)						\
	(wxCommandEventFunction) wxStaticCastEvent(EffectLoadEventFunction, &fn), (wxObject*) NULL ),


#endif