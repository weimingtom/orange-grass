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
#ifndef RESOURCELOADINGEVENT_H_
#define RESOURCELOADINGEVENT_H_
#include "CommonToolEvent.h"


struct ResLoadEventData
{
    ResLoadEventData () {}
    ResLoadEventData (const wxString& _res, const wxString& _group, const wxString& _icon)
    {
        m_Resource = _res;
        m_ResourceGroup = _group;
        m_ResourceIcon = _icon;
    }

    wxString	m_Resource;
    wxString	m_ResourceGroup;
    wxString	m_ResourceIcon;
};


DECLARE_EVENT_TYPE( EVENTID_RESLOAD, -1 )

typedef void (wxEvtHandler::*ResLoadEventFunction)(CommonToolEvent<ResLoadEventData> &);

#define ResLoadEventHandler(func)                                   \
	(wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)\
	wxStaticCastEvent(ResLoadEventFunction, &func)                    
 
#define EVT_RESLOAD(id, fn)                                         \
	DECLARE_EVENT_TABLE_ENTRY( EVENTID_RESLOAD, id, wxID_ANY,	    \
	(wxObjectEventFunction)(wxEventFunction)						\
	(wxCommandEventFunction) wxStaticCastEvent(ResLoadEventFunction, &fn), (wxObject*) NULL ),


#endif