#ifndef COMMONTOOLEVENT_H_
#define COMMONTOOLEVENT_H_
#include <wx/wx.h>

static const int EVENTID_TOOLCMD	    = 32000;
static const int EVENTID_RESLOAD	    = 32001;
static const int EVENTID_RESSWITCH	    = 32002;
static const int EVENTID_LEVELLOAD	    = 32003;
static const int EVENTID_MTLLOAD	    = 32004;
static const int EVENTID_MTLADJUST	    = 32005;
static const int EVENTID_EFFECTLOAD	    = 32006;
static const int EVENTID_EFFECTADJUST	= 32007;


template <typename T>
class CommonToolEvent : public wxCommandEvent
{
public:
    CommonToolEvent( wxEventType commandType ) : wxCommandEvent(commandType, 0)
    {
    }
 
	CommonToolEvent( const CommonToolEvent& event ) : wxCommandEvent(event)
    {
        SetEventCustomData ( event.GetEventCustomData() );
    }
 
	wxEvent* Clone() const
    {
        return new CommonToolEvent<T>(*this);
    }
 
	const T& GetEventCustomData() const { return m_CustomData; }
	void SetEventCustomData( const T& _customData ) { m_CustomData = _customData; }

private:

    T   m_CustomData;
};

#endif