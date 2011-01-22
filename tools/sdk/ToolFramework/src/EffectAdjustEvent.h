#ifndef EFFECTADJUSTEVENT_H_
#define EFFECTADJUSTEVENT_H_
#include "CommonToolEvent.h"


enum ParamType
{
    PRMTYPE_STR,
    PRMTYPE_INT,
    PRMTYPE_FLT,
    PRMTYPE_CLR,
};


struct EffectAdjustEventData
{
    EffectAdjustEventData () {}
    EffectAdjustEventData (ParamType _type, void* _pData)
    {
        m_type = _type;
        m_pData = _pData;
    }

    ParamType   m_type;
    void*       m_pData;
};


DECLARE_EVENT_TYPE( EVENTID_EFFECTADJUST, -1 )

typedef void (wxEvtHandler::*EffectAdjustEventFunction)(CommonToolEvent<EffectAdjustEventData> &);

#define EffectAdjustEventHandler(func)                                 \
	(wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)\
	wxStaticCastEvent(EffectAdjustEventFunction, &func)                    
 
#define EVT_EFFECTADJUST(id, fn)                                       \
	DECLARE_EVENT_TABLE_ENTRY( EVENTID_EFFECTADJUST, id, wxID_ANY,	    \
	(wxObjectEventFunction)(wxEventFunction)						\
	(wxCommandEventFunction) wxStaticCastEvent(EffectAdjustEventFunction, &fn), (wxObject*) NULL ),


#endif