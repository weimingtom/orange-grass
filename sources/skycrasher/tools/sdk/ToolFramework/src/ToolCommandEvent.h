/*
 * OrangeGrass
 * Copyright (C) 2009 Vyacheslav Bogdanov.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/lgpl-3.0-standalone.html>.
 */
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
	CMD_LEVEL_SAVE,
	CMD_SETTINGSMODE_LEVSTART,
	CMD_SETTINGSMODE_LEVFINISH,
	CMD_SETTINGSMODE_LEVWIDTH,
	CMD_UPDATE,
	CMD_VIEW_EDITOR,
	CMD_VIEW_GAME,
	CMD_ITEM_SAVE
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