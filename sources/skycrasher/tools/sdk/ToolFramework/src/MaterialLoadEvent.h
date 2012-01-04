#ifndef MATERIALLOADINGEVENT_H_
#define MATERIALLOADINGEVENT_H_
#include "CommonToolEvent.h"


struct MtlLoadEventData
{
    MtlLoadEventData () {}
    MtlLoadEventData (float _dif, float _amb, float _spc)
    {
        m_dif = _dif;
        m_amb = _amb;
        m_spc = _spc;
    }

    float m_dif;
    float m_amb;
    float m_spc;
};


DECLARE_EVENT_TYPE( EVENTID_MTLLOAD, -1 )

typedef void (wxEvtHandler::*MtlLoadEventFunction)(CommonToolEvent<MtlLoadEventData> &);

#define MtlLoadEventHandler(func)                                   \
	(wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)\
	wxStaticCastEvent(MtlLoadEventFunction, &func)                    
 
#define EVT_MTLLOAD(id, fn)                                         \
	DECLARE_EVENT_TABLE_ENTRY( EVENTID_MTLLOAD, id, wxID_ANY,	    \
	(wxObjectEventFunction)(wxEventFunction)						\
	(wxCommandEventFunction) wxStaticCastEvent(MtlLoadEventFunction, &fn), (wxObject*) NULL ),


#endif