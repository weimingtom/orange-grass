#ifndef MATERIALADJUSTEVENT_H_
#define MATERIALADJUSTEVENT_H_
#include "CommonToolEvent.h"


enum MtlType
{
    MTLTYPE_DIF,
    MTLTYPE_AMB,
    MTLTYPE_SPC,
};


struct MtlAdjustEventData
{
    MtlAdjustEventData () {}
    MtlAdjustEventData (MtlType _type, float _val)
    {
        m_type = _type;
        m_val = _val;
    }

    MtlType m_type;
    float m_val;
};


DECLARE_EVENT_TYPE( EVENTID_MTLADJUST, -1 )

typedef void (wxEvtHandler::*MtlAdjustEventFunction)(CommonToolEvent<MtlAdjustEventData> &);

#define MtlAdjustEventHandler(func)                                 \
	(wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)\
	wxStaticCastEvent(MtlAdjustEventFunction, &func)                    
 
#define EVT_MTLADJUST(id, fn)                                       \
	DECLARE_EVENT_TABLE_ENTRY( EVENTID_MTLADJUST, id, wxID_ANY,	    \
	(wxObjectEventFunction)(wxEventFunction)						\
	(wxCommandEventFunction) wxStaticCastEvent(MtlAdjustEventFunction, &fn), (wxObject*) NULL ),


#endif