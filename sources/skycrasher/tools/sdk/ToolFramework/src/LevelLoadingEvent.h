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