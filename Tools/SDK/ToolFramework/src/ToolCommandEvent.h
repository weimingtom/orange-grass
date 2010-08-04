#ifndef TOOLCOMMANDEVENT_H_
#define TOOLCOMMANDEVENT_H_
#include <wx/wx.h>
#include "CommonToolEvent.h"


enum CmdEvents
{
	CMD_COORDGRID,
	CMD_AABB,
	CMD_EDITMODE_ADJUST,
	CMD_EDITMODE_SETTINGS,
	CMD_EDITMODE_OBJECTS,
	CMD_LEVEL_SAVE
};


struct ToolCmdEventData
{
    ToolCmdEventData () {}
    ToolCmdEventData (CmdEvents _type, bool _switch)
    {
        m_CmdType = _type;
        m_bSwitcher = _switch;
    }

    CmdEvents		m_CmdType;
    bool			m_bSwitcher;
};


DECLARE_EVENT_TYPE( EVENTID_TOOLCMD, -1 )

typedef void (wxEvtHandler::*ToolCmdEventFunction)(CommonToolEvent<ToolCmdEventData> &);

#define ToolCmdEventHandler(func)                                   \
	(wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)\
	wxStaticCastEvent(ToolCmdEventFunction, &func)                    
 
#define EVT_TOOLCMD(id, fn)                                         \
	DECLARE_EVENT_TABLE_ENTRY( EVENTID_TOOLCMD, id, wxID_ANY,	    \
	(wxObjectEventFunction)(wxEventFunction)						\
	(wxCommandEventFunction) wxStaticCastEvent(ToolCmdEventFunction, &fn), (wxObject*) NULL ),

#endif